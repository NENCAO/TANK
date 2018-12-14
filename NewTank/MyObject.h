#pragma once
#include "Graphic.h"

enum Dir {UP,DOWN,LEFT,RIGHT};

class CMyObject
{
public:
    CMyObject();
    ~CMyObject();

    virtual void Display() = 0;  //�ڵ�ͼ�ϻ���
    virtual void Move() = 0;     //�Զ��ƶ�

    virtual void MoveUp() = 0;   //�ƶ�
    virtual void MoveDown() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveRight() = 0;

    virtual bool IsDisAppear() = 0;   //�ж��Ƿ���ʧ
    virtual CMyRect GetSphere() = 0;    //�������������
    virtual void SetDisAppear() = 0; //���ö�����ʧ
protected:
    virtual void CalculateSphere() = 0; //������ռ�����С

protected:
    CMyPoint m_Pos;              //����
    CMyRect m_RectSphere;        //��ռ����

    COLORREF m_color;            //��ɫ

    Dir m_dir;                   //����
    int m_step;                  //ÿ������

    bool m_bDisapper;            //�Ƿ����

};

