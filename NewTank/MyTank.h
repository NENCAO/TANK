#pragma once
#include "Tank.h"
class CMyTank :
    public CTank
{
public:
    CMyTank ()
    {
        m_Pos.SetX(200);
        m_Pos.SetY(550);
        m_dir = Dir::UP;

        this->CalculateSphere();
        m_color = YELLOW;
        m_step = 3;
        m_bDisapper = false;
        m_bCanMove = true;
        b_Cheat = false;
    }
    ~CMyTank();

    void SetDir(Dir dir);             //��������
    virtual void Display();           //��ʾ

    virtual void MoveUp();            //�ƶ�
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    virtual void Move();            //û�� �Լ���̹�˲���Ҫ�Զ���
    void Shoot(std::list<CMyObject*>& LstBullets); //���
    virtual CMyRect GetSphere() { return m_RectSphere; }

public:
    bool b_Cheat;                   //���׿���
protected:
    void CalculateSphere();         //������ռ�����С
    void DrawTankBody();

};

