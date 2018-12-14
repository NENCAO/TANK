#include "stdafx.h"
#include "Tank.h"


CTank::CTank()
{
}


CTank::~CTank()
{
}

void CTank::Display()
{
}

void CTank::MoveUp()
{
}

void CTank::MoveDown()
{
}

void CTank::MoveLeft()
{
}

void CTank::MoveRight()
{
}

void CTank::Move()
{
}

bool CTank::IsDisAppear()
{
    return m_bDisapper;
}

//void CTank::Shoot(std::list<CMyObject*>& LstBullets)
//{
//}

void CTank::SetDisAppear()
{
    m_bDisapper = true;
}

void CTank::CalculateSphere()
{
}

CMyRect CTank::GetSphere()
{
    return CMyRect();
}

void CTank::SetCanmove(bool bMove)
{
    m_bCanMove = bMove;
}

bool CTank::Canmove()
{
    return m_bCanMove;
}
