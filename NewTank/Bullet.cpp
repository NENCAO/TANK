#include "stdafx.h"
#include "Bullet.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

CBullet::CBullet(CMyPoint pos, Dir dir, COLORREF color)
{
    m_Pos = pos;
    m_dir = dir;
    m_color = color;

    m_step = 8;

    m_bDisapper = false;

    CalculateSphere();
}

void CBullet::Display()
{
    COLORREF fill_color_save = getfillcolor();
    COLORREF color_save = getcolor();

    setfillcolor(m_color);
    setcolor(m_color);

    fillcircle(m_Pos.GetX() - 1, m_Pos.GetY() - 1, 4);
    setcolor(color_save);
    setfillcolor(fill_color_save);
}


void CBullet::MoveUp()
{
    m_Pos.SetY(m_Pos.GetY() - m_step);
    CalculateSphere();

    if (m_Pos.GetY() - m_step < BATTEL_GROUND_Y1)
    {
        m_bDisapper = true;
        return;
    }
}

void CBullet::MoveDown()
{
    m_Pos.SetY(m_Pos.GetY() + m_step);
    CalculateSphere();

    if (m_Pos.GetY() + m_step > BATTEL_GROUND_Y2)
    {
        m_bDisapper = true;
        return;
    }
}

void CBullet::MoveLeft()
{
    m_Pos.SetX(m_Pos.GetX() - m_step);
    CalculateSphere();

    if (m_Pos.GetX() - m_step < BATTEL_GROUND_X1)
    {
        m_bDisapper = true;
        return;
    }
}

void CBullet::MoveRight()
{
    m_Pos.SetX(m_Pos.GetX() + m_step);
    CalculateSphere();

    if (m_Pos.GetX() + m_step > BATTEL_GROUND_X2)
    {
        m_bDisapper = true;
        return;
    }
}

void CBullet::SetDisAppear()
{
    m_bDisapper = true;
}

void CBullet::CalculateSphere()
{
    m_RectSphere.Set(m_Pos.GetX() - 2, m_Pos.GetY() - 2,
        m_Pos.GetX() + 2, m_Pos.GetY() + 2);
}

void CBullet::Move()
{
    switch (m_dir)
    {
    case UP:
        MoveUp();
        break;
    case DOWN:
        MoveDown();
        break;
    case LEFT:
        MoveLeft();
        break;
    case RIGHT:
        MoveRight();
        break;
    default:
        break;
    }
}
