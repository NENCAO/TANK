#pragma once
#include "Graphic.h"
class CItem
{
public:
    CItem();
    ~CItem();
    void Display();      //�ڵ�ͼ�ϻ���
    bool IsDisAppear();  //�ж��Ƿ���ʧ
    void SetDisAppear(); //���ö�����ʧ
    CMyRect GetSphere(); //��ȡ�����
    CMyPoint GetPoint(); //��ȡ����
protected:
    void CalculateSphere(); //������ռ�����С

protected:
    CMyPoint m_Pos;              //����
    CMyRect m_RectSphere;        //��ռ����
    COLORREF m_color;            //��ɫ
    bool m_bDisapper;            //�Ƿ���ʧ false����
};

