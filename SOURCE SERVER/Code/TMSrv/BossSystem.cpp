
#include "Server.h"
#include "Functions.h"

struct STRUCT_BOSS_CONFIG {
    int MobID;
    int PosX, PosY;
    int SpawnHour;
    int SpawnMin;
    bool IsSpawned;
};

STRUCT_BOSS_CONFIG g_Bosses[] = {
    { 250, 2100, 2100, 20, 0, false }, // Boss 1 às 20:00
    { 251, 1050, 1050, 22, 0, false }  // Boss 2 às 22:00
};

void BossTimer()
{
    time_t now = time(0);
    struct tm* ltm = localtime(&now);

    for (int i = 0; i < sizeof(g_Bosses) / sizeof(STRUCT_BOSS_CONFIG); i++)
    {
        if (ltm->tm_hour == g_Bosses[i].SpawnHour && ltm->tm_min == g_Bosses[i].SpawnMin)
        {
            if (!g_Bosses[i].IsSpawned)
            {
                // Lógica de Spawn
                // int mobIdx = SummonMob(g_Bosses[i].MobID, g_Bosses[i].PosX, g_Bosses[i].PosY);
                char notice[128];
                sprintf(notice, "O Boss %d nasceu em %d, %d!", g_Bosses[i].MobID, g_Bosses[i].PosX, g_Bosses[i].PosY);
                SendNotice(notice);
                g_Bosses[i].IsSpawned = true;
            }
        }
        else
        {
            g_Bosses[i].IsSpawned = false;
        }
    }
}
