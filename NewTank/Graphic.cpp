#include "stdafx.h"
#include "Graphic.h"

// CGraphic::m_Screen_Width = SCREEN_WIDTH;
//int CGraphic::m_Screen_Height = SCREEN_HEIGHT;
CMyRect CGraphic::m_RectScreen;
CMyRect CGraphic::m_RectBattleGround;

CGraphic::CGraphic()
{
}


CGraphic::~CGraphic()
{
}

void CGraphic::Create()
{
    m_RectScreen.Set(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    /*初始化画布*/
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
    setbkcolor(DARKGRAY);//设置画布为灰色

    m_RectBattleGround.Set(BATTEL_GROUND_X1, BATTEL_GROUND_Y1,
                           BATTEL_GROUND_X2, BATTEL_GROUND_Y2);
}

void CGraphic::Destroy()
{
    closegraph();
}

void CGraphic::DrawBattleGround()
{
    rectangle(m_RectBattleGround.GetStartPoint().GetX(),
        m_RectBattleGround.GetStartPoint().GetY(),
        m_RectBattleGround.GetEndPoint().GetX(),
        m_RectBattleGround.GetEndPoint().GetY());
}

int CGraphic::GetScreenWidth()
{
    return SCREEN_WIDTH;
}

int CGraphic::GetScreenHeight()
{
    return SCREEN_HEIGHT;
}

CMyRect CGraphic::GetBattleGround()
{
    return m_RectBattleGround;
}



