
#include "SControlContainer.h"
#include "SControl.h"
#include "TMGlobal.h"
#include "Basedef.h"

class SBossPanel {
public:
    SPanel* m_pMainPanel;
    SListControl* m_pBossList;
    SButton* m_pBtnTeleport;
    
    // DPS Meter (Ranking de Dano)
    SPanel* m_pDPSPanel;
    STextControl* m_pRankingText[5];

    void Init(SControlContainer* pContainer) {
        // Janela Principal de Bosses
        m_pMainPanel = (SPanel*)pContainer->FindControl(91000); 
        if (m_pMainPanel) {
            m_pMainPanel->SetVisible(false);
            m_pMainPanel->SetPos(150, 80);
        }

        m_pBossList = (SListControl*)pContainer->FindControl(91001);
        m_pBtnTeleport = (SButton*)pContainer->FindControl(91002);

        // Janela de DPS (Ranking de Dano)
        m_pDPSPanel = (SPanel*)pContainer->FindControl(91100);
        if (m_pDPSPanel) {
            m_pDPSPanel->SetVisible(false);
            m_pDPSPanel->SetPos(600, 50); // Lado superior direito
        }

        for (int i = 0; i < 5; i++) {
            m_pRankingText[i] = (STextControl*)pContainer->FindControl(91101 + i);
        }
    }

    void ShowPanel(bool bShow) {
        if (m_pMainPanel) {
            m_pMainPanel->SetVisible(bShow);
            if (bShow) {
                // Solicita lista atualizada ao servidor
                MSG_STANDARD sm;
                sm.Type = _MSG_BossInfo;
                sm.Size = sizeof(MSG_STANDARD);
                // SendPacket(&sm);
            }
        }
    }

    void OnPacketBossInfo(MSG_BossInfo* pPacket) {
        if (!m_pBossList) return;
        
        m_pBossList->ClearList();
        for (int i = 0; i < pPacket->BossCount; i++) {
            char buffer[128];
            sprintf(buffer, "%s - %s (%d, %d)", 
                pPacket->Bosses[i].Name, 
                pPacket->Bosses[i].Status == 1 ? "VIVO" : "MORTO",
                pPacket->Bosses[i].X, pPacket->Bosses[i].Y);
            
            m_pBossList->AddString(buffer);
        }
    }

    void OnPacketRanking(MSG_BossDamageRanking* pPacket) {
        if (!m_pDPSPanel) return;
        
        m_pDPSPanel->SetVisible(true);
        for (int i = 0; i < 5; i++) {
            if (i < pPacket->PlayerCount) {
                char buffer[64];
                sprintf(buffer, "%d. %s: %lld", i + 1, pPacket->Ranking[i].Name, pPacket->Ranking[i].Damage);
                m_pRankingText[i]->SetText(buffer);
                m_pRankingText[i]->SetVisible(true);
            } else {
                m_pRankingText[i]->SetVisible(false);
            }
        }
    }
};
