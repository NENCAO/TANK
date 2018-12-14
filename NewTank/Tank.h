#pragma once
#include "Graphic.h"
#include "MyObject.h"
#include <list>

class CTank
    : public CMyObject
{
public:
    CTank();
    ~CTank();

    virtual void Display();  //显示

    virtual void MoveUp();  //移动
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    virtual void Move();    //敌人自动移动

    virtual bool IsDisAppear(); //判断是否消失
    /*射击*/
    //void Shoot(std::list<CMyObject*>& LstBullets);
    virtual void SetDisAppear(); //设置坦克消失
    virtual CMyRect GetSphere();
    bool AutoShoot() { return m_AutoShoot; }
    void SetCanmove(bool bMove); //是否能移动
    bool Canmove();
protected:
    virtual void CalculateSphere(); //计算所占区域大小
    bool m_AutoShoot;               //自动射击开关
    bool m_bCanMove;                //能否移动
};

