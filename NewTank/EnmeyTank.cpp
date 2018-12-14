#include "stdafx.h"
#include "EnmeyTank.h"
#include "Bullet.h"

#define MAX_STEP 12 //转弯步数

CEnmeyTank::CEnmeyTank()
{
    int x = (rand() % (CGraphic::GetBattleGround().GetWidth() - 50)) + 50;
    if (x % 25 > 13)
    {
        x = x + 25 - x % 25;
    }
    else
    {
        x = x - x % 25;
    }
    m_Pos.SetX(x);
    m_Pos.SetY(20);
    m_step = rand() % 2 + 1;

    m_color = 1 == m_step? WHITE : LIGHTGREEN;
    m_dir = Dir::DOWN;
    this->CalculateSphere();
    m_StepCount = 0;
    m_bDisapper = false;
    m_bCanMove = true;
    m_ShootCount = 0;
}


CEnmeyTank::~CEnmeyTank()
{
}

/*坦克移动的方向*/
void CEnmeyTank::SetDir(Dir dir)
{
    m_dir = dir;
}

/*坦克的显示*/
void CEnmeyTank::Display()
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

void CEnmeyTank::MoveUp()
{
    SetDir(Dir::UP);
    if (m_Pos.GetY() - m_step - 12 < BATTEL_GROUND_Y1)
    {
        return;
    }

    m_Pos.SetY(m_Pos.GetY() - m_step);
    CalculateSphere();
}

void CEnmeyTank::MoveDown()
{
    SetDir(Dir::DOWN);
    if (m_Pos.GetY() + m_step + 12 > BATTEL_GROUND_Y2)
    {
        return;
    }

    m_Pos.SetY(m_Pos.GetY() + m_step);
    CalculateSphere();
}

void CEnmeyTank::MoveLeft()
{
    SetDir(Dir::LEFT);
    if (m_Pos.GetX() - m_step - 12 < BATTEL_GROUND_X1)
    {
        return;
    }

    m_Pos.SetX(m_Pos.GetX() - m_step);
    CalculateSphere();
}

void CEnmeyTank::MoveRight()
{
    SetDir(Dir::RIGHT);
    if (m_Pos.GetX() + m_step + 12 > BATTEL_GROUND_X2)
    {
        return;
    }

    m_Pos.SetX(m_Pos.GetX() + m_step);
    CalculateSphere();
}

void CEnmeyTank::Move()
{
    //if (!Canmove())
    //{
    //    switch (m_dir)
    //    {
    //    case UP:
    //        m_dir = DOWN;
    //        break;
    //    case DOWN:
    //        m_dir = UP;
    //        break;
    //    case LEFT:
    //        m_dir = RIGHT;
    //        break;
    //    case RIGHT:
    //        m_dir = LEFT;
    //        break;
    //    default:
    //        break;
    //    }
    //    SetCanmove(true);
    //}
    switch (m_dir)
    {
    case UP:
        if (!Canmove())
        {
            SetCanmove(true);
            MoveDown();
            SetDir(DOWN);
            break;
        }
        MoveUp();
        break;
    case DOWN:
        if (!Canmove())
        {
            SetCanmove(true);
            MoveUp();
            SetDir(UP);
            break;
        }
        MoveDown();
        break;
    case LEFT:
        if (!Canmove())
        {
            SetCanmove(true);
            MoveRight();
            SetDir(RIGHT);
            break;
        }
        MoveLeft();
        break;
    case RIGHT:
        if (!Canmove())
        {
            SetCanmove(true);
            MoveLeft();
            SetDir(LEFT);
            break;
        }
        MoveRight();
        break;
    default:
        break;
    }

    m_StepCount++;
    if (rand() % 10 == 0) //自动发子弹
    {
        m_AutoShoot = true;
    }

    if (//MAX_STEP <= m_StepCount
        rand() % 20 == 0
        )//转弯
    {
        m_StepCount = 0;
        this->RandomDir();
    }

}

void CEnmeyTank::Shoot(std::list<CMyObject*>& LstBullets)
{
    //if (LstBullets.size() > 16)
    //{
    //    return;
    //}
    CBullet* pBullet = new CBullet(m_Pos, m_dir, m_color);
    LstBullets.push_back(pBullet);
    m_AutoShoot = false;
}

/*设置坦克的区域 并以此来画履带*/
void CEnmeyTank::CalculateSphere()
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

/*转向*/
void CEnmeyTank::RandomDir()
{
    Dir dir = (Dir)(Dir::UP + rand() % 4);
    SetDir(dir);
}


void CEnmeyTank::DrawTankBody()
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
            m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetStartPoint().GetY() + 4);

        fillrectangle(m_RectSphere.GetStartPoint().GetX(), m_RectSphere.GetEndPoint().GetY() - 4,
            m_RectSphere.GetEndPoint().GetX(), m_RectSphere.GetEndPoint().GetY());
        break;
    default:
        break;
    }
}