#pragma once
#include "Item.h"
class CMatrix
    :public CItem
{
public:
    CMatrix(int x , int y)
    {
        m_Pos.SetX(x);
        m_Pos.SetY(y);
        m_bDisapper = false;
        m_color = RED;
        this->CalculateSphere();
    };
    ~CMatrix();



};

