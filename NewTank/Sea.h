#pragma once
#include "Item.h"
class CSea :
    public CItem
{
public:
    CSea(int x, int y)
    {
        m_Pos.SetX(x);
        m_Pos.SetY(y);
        m_bDisapper = false;
        m_color = LIGHTBLUE;
        this->CalculateSphere();
    };
    ~CSea();
};

