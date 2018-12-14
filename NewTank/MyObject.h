#pragma once
#include "Graphic.h"

enum Dir {UP,DOWN,LEFT,RIGHT};

class CMyObject
{
public:
    CMyObject();
    ~CMyObject();

    virtual void Display() = 0;  //在地图上绘制
    virtual void Move() = 0;     //自动移动

    virtual void MoveUp() = 0;   //移动
    virtual void MoveDown() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;

    virtual bool IsDisAppear() = 0;   //判断是否消失
    virtual CMyRect GetSphere() = 0;    //返回区域的坐标
    virtual void SetDisAppear() = 0; //设置对象消失
protected:
    virtual void CalculateSphere() = 0; //计算所占区域大小

protected:
    CMyPoint m_Pos;              //坐标
    CMyRect m_RectSphere;        //所占区域

    COLORREF m_color;            //颜色

    Dir m_dir;                   //方向
    int m_step;                  //每步距离

    bool m_bDisapper;            //是否存在

};

