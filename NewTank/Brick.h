#pragma once
#include "Item.h"
class CBrick :
    public CItem
{
public:
    CBrick(int x, int y)
    {
        m_Pos.SetX(x);
        m_Pos.SetY(y);
        m_bDisapper = false;
        m_color = LIGHTGRAY;
        this->CalculateSphere();
    };
    ~CBrick();
};

