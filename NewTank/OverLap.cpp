#include "stdafx.h"
#include "OverLap.h"


COverLap::COverLap()
{
}


COverLap::~COverLap()
{
}

bool COverLap::CheckPointRect(CMyPoint & Point, CMyRect & Rect)
{
    if (Point.GetX() < Rect.GetStartPoint().GetX() ||
        Point.GetX() > Rect.GetEndPoint().GetX()   ||
        Point.GetY() < Rect.GetStartPoint().GetY() ||
        Point.GetY() > Rect.GetEndPoint().GetY())
    {
        return false;
    }
    else
    {
        return true;
    }
}

//����ӵ��ص� ���ص�����true
bool COverLap::CheckInterSect(CMyRect & Rect1, CMyRect & Rect2)
{
    if (CheckPointRect(Rect1.GetStartPoint(), Rect2) ||
        CheckPointRect(Rect1.GetEndPoint(), Rect2) ||
        CheckPointRect(Rect1.GetTRPoint(), Rect2) ||
        CheckPointRect(Rect1.GetBLPoint(), Rect2)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool COverLap::CheckTankPointRect(CMyPoint & Point, CMyRect & Rect)
{
    if (Point.GetX() < Rect.GetStartPoint().GetX()  ||
        Point.GetX() > Rect.GetEndPoint().GetX()    ||
        Point.GetY() < Rect.GetStartPoint().GetY()  ||
        Point.GetY() > Rect.GetEndPoint().GetY())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool COverLap::CheckTankInterSect(CMyRect & Rect1, CMyRect & Rect2)
{
    if (CheckTankPointRect(Rect1.GetStartPoint(), Rect2) ||
        CheckTankPointRect(Rect1.GetEndPoint(), Rect2) ||
        CheckTankPointRect(Rect1.GetTRPoint(), Rect2) ||
        CheckTankPointRect(Rect1.GetBLPoint(), Rect2)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}
