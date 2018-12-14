#pragma once
#include <graphics.h>
#include "MyRect.h"
/*��Ļ����*/
#define SCREEN_WIDTH   800
#define SCREEN_HEIGHT  600

/*ս������������������������*/
#define BATTEL_GROUND_X1 10
#define BATTEL_GROUND_Y1 10
#define BATTEL_GROUND_X2 600
#define BATTEL_GROUND_Y2 (SCREEN_HEIGHT - BATTEL_GROUND_X1)

class CGraphic
{
public:
    CGraphic();
    ~CGraphic();

    static void Create();         //��������
    static void Destroy();        //���ٴ���

    static void DrawBattleGround();  //����ս������

    static int GetScreenWidth();  //�ⲿ�ӿ� ��ȡ���
    static int GetScreenHeight(); //�ⲿ�ӿ� ��ȡ�߶�

    static CMyRect GetBattleGround(); //��ȡս������
private:
    //static int m_Screen_Width;
    //static int m_Screen_Height;

    static CMyRect m_RectScreen;
    static CMyRect m_RectBattleGround;
};

