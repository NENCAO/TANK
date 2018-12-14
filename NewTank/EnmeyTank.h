#pragma once
#include "Tank.h"
class CEnmeyTank :
    public CTank
{
public:
    CEnmeyTank();
    ~CEnmeyTank();

    void SetDir(Dir dir);             //��������
    virtual void Display();           //��ʾ

    virtual void MoveUp();            //�ƶ�
    virtual void MoveDown();
    virtual void MoveLeft();
    virtual void MoveRight();

    void Move();                      //�õ���̹�˸��ݷ����ƶ�
    virtual CMyRect GetSphere() { return m_RectSphere; }
    void Shoot(std::list<CMyObject*>& LstBullets); //���

protected:
    void CalculateSphere();           //������ռ�����С
    void RandomDir();                 //�������
    void DrawTankBody();

protected:
    int m_StepCount;                  //�Ʋ���
    int m_ShootCount;
    int m_nCount;                     //���ɵص�ļƲ�
};

