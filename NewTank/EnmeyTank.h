#pragma once
#include "Tank.h"
class CEnmeyTank :
    public CTank
{
public:
    CEnmeyTank();
    ~CEnmeyTank();

    void SetDir(Dir dir);             //按键方向
    virtual void Display();           //显示

    virtual void MoveUp();            //移动
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    void Move();                      //让敌人坦克根据方向移动
    virtual CMyRect GetSphere() { return m_RectSphere; }
    void Shoot(std::list<CMyObject*>& LstBullets); //射击

protected:
    void CalculateSphere();           //计算所占区域大小
    void RandomDir();                 //随机方向
    void DrawTankBody();

protected:
    int m_StepCount;                  //计步器
    int m_ShootCount;
    int m_nCount;                     //生成地点的计步
};

