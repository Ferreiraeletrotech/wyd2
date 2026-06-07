
#include "SControlContainer.h"
#include "SControl.h"
#include "TMGlobal.h"
#include "Basedef.h"

class SLootBox {
public:
    SPanel* m_pGachaPanel;
    SImageControl* m_pItemSlots[10];
    SButton* m_pBtnClose;
    STextControl* m_pResultText;
    
    int m_AnimationTick;
    bool m_IsAnimating;
    int m_WinningIndex;

    void Init(SControlContainer* pContainer) {
        m_pGachaPanel = (SPanel*)pContainer->FindControl(92000); 
        if (m_pGachaPanel) {
            m_pGachaPanel->SetVisible(false);
            m_pGachaPanel->SetPos(250, 150);
        }

        for (int i = 0; i < 10; i++) {
            m_pItemSlots[i] = (SImageControl*)pContainer->FindControl(92001 + i);
        }

        m_pBtnClose = (SButton*)pContainer->FindControl(92011);
        m_pResultText = (STextControl*)pContainer->FindControl(92012);
        
        m_IsAnimating = false;
    }

    void OnPacketLootBoxResult(MSG_LootBoxResult* pPacket) {
        if (!m_pGachaPanel) return;

        m_pGachaPanel->SetVisible(true);
        m_IsAnimating = true;
        m_AnimationTick = 0;
        m_WinningIndex = pPacket->WinningItemIndex;

        for (int i = 0; i < 10; i++) {
            // Define a imagem do item no slot da interface
            // m_pItemSlots[i]->SetItemImage(pPacket->ItemList[i]);
            m_pItemSlots[i]->SetVisible(true);
        }
        
        if (m_pResultText) m_pResultText->SetVisible(false);
    }

    void Update() {
        if (!m_IsAnimating) return;

        m_AnimationTick++;

        // Simulação de animação de "roleta"
        // Move os itens ou altera o brilho...
        
        if (m_AnimationTick > 100) { // Fim da animação (aprox 3-4 segundos)
            m_IsAnimating = false;
            if (m_pResultText) {
                m_pResultText->SetText("Parabéns! Você recebeu o item.");
                m_pResultText->SetVisible(true);
            }
            // Destaca o m_WinningIndex
        }
    }
};
