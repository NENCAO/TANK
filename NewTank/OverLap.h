#pragma once
#include "MyRect.h"

class COverLap
{
public:
    COverLap();
    ~COverLap();

    /*�����Ƿ����ھ�����*/
    static bool CheckPointRect(CMyPoint &Point, CMyRect &Rect);
    /*�������Ƿ��ص�*/
    static bool CheckInterSect(CMyRect &Rect1, CMyRect &Rect2);

    /*̹�˵���ײ��� ��һȦ����*/
    static bool CheckTankPointRect(CMyPoint &Point, CMyRect &Rect);
    /*���̹���Ƿ��ص�*/
    static bool CheckTankInterSect(CMyRect &Rect1, CMyRect &Rect2);
};

