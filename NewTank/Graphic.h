#pragma once
#include <graphics.h>
#include "MyRect.h"
/*屏幕长宽*/
#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  600

/*战斗区域的左上坐标和右下坐标*/
#define BATTEL_GROUND_X1 10
#define BATTEL_GROUND_Y1 10
#define BATTEL_GROUND_X2 600
#define BATTEL_GROUND_Y2 (SCREEN_HEIGHT - BATTEL_GROUND_X1)

class CGraphic
{
public:
    CGraphic();
    ~CGraphic();

    static void Create();         //创建窗口
    static void Destroy();        //销毁窗口

    static void DrawBattleGround();  //绘制战斗区域

    static int GetScreenWidth();  //外部接口 获取宽度
    static int GetScreenHeight(); //外部接口 获取高度

    static CMyRect GetBattleGround(); //获取战斗区域
private:
    //static int m_Screen_Width;
    //static int m_Screen_Height;

    static CMyRect m_RectScreen;
    static CMyRect m_RectBattleGround;
};

