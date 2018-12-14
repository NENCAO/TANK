#pragma once
#include "Item.h"
class CGrass :
    public CItem
{
public:
    CGrass(int x, int y)
    {
        m_Pos.SetX(x);
        m_Pos.SetY(y);
        m_bDisapper = false;
        m_color = GREEN;
        this->CalculateSphere();
    };
    ~CGrass();
};

