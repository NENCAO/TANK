#pragma once
#include "Item.h"
class CIron :
    public CItem
{
public:
    CIron(int x, int y)
    {
        m_Pos.SetX(x);
        m_Pos.SetY(y);
        m_bDisapper = false;
        m_color = BLACK;
        this->CalculateSphere();
    };
    ~CIron();
};

