
#include "Server.h"
#include "Functions.h"

void CastleWarTimer(tm* timeinfo)
{
    // Guerra de Castelo: Todo Domingo às 21:00
    if (timeinfo->tm_wday == 0 && timeinfo->tm_hour == 21)
    {
        if (timeinfo->tm_min == 0 && CastleState == 0)
        {
            CastleState = 1; // Início da Guerra
            SendNotice("A Guerra de Castelo começou! Protejam o Rei!");
            
            // Spawn dos Guardas do Castelo
            // GenerateMob(GUARD_ID, CASTLE_X, CASTLE_Y);
        }
        
        if (timeinfo->tm_min == 50 && CastleState == 1)
        {
            CastleState = 0; // Fim da Guerra
            SendNotice("A Guerra de Castelo terminou!");
            
            // Lógica de premiação para a Guilda vencedora
        }
    }
}

void OnCastleKingKilled(int killerConn)
{
    int guildID = pMob[killerConn].MOB.Guild;
    if (guildID > 0)
    {
        char guildName[16];
        BASE_GetGuildName(ServerGroup, guildID, guildName);
        SendNotice(strFmt("O Rei foi derrotado pela guilda %s! Eles agora dominam o castelo!", guildName));
        
        // Atualiza o dono do castelo no banco de dados
        auto& pc = cSQL::instance();
        char query[256];
        sprintf(query, "UPDATE castle_info SET owner_guild = %d WHERE castle_id = 1", guildID);
        pc.wQuery(query);
    }
}
