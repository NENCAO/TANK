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

    /*����=�� ���������յ��λ��*/
    CMyRect &operator = (const CMyRect &Rect)
    {
        m_SrartPonit = Rect.GetStartPoint();
        m_EndPoint = Rect.GetEndPoint();

        return *this;
    }

    void Set(const CMyPoint pStart, const CMyPoint pEnd);
    void Set(int x1, int y1 ,int x2 ,int y2);

    void SetStartPonit(const CMyPoint p);   //�������Ͻǵ�����
    void SetEndPonit(const CMyPoint p);    //�������½ǵ�����

    CMyPoint GetStartPoint() const;  //EasyX�����ֵ�ܶ඼��const��
    CMyPoint GetEndPoint() const;    //���ӻᱨ��

    int GetWidth();                 //��ȡ���
    int GetHeight();                //��ȡ�߶�

    CMyPoint GetTRPoint();      //��ȡ���Ͻ�����
    CMyPoint GetBLPoint();      //��ȡ���½�����

private:
    void Check();           //�������ʱ���λ�÷��� ��������

    CMyPoint m_SrartPonit;    //���ε����Ͻ�
    CMyPoint m_EndPoint;      //���ε����½�
};

