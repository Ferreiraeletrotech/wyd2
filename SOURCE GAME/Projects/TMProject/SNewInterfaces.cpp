#include "SControl.h"
#include "TMFieldScene.h"

class SRankingPanel : public SPanel
{
public:
    SRankingPanel() : SPanel(90020, 100, 100, 400, 500, 0, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH) {}
    
    void Init()
    {
        m_pTitle = new SText(-1, "Ranking Geral", 0xFFFFFFFF, 150, 10, 200, 20, 0, 0, 1, 0);
        AddChild(m_pTitle);
        
        m_pList = new SListBox(90021, 20, 50, 360, 400, 0x77000000, 1);
        AddChild(m_pList);
        
        SetVisible(0);
    }

private:
    SText* m_pTitle;
    SListBox* m_pList;
};

class SCashShopPanel : public SPanel
{
public:
    SCashShopPanel() : SPanel(90030, 150, 100, 500, 400, 0, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH) {}
    
    void Init()
    {
        m_pTitle = new SText(-1, "Loja de Cash", 0xFFFFFFFF, 200, 10, 200, 20, 0, 0, 1, 0);
        AddChild(m_pTitle);
        
        m_pGrid = new SGridControl(90031, 20, 50, 460, 300, 5, 4);
        AddChild(m_pGrid);
        
        SetVisible(0);
    }

private:
    SText* m_pTitle;
    SGridControl* m_pGrid;
};
