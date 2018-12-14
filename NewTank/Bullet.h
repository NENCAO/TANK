#pragma once
#include "MyObject.h"
class CBullet :
    public CMyObject
{
public:
    CBullet();
    ~CBullet();

    CBullet(CMyPoint,Dir dir, COLORREF color);
    virtual void Display();  //在地图上绘制
    virtual void Move();     //自动移动

    virtual void MoveUp();   //移动
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();
    virtual bool IsDisAppear() { return m_bDisapper; }
    virtual CMyRect GetSphere() { return m_RectSphere; }
    virtual void SetDisAppear(); //设置子弹是否消失
protected:
    /*子弹的范围*/
    virtual void CalculateSphere();
};

