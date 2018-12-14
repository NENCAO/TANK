#include "stdafx.h"
#include "Item.h"


CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Display()
{
    setfillcolor(m_color);
    fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetStartPoint().GetY(),
        m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetEndPoint().GetY());
}

bool CItem::IsDisAppear()
{
    return m_bDisapper;
}

void CItem::SetDisAppear()
{
    m_bDisapper = true;
}

CMyRect CItem::GetSphere()
{
    return m_RectSphere;
}

CMyPoint CItem::GetPoint()
{
    return m_Pos;
}

void CItem::CalculateSphere()
{
    m_RectSphere.Set(m_Pos.GetX() - 12, m_Pos.GetY() - 12,
        m_Pos.GetX() + 12, m_Pos.GetY() + 12);
}

