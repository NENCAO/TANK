#pragma once
#include "MyRect.h"

class COverLap
{
public:
    COverLap();
    ~COverLap();

    /*检测点是否是在矩形内*/
    static bool CheckPointRect(CMyPoint &Point, CMyRect &Rect);
    /*检测矩形是否重叠*/
    static bool CheckInterSect(CMyRect &Rect1, CMyRect &Rect2);

    /*坦克的碰撞检测 大一圈即可*/
    static bool CheckTankPointRect(CMyPoint &Point, CMyRect &Rect);
    /*检测坦克是否重叠*/
    static bool CheckTankInterSect(CMyRect &Rect1, CMyRect &Rect2);
};

