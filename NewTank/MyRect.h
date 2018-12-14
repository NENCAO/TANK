#pragma once
#include"MyPoint.h"

class CMyRect
{
public:
    CMyRect(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0)
        : m_SrartPonit(x1, x2), m_EndPoint(x2, y2)
    {
    };

    CMyRect(const CMyPoint p1 , const CMyPoint p2)
        : m_SrartPonit(p1), m_EndPoint(p2)
    {
    };

    ~CMyRect();

    /*重载=号 方便后面接收点的位置*/
    CMyRect &operator = (const CMyRect &Rect)
    {
        m_SrartPonit = Rect.GetStartPoint();
        m_EndPoint = Rect.GetEndPoint();

        return *this;
    }

    void Set(const CMyPoint pStart, const CMyPoint pEnd);
    void Set(int x1, int y1 ,int x2 ,int y2);

    void SetStartPonit(const CMyPoint p);   //设置左上角的坐标
    void SetEndPonit(const CMyPoint p);    //设置右下角的坐标

    CMyPoint GetStartPoint() const;  //EasyX库接收值很多都是const的
    CMyPoint GetEndPoint() const;    //不加会报错

    int GetWidth();                 //获取宽度
    int GetHeight();                //获取高度

    CMyPoint GetTRPoint();      //获取右上角坐标
    CMyPoint GetBLPoint();      //获取左下角坐标

private:
    void Check();           //如果创建时点的位置反了 交换回来

    CMyPoint m_SrartPonit;    //矩形的左上角
    CMyPoint m_EndPoint;      //矩形的右下角
};

