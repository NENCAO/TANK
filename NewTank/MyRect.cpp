#include "stdafx.h"
#include "MyRect.h"


CMyRect::~CMyRect()
{
}

void CMyRect::Set(const CMyPoint pStart, const CMyPoint pEnd)
{
    m_SrartPonit = pStart;
    m_EndPoint = pEnd;
}

void CMyRect::Set(int x1, int y1, int x2, int y2)
{
    m_SrartPonit.SetX(x1);
    m_SrartPonit.SetY(y1);
    m_EndPoint.SetX(x2);
    m_EndPoint.SetY(y2);
}

void CMyRect::SetStartPonit(const CMyPoint p)
{
    m_SrartPonit = p;
}

void CMyRect::SetEndPonit(const CMyPoint p)
{
    m_EndPoint = p;
}

CMyPoint CMyRect::GetStartPoint() const
{
    return m_SrartPonit;
}

CMyPoint CMyRect::GetEndPoint() const
{
    return m_EndPoint;
}

int CMyRect::GetWidth()
{
    return m_EndPoint.GetX() - m_SrartPonit.GetX();
}

int CMyRect::GetHeight()
{
    return m_EndPoint.GetY() - m_SrartPonit.GetY();
}

CMyPoint CMyRect::GetTRPoint()
{
    CMyPoint p = m_SrartPonit;
    p.SetX(m_EndPoint.GetX());

    return p;
}

CMyPoint CMyRect::GetBLPoint()
{
    CMyPoint p = m_SrartPonit;
    p.SetY(m_EndPoint.GetY());

    return p;
}


void CMyRect::Check()
{
    if (m_SrartPonit.GetX() > m_EndPoint.GetX() ||
        m_SrartPonit.GetY() > m_EndPoint.GetY())
    {
        CMyPoint Temp = m_SrartPonit;
        m_SrartPonit = m_EndPoint;
        m_EndPoint = Temp;
    }
}
