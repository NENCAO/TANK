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

    virtual void Display();  //��ʾ

    virtual void MoveUp();  //�ƶ�
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    virtual void Move();    //�����Զ��ƶ�

    virtual bool IsDisAppear(); //�ж��Ƿ���ʧ
    /*���*/
    //void Shoot(std::list<CMyObject*>& LstBullets);
    virtual void SetDisAppear(); //����̹����ʧ
    virtual CMyRect GetSphere();
    bool AutoShoot() { return m_AutoShoot; }
    void SetCanmove(bool bMove); //�Ƿ����ƶ�
    bool Canmove();
protected:
    virtual void CalculateSphere(); //������ռ�����С
    bool m_AutoShoot;               //�Զ��������
    bool m_bCanMove;                //�ܷ��ƶ�
};

