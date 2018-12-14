#pragma once
#include "Tank.h"
class CMyTank :
    public CTank
{
public:
    CMyTank ()
    {
        m_Pos.SetX(200);
        m_Pos.SetY(550);
        m_dir = Dir::UP;

        this->CalculateSphere();
        m_color = YELLOW;
        m_step = 3;
        m_bDisapper = false;
        m_bCanMove = true;
        b_Cheat = false;
    }
    ~CMyTank();

    void SetDir(Dir dir);             //按键方向
    virtual void Display();           //显示

    virtual void MoveUp();            //移动
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    virtual void Move();            //没用 自己的坦克不需要自动走
    void Shoot(std::list<CMyObject*>& LstBullets); //射击
    virtual CMyRect GetSphere() { return m_RectSphere; }

public:
    bool b_Cheat;                   //作弊开关
protected:
    void CalculateSphere();         //计算所占区域大小
    void DrawTankBody();

};

