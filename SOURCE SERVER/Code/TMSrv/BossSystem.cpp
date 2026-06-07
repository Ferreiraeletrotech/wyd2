
#include "Server.h"
#include "Functions.h"
#include <map>
#include <vector>
#include <algorithm>
#include <string>

struct STRUCT_BOSS_STATUS {
    int MobID;
    char Name[16];
    int PosX, PosY;
    int SpawnHour;
    int SpawnMin;
    int CurrentMobIndex; // Index atual do mob no mundo
    bool IsAlive;
    
    // Gerenciamento de Dano
    std::map<int, long long> DamageMap; // conn -> total damage
};

STRUCT_BOSS_STATUS g_BossList[] = {
    { 250, "Lich Supremo", 2100, 2100, 20, 0, 0, false },
    { 251, "Xeno Gigante", 1050, 1050, 22, 0, 0, false },
    { 252, "Aranha Rei", 3000, 3000, 15, 30, 0, false }
};

const int BOSS_COUNT = sizeof(g_BossList) / sizeof(STRUCT_BOSS_STATUS);

// Função chamada quando um jogador causa dano
void OnBossDamage(int attackerConn, int targetMobIdx, int damage)
{
    for (int i = 0; i < BOSS_COUNT; i++)
    {
        if (g_BossList[i].IsAlive && g_BossList[i].CurrentMobIndex == targetMobIdx)
        {
            g_BossList[i].DamageMap[attackerConn] += damage;
            
            // A cada X segundos ou a cada dano, podemos enviar o ranking atualizado
            // Para performance, vamos enviar apenas para quem está na área do Boss
            if (damage % 5 == 0) // Exemplo: envia a cada 5 hits para não sobrecarregar
            {
                SendBossRanking(i);
            }
            break;
        }
    }
}

// Envia o Top 5 de dano para os jogadores próximos
void SendBossRanking(int bossIdx)
{
    if (g_BossList[bossIdx].DamageMap.empty()) return;

    struct DamageEntry {
        int conn;
        long long damage;
    };
    
    std::vector<DamageEntry> ranking;
    for (auto const& [conn, dmg] : g_BossList[bossIdx].DamageMap) {
        ranking.push_back({conn, dmg});
    }

    // Ordena por maior dano
    std::sort(ranking.begin(), ranking.end(), [](const DamageEntry& a, const DamageEntry& b) {
        return a.damage > b.damage;
    });

    MSG_BossDamageRanking sm;
    sm.Type = _MSG_BossDamageRanking;
    sm.Size = sizeof(MSG_BossDamageRanking);
    sm.BossIndex = bossIdx;
    sm.PlayerCount = std::min((int)ranking.size(), 5);

    for (int i = 0; i < sm.PlayerCount; i++) {
        strncpy(sm.Ranking[i].Name, pMob[ranking[i].conn].MOB.MobName, 16);
        sm.Ranking[i].Damage = ranking[i].damage;
    }

    // Envia para todos na área do boss
    GridMulticast(g_BossList[bossIdx].PosX, g_BossList[bossIdx].PosY, (MSG_STANDARD*)&sm, 0);
}

// Envia a lista de Bosses para o jogador (chamado ao abrir o painel)
void SendBossList(int conn)
{
    MSG_BossInfo sm;
    sm.Type = _MSG_BossInfo;
    sm.Size = sizeof(MSG_BossInfo);
    sm.BossCount = BOSS_COUNT;

    for (int i = 0; i < BOSS_COUNT; i++) {
        sm.Bosses[i].MobIndex = g_BossList[i].MobID;
        strncpy(sm.Bosses[i].Name, g_BossList[i].Name, 16);
        sm.Bosses[i].X = g_BossList[i].PosX;
        sm.Bosses[i].Y = g_BossList[i].PosY;
        sm.Bosses[i].Status = g_BossList[i].IsAlive ? 1 : 0;
        
        // Cálculo simples de tempo para o próximo respawn (exemplo)
        sm.Bosses[i].RespawnTime = 3600; 
    }

    pUser[conn].cSock.SendOneMessage((char*)&sm, sm.Size);
}

void BossTimer()
{
    time_t now = time(0);
    struct tm* ltm = localtime(&now);

    for (int i = 0; i < BOSS_COUNT; i++)
    {
        if (ltm->tm_hour == g_BossList[i].SpawnHour && ltm->tm_min == g_BossList[i].SpawnMin)
        {
            if (!g_BossList[i].IsAlive)
            {
                // Simulação de Spawn - No código real seria SummonMob
                g_BossList[i].CurrentMobIndex = 10000 + i; // Index fictício para teste
                g_BossList[i].IsAlive = true;
                g_BossList[i].DamageMap.clear();

                char notice[128];
                sprintf(notice, "[BOSS] O terrível %s despertou em %d, %d!", g_BossList[i].Name, g_BossList[i].PosX, g_BossList[i].PosY);
                SendNotice(notice);
            }
        }
    }
}

// Função chamada quando o Boss morre
void OnBossKilled(int targetMobIdx)
{
    for (int i = 0; i < BOSS_COUNT; i++)
    {
        if (g_BossList[i].IsAlive && g_BossList[i].CurrentMobIndex == targetMobIdx)
        {
            g_BossList[i].IsAlive = false;
            
            char notice[128];
            sprintf(notice, "[BOSS] %s foi derrotado!", g_BossList[i].Name);
            SendNotice(notice);

	            // Entrega de prêmios para o Top 3
	            struct DamageEntry { int conn; long long damage; };
	            std::vector<DamageEntry> ranking;
	            for (auto const& [conn, dmg] : g_BossList[i].DamageMap) ranking.push_back({conn, dmg});
	            std::sort(ranking.begin(), ranking.end(), [](const DamageEntry& a, const DamageEntry& b) { return a.damage > b.damage; });

	            for (int rank = 0; rank < std::min((int)ranking.size(), 3); rank++) {
	                int winnerConn = ranking[rank].conn;
	                if (winnerConn > 0 && winnerConn < MAX_USER) {
	                    STRUCT_ITEM prize = { 0 };
	                    if (rank == 0) prize.sIndex = 4011; // 1º Lugar: Barra de 1Bi
	                    else if (rank == 1) prize.sIndex = 4010; // 2º Lugar: Barra de 100mi
	                    else prize.sIndex = 4009; // 3º Lugar: Barra de 50mi

	                    PutItem(winnerConn, &prize);
	                    char winMsg[128];
	                    sprintf(winMsg, "Parabéns! Você ficou em %dº lugar no dano e recebeu seu prêmio.", rank + 1);
	                    SendClientMessage(winnerConn, winMsg);
	                }
	            }
	            
	            g_BossList[i].DamageMap.clear();
            break;
        }
    }
}
