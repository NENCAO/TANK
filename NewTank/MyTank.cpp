#include "stdafx.h"
#include "MyTank.h"
#include "Bullet.h"

CMyTank::~CMyTank()
{
}

/*坦克移动的方向*/
void CMyTank::SetDir(Dir dir)
{
    m_dir = dir;
}

/*坦克的显示*/
void CMyTank::Display()
{
    COLORREF fill_color_save = getfillcolor();
    COLORREF color_save = getfillcolor();
    
    setfillcolor(m_color);

    switch (m_dir)
    {
    case UP:

        DrawTankBody();                                                     //显示主体和履带
        line(m_Pos.GetX(), m_Pos.GetY(), m_Pos.GetX(), m_Pos.GetY() - 15);  //显示炮管
        break;
    case DOWN:
        DrawTankBody();
        line(m_Pos.GetX(), m_Pos.GetY(), m_Pos.GetX(), m_Pos.GetY() + 15);
        break;
    case LEFT:
        DrawTankBody();
        line(m_Pos.GetX(), m_Pos.GetY(), m_Pos.GetX() - 15, m_Pos.GetY());
        break;
    case RIGHT:
        DrawTankBody();
        line(m_Pos.GetX(), m_Pos.GetY(), m_Pos.GetX() + 15, m_Pos.GetY());
        break;
    default:
        break;
    }

    setfillcolor(color_save);
    setfillcolor(fill_color_save);
}

void CMyTank::MoveUp()
{
    SetDir(Dir::UP);
    if (m_Pos.GetY() - m_step - 12 < BATTEL_GROUND_Y1)
    {
        return;
    }

    m_Pos.SetY(m_Pos.GetY() - m_step);
    CalculateSphere();
}

void CMyTank::MoveDown()
{
    SetDir(Dir::DOWN);
    if (m_Pos.GetY() + m_step + 12 > BATTEL_GROUND_Y2)
    {
        return;
    }

    m_Pos.SetY(m_Pos.GetY() + m_step);
    CalculateSphere();
}

void CMyTank::MoveLeft()
{
    SetDir(Dir::LEFT);
    if (m_Pos.GetX() - m_step - 12 < BATTEL_GROUND_X1)
    {
        return;
    }

    m_Pos.SetX(m_Pos.GetX() - m_step);
    CalculateSphere();
}

void CMyTank::MoveRight()
{
    SetDir(Dir::RIGHT);
    if (m_Pos.GetX() + m_step + 12 > BATTEL_GROUND_X2)
    {
        return;
    }

    m_Pos.SetX(m_Pos.GetX() + m_step);
    CalculateSphere();
}

void CMyTank::Move()
{
}

/*用list来管理子弹*/
void CMyTank::Shoot(std::list<CMyObject*>& LstBullets)
{
    if (!b_Cheat)
    {
        if (LstBullets.size() >= 2)
        {
            return;
        }
    }
    /*作弊模式*/
    else
    {
        CBullet* pBullet = new CBullet(m_Pos, m_dir, m_color);
        LstBullets.push_back(pBullet);
        CBullet* pBullet2 = new CBullet(m_Pos, (Dir)(int)((m_dir + 1) % 4), m_color);
        LstBullets.push_back(pBullet2);
        CBullet* pBullet3 = new CBullet(m_Pos, (Dir)(int)((m_dir + 2) % 4), m_color);
        LstBullets.push_back(pBullet3);
        CBullet* pBullet4 = new CBullet(m_Pos, (Dir)(int)((m_dir + 3) % 4), m_color);
        LstBullets.push_back(pBullet4);
        return;
    }
    CBullet* pBullet = new CBullet(m_Pos, m_dir, m_color);
    LstBullets.push_back(pBullet);
}

/*设置坦克的区域 并以此来画履带*/
void CMyTank::CalculateSphere()
{
    switch (m_dir)
    {
    case UP:
    case DOWN:
        m_RectSphere.Set(m_Pos.GetX() - 12, m_Pos.GetY() - 12,
            m_Pos.GetX() + 12, m_Pos.GetX() + 12);
    case LEFT:
    case RIGHT:
        m_RectSphere.Set(m_Pos.GetX() - 12, m_Pos.GetY() - 12,
            m_Pos.GetX() + 12, m_Pos.GetY() + 12);

        break;
    default:
        break;
    }
}

void CMyTank::DrawTankBody()
{
    /*绘制坦克主体*/
    fillrectangle(m_Pos.GetX() - 6, m_Pos.GetY() - 6, m_Pos.GetX() + 6, m_Pos.GetY() + 6);

    /*绘制履带*/
    switch (m_dir)
    {
    case UP:
    case DOWN:
        fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetStartPoint().GetY(),
            m_RectSphere.GetStartPoint().GetX() + 4, m_RectSphere.GetEndPoint().GetY());
        
        fillrectangle(m_RectSphere.GetEndPoint().GetX() - 4, m_RectSphere.GetStartPoint().GetY(),
            m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetEndPoint().GetY());
        break;
    case LEFT:
    case RIGHT:
        fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetStartPoint().GetY(),
            m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetStartPoint().GetY() + 4) ;

        fillrectangle(m_RectSphere.GetStartPoint().GetX() , m_RectSphere.GetEndPoint().GetY() - 4,
            m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetEndPoint().GetY());
        break;
    default:
        break;
    }

}
