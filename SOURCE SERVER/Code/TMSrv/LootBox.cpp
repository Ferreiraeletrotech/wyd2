
#include "Server.h"
#include "Functions.h"
#include <vector>
#include <random>

struct LootBoxItem {
    int sIndex;
    int Rate; // Chance em 1000
};

// Configuração dos itens do Baú de Boss (ID 4050 como exemplo)
std::vector<LootBoxItem> g_BossBoxItems = {
    { 4011, 10 },   // Barra de 1Bi (1%)
    { 4010, 50 },   // Barra de 100mi (5%)
    { 4009, 100 },  // Barra de 50mi (10%)
    { 412, 200 },   // Poeira de Lac (20%)
    { 413, 300 },   // Poeira de Ori (30%)
    { 746, 340 }    // Resto de Ori (34%)
};

void Exec_MSG_LootBoxOpen(int conn, char* pMsg)
{
    MSG_LootBoxOpen* m = (MSG_LootBoxOpen*)pMsg;
    
    // Valida se o jogador tem o baú no slot informado
    if (pMob[conn].MOB.Carry[m->Slot].sIndex != m->ItemID) {
        return;
    }

    // Sorteio
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 999);
    int luckyNumber = dis(gen);

    int currentRate = 0;
    int winningIndex = 0;
    
    for (int i = 0; i < g_BossBoxItems.size(); i++) {
        currentRate += g_BossBoxItems[i].Rate;
        if (luckyNumber < currentRate) {
            winningIndex = i;
            break;
        }
    }

    // Prepara o pacote de resultado para o cliente (Gacha visual)
    MSG_LootBoxResult sm;
    sm.Type = _MSG_LootBoxResult;
    sm.Size = sizeof(MSG_LootBoxResult);
    
    // Preenche 10 itens aleatórios para a "roleta", colocando o vencedor em uma posição específica
    for (int i = 0; i < 10; i++) {
        int randIdx = dis(gen) % g_BossBoxItems.size();
        sm.ItemList[i] = g_BossBoxItems[randIdx].sIndex;
    }
    
    // O vencedor real será o 7º item da lista visual para a animação parar nele
    sm.WinningItemIndex = 7;
    sm.ItemList[7] = g_BossBoxItems[winningIndex].sIndex;

    // Remove o baú do inventário
    memset(&pMob[conn].MOB.Carry[m->Slot], 0, sizeof(STRUCT_ITEM));
    SendItem(conn, ITEM_PLACE_CARRY, m->Slot, &pMob[conn].MOB.Carry[m->Slot]);

    // Entrega o item real
    STRUCT_ITEM prize = { 0 };
    prize.sIndex = g_BossBoxItems[winningIndex].sIndex;
    PutItem(conn, &prize);

    // Envia o resultado para disparar a interface visual
    pUser[conn].cSock.SendOneMessage((char*)&sm, sm.Size);
    
    char notice[128];
    sprintf(notice, "[BAÚ] %s abriu um Baú de Boss e ganhou um item raro!", pMob[conn].MOB.MobName);
    if (g_BossBoxItems[winningIndex].Rate < 100) { // Avisa globalmente se for item raro (<10%)
        SendNotice(notice);
    }
}
