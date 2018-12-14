#pragma once
#include "MyObject.h"
class CBullet :
    public CMyObject
{
public:
    CBullet();
    ~CBullet();

    CBullet(CMyPoint,Dir dir, COLORREF color);
    virtual void Display();  //�ڵ�ͼ�ϻ���
    virtual void Move();     //�Զ��ƶ�

    virtual void MoveUp();   //�ƶ�
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();
    virtual bool IsDisAppear() { return m_bDisapper; }
    virtual CMyRect GetSphere() { return m_RectSphere; }
    virtual void SetDisAppear(); //�����ӵ��Ƿ���ʧ
protected:
    /*�ӵ��ķ�Χ*/
    virtual void CalculateSphere();
};

