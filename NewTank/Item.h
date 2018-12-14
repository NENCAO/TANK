#pragma once
#include "Graphic.h"
class CItem
{
public:
    CItem();
    ~CItem();
    void Display();      //在地图上绘制
    bool IsDisAppear();  //判断是否消失
    void SetDisAppear(); //设置对象消失
    CMyRect GetSphere(); //获取区域点
    CMyPoint GetPoint(); //获取坐标
protected:
    void CalculateSphere(); //计算所占区域大小

protected:
    CMyPoint m_Pos;              //坐标
    CMyRect m_RectSphere;        //所占区域
    COLORREF m_color;            //颜色
    bool m_bDisapper;            //是否消失 false存在
};

