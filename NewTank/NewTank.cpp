// NewTank.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#pragma warning(disable:4996)
#include "Graphic.h"
#include "MyTank.h"
#include "EnmeyTank.h"
#include "OverLap.h"
#include "Brick.h"
#include "Iron.h"
#include "Grass.h"
#include "Sea.h"
#include "Matrix.h"

#define MAX_TANK 5 //��������

//����̹��list
std::list<CTank*> ListETank;

//�����ӵ�list
std::list<CMyObject*> ListETankBullets;
//�ҵ��ӵ�list
std::list<CMyObject*> ListMyBullets;

//ש��list
std::list<CItem*> ListBrick;
//��list
std::list<CItem*> ListIron;
//��list
std::list<CItem*> ListGrass;
//��list
std::list<CItem*> ListSea;
//�ϼ�list
std::list<CItem*> ListMatrix;

CMyTank *pMyTank = new CMyTank;

bool bLoop = true;  //��Ϸ��ѭ��
int nLife = 3;      //����
int nScore = 0;     //��Ϸ�÷�

void CheckCrash();
void CheckTankCrash();
bool MyTankCrash();
void CustomMap();
void StoreMap();
void LoadMap();
void SelectMap();

int main()
{
    CGraphic::Create();
    cleardevice();
    CGraphic::DrawBattleGround();
    ListETank.clear();
    ListETankBullets.clear();
    ListMyBullets.clear();
    ListBrick.clear();
    ListIron.clear();
    ListGrass.clear();
    ListSea.clear();
    ListMatrix.clear();

    srand(time(NULL));

    SelectMap(); //ģʽѡ��

    bool bSkip = false;//��Ϸ��ͣ

    /*ͼƬ��ָ��*/
    IMAGE pPause;
    IMAGE pOver;
    IMAGE pHit;
    loadimage(&pOver, _T("gameover.jpg"));
    loadimage(&pPause, _T("pause.jpg"));
    loadimage(&pHit, _T("operate.jpg"));

    while (bLoop)
    {

        if( ListETank.size() < MAX_TANK)
        {
            ListETank.push_back(new CEnmeyTank());
        }

        if (_kbhit() && nullptr != pMyTank)
        {
            int key = _getch();

            switch (key)
            {
            case'w':
                if (bSkip) { break; }
                pMyTank->MoveUp();
                if (MyTankCrash())
                {
                    pMyTank->MoveDown();
                    pMyTank->SetDir(UP);
                    break;
                }
                break;
            case's':
                if (bSkip) { break; }
                pMyTank->MoveDown();
                if (MyTankCrash())
                {
                    pMyTank->MoveUp();
                    pMyTank->SetDir(DOWN);
                    break;
                }
                break;
            case'a':
                if (bSkip) { break; }
                pMyTank->MoveLeft();
                if (MyTankCrash())
                {
                    pMyTank->MoveRight();
                    pMyTank->SetDir(LEFT);
                    break;
                }
                break;
            case'd':
                if (bSkip) { break; }
                pMyTank->MoveRight();
                if (MyTankCrash())
                {
                    pMyTank->MoveLeft();
                    pMyTank->SetDir(RIGHT);
                    break;
                }
                break;
            //�ո��
            case 32:
                if (bSkip) { break; }
                pMyTank->Shoot(ListMyBullets);
                break;
            /*��ͣ  Enter��*/
            case 13:
                if (bSkip)
                {
                    bSkip = false;
                }
                else
                {
                    bSkip = true;
                   // 
                    putimage(200, 200, &pPause);
                }
                break;
            /*�˳�����  ESC��*/
            case 27:
                bLoop = false;
                break;
            /*��������ģʽ*/
            case 'q':
            case 'Q':
                pMyTank->b_Cheat = true;
                break;
            default:
                break;
            }
        }

        BeginBatchDraw();
        if (!bSkip)
        {
            cleardevice();
            CheckCrash();        //�ӵ���ײ���
            CheckTankCrash();    //̹����ײ���

            //putimage(200, 200, &pPause);
            /*��ʾ����*/
            TCHAR Score[5];
            _stprintf(Score, _T("�÷�:%d"), nScore);
            outtextxy(680, 100, Score);

            TCHAR Life[2];
            _stprintf(Life, _T("����:%d"), nLife);
            outtextxy(680, 130, Life);


            /*��ʾ����ָ��*/
            //loadimage(pHit, _T("operate.jpg"));
            putimage(620, 200, &pHit);

            CGraphic::DrawBattleGround();

            if (nullptr != pMyTank)
            {
                pMyTank->Display();

                if (pMyTank->IsDisAppear())
                {
                    delete pMyTank;
                    pMyTank = nullptr;
                }
            }

            /*�������� ��ʾ��*/
            for (std::list<CItem*>::iterator it = ListSea.begin();
                it != ListSea.end(); )
            {
                (*it)->Display();
                it++;
            }

            /*�������� ��ÿ��̹�˶�ִ��һ��*/
            for (std::list<CTank*>::iterator it = ListETank.begin();
                it != ListETank.end(); )
            {
                (*it)->Move();

                if (true == (*it)->IsDisAppear())
                {
                    delete *it;
                    it = ListETank.erase(it);
                    continue;
                }
                (*it)->Display();
                if ((*it)->AutoShoot())
                {
                    CEnmeyTank*p = (CEnmeyTank*)*it;
                    p->Shoot(ListETankBullets);
                }
                it++;
            }

            /*�������� ��ÿ���ӵ���ִ��һ�� ��ʧ���ӵ����ټ�*/
            for (std::list<CMyObject*>::iterator it = ListETankBullets.begin();
                it != ListETankBullets.end(); )
            {
                (*it)->Move();
                if (true == (*it)->IsDisAppear())
                {
                    delete *it;
                    it = ListETankBullets.erase(it);
                    continue;
                }

                (*it)->Display();

                //����д������ ��Ȼ it��ָ��һ��û�еĵط�
                it++;
            }
            /*�Լ������ҲҪ����*/
            for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
                it != ListMyBullets.end(); )
            {
                (*it)->Move();
                if (true == (*it)->IsDisAppear())
                {
                    delete *it;
                    it = ListMyBullets.erase(it);
                    continue;
                }

                (*it)->Display();

                //����д������ ��Ȼ it��ָ��һ��û�еĵط�
                it++;
            }


            /*�������� ��ʾש��*/
            for (std::list<CItem*>::iterator it = ListBrick.begin();
                it != ListBrick.end(); )
            {
                if (true == (*it)->IsDisAppear())
                {
                    delete *it;
                    it = ListBrick.erase(it);
                    continue;
                }
                (*it)->Display();
                it++;
            }

            /*�������� ��ʾ��*/
            for (std::list<CItem*>::iterator it = ListIron.begin();
                it != ListIron.end(); )
            {
                (*it)->Display();
                it++;
            }

            /*�������� ��ʾ��*/
            for (std::list<CItem*>::iterator it = ListGrass.begin();
                it != ListGrass.end(); )
            {
                (*it)->Display();
                it++;
            }

            /*�������� ��ʾ�ϼ�*/
            for (std::list<CItem*>::iterator it = ListMatrix.begin();
                it != ListMatrix.end(); )
            {
                if (true == (*it)->IsDisAppear())
                {
                    delete *it;
                    it = ListMatrix.erase(it);
                    continue;
                }
                (*it)->Display();
                it++;
            }
        }
        Sleep(10); 

        if (nullptr == pMyTank)
        {
            if (0 == --nLife)
            {
                bLoop = false;
                EndBatchDraw(); //�����ִ�л���ˢ�� �����ͼ���ܶ�������
                break;
            }
            pMyTank = new CMyTank;
        }
        EndBatchDraw();
    }

    putimage(200, 200, &pOver);

    //����
    for (std::list<CTank*>::iterator it = ListETank.begin();
        it != ListETank.end(); it++)
    {
        delete *it;
    }
    ListETank.clear();

    for (std::list<CMyObject*>::iterator it = ListETankBullets.begin();
        it != ListETankBullets.end(); it++)
    {
        delete *it;
    }
    ListETankBullets.clear();

    for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
        it != ListMyBullets.end(); it++)
    {
        delete *it;
    }
    ListMyBullets.clear();

    for (std::list<CItem*>::iterator it = ListBrick.begin();
        it != ListBrick.end(); it++)
    {
        delete *it;
    }
    ListBrick.clear();

    for (std::list<CItem*>::iterator it = ListIron.begin();
        it != ListIron.end(); it++)
    {
        delete *it;
    }
    ListIron.clear();

    for (std::list<CItem*>::iterator it = ListGrass.begin();
        it != ListGrass.end(); it++)
    {
        delete *it;
    }
    ListGrass.clear();

    for (std::list<CItem*>::iterator it = ListSea.begin();
        it != ListSea.end(); it++)
    {
        delete *it;
    }
    ListSea.clear();

    for (std::list<CItem*>::iterator it = ListMatrix.begin();
        it != ListMatrix.end(); it++)
    {
        delete *it;
    }
    ListMatrix.clear();

    if (nullptr != pMyTank)
    {
        delete pMyTank;
        pMyTank = nullptr;
    }

    //loadimage(pOver, _T("gameover.jpg"));
    putimage(200, 200, &pOver);

    //if (nullptr != pOver)
    //{
    //    delete pOver;
    //    &pOver = nullptr;
    //}

    //if (nullptr != pHit)
    //{
    //    delete &pHit;
    //    pHit = nullptr;
    //}

    //if (nullptr != pPause)
    //{
    //    delete pPause;
    //    pPause = nullptr;
    //}
    Sleep(3000);

    CGraphic::Destroy();
    system("pause");
    return 0;
}

/*����ӵ���������*/
void CheckCrash()
{
    /*�ҷ��ӵ����е���̹��*/
    for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
        it != ListMyBullets.end(); it++)
    {
        for (std::list<CTank*>::iterator it2 = ListETank.begin();
            it2 != ListETank.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it2)->SetDisAppear();
                (*it)->SetDisAppear();
                nScore += 10;
            }
        }
    }

    /*���˴����ҷ�̹��*/
    for (std::list<CMyObject*>::iterator it = ListETankBullets.begin();
        it != ListETankBullets.end(); it++)
    {
        if (nullptr != pMyTank)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
            {
                pMyTank->SetDisAppear();
                (*it)->SetDisAppear();
            }
        }
    }

    /*�ҷ��ӵ��͵����ӵ�����*/
    for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
        it != ListMyBullets.end(); it++)
    {
        for (std::list<CMyObject*>::iterator it2 = ListETankBullets.begin();
            it2 != ListETankBullets.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it)->SetDisAppear();
                (*it2)->SetDisAppear();
            }
        }
    }

    /*�ҷ��ӵ�����ש��*/
    for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
        it != ListMyBullets.end(); it++)
    {
        for (std::list<CItem*>::iterator it2 = ListBrick.begin();
            it2 != ListBrick.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it)->SetDisAppear();
                (*it2)->SetDisAppear();
            }
        }
    }

    /*�з��ӵ�����ש��*/
    for (std::list<CMyObject*>::iterator it = ListETankBullets.begin();
        it != ListETankBullets.end(); it++)
    {
        for (std::list<CItem*>::iterator it2 = ListBrick.begin();
            it2 != ListBrick.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it)->SetDisAppear();
                (*it2)->SetDisAppear();
            }
        }
    }

    /*�ҷ��ӵ�������*/
    for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
        it != ListMyBullets.end(); it++)
    {
        for (std::list<CItem*>::iterator it2 = ListIron.begin();
            it2 != ListIron.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it)->SetDisAppear();
            }
        }
    }

    /*�з��ӵ�������*/
    for (std::list<CMyObject*>::iterator it = ListETankBullets.begin();
        it != ListETankBullets.end(); it++)
    {
        for (std::list<CItem*>::iterator it2 = ListIron.begin();
            it2 != ListIron.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it)->SetDisAppear();
            }
        }
    }

    /*�з��ӵ������ϼ�*/
    for (std::list<CMyObject*>::iterator it = ListETankBullets.begin();
        it != ListETankBullets.end(); it++)
    {
        for (std::list<CItem*>::iterator it2 = ListMatrix.begin();
            it2 != ListMatrix.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                bLoop = false;
                (*it)->SetDisAppear();
                (*it2)->SetDisAppear();
            }
        }
    }

    /*�ҷ��ӵ������ϼ�*/
    for (std::list<CMyObject*>::iterator it = ListMyBullets.begin();
        it != ListMyBullets.end(); it++)
    {
        for (std::list<CItem*>::iterator it2 = ListMatrix.begin();
            it2 != ListMatrix.end(); it2++)
        {
            if (COverLap::CheckInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                bLoop = false;
                (*it)->SetDisAppear();
                (*it2)->SetDisAppear();
            }
        }
    }
}

/*������̹�˵���ײ*/
void CheckTankCrash()
{
    //̹�˼����ײ
    for (std::list<CTank*>::iterator it = ListETank.begin();
        it != ListETank.end();it++)
    {
        for (std::list<CTank*>::iterator it2 = ListETank.begin();
            it2 != ListETank.end(); it2++)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), (*it2)->GetSphere()) && it != it2)
            {
                (*it)->SetCanmove(false);
                (*it)->Move();
            }
        }
    }

    //�����ҷ�̹��
    for (std::list<CTank*>::iterator it = ListETank.begin();
        it != ListETank.end(); it++)
    {
        if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
        {
            (*it)->SetCanmove(false);
            (*it)->Move();
        }
    }

    //����ש
    for (std::list<CItem*>::iterator it = ListBrick.begin();
        it != ListBrick.end(); it++)
    {
        for (std::list<CTank*>::iterator it2 = ListETank.begin();
            it2 != ListETank.end(); it2++)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), (*it2)->GetSphere()))
            {
                (*it2)->SetCanmove(false);
                (*it2)->Move();
            }
        }
    }

    //������
    for (std::list<CItem*>::iterator it = ListIron.begin();
        it != ListIron.end(); it++)
    {
        for (std::list<CTank*>::iterator it2 = ListETank.begin();
            it2 != ListETank.end(); it2++)
        {
            if (COverLap::CheckTankInterSect((*it2)->GetSphere(), (*it)->GetSphere()))
            {
                (*it2)->SetCanmove(false);
                (*it2)->Move();
            }
        }
    }


    //������
    for (std::list<CItem*>::iterator it = ListSea.begin();
        it != ListSea.end(); it++)
    {
        for (std::list<CTank*>::iterator it2 = ListETank.begin();
            it2 != ListETank.end(); it2++)
        {
            if (COverLap::CheckTankInterSect((*it2)->GetSphere(), (*it)->GetSphere()))
            {
                (*it2)->SetCanmove(false);
                (*it2)->Move();
            }
        }
    }
    //�����ϼ�
    for (std::list<CItem*>::iterator it = ListMatrix.begin();
        it != ListMatrix.end(); it++)
    {
        for (std::list<CTank*>::iterator it2 = ListETank.begin();
            it2 != ListETank.end(); it2++)
        {
            if (COverLap::CheckTankInterSect((*it2)->GetSphere(), (*it)->GetSphere()))
            {
                (*it2)->SetCanmove(false);
                (*it2)->Move();
            }
        }
    }
}

/*�����ײ���*/
bool MyTankCrash()
{
    //��������̹��
    for (std::list<CTank*>::iterator it = ListETank.begin();
        it != ListETank.end(); it++)
    {
        if (nullptr != pMyTank)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
            {
                return true;
            }
        }
    }

    //����ש��
    for (std::list<CItem*>::iterator it = ListBrick.begin();
        it != ListBrick.end(); it++)
    {
        if (nullptr != pMyTank)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
            {
                return true;
            }
        }
    }

    //������
    for (std::list<CItem*>::iterator it = ListIron.begin();
        it != ListIron.end(); it++)
    {
        if (nullptr != pMyTank)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
            {
                return true;
            }
        }
    }

    //������
    for (std::list<CItem*>::iterator it = ListSea.begin();
        it != ListSea.end(); it++)
    {
        if (nullptr != pMyTank)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
            {
                return true;
            }
        }
    }

    //�����ϼ�
    for (std::list<CItem*>::iterator it = ListMatrix.begin();
        it != ListMatrix.end(); it++)
    {
        if (nullptr != pMyTank)
        {
            if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
            {
                return true;
            }
        }
    }
    return false;
}

/*�Զ����ͼ*/
void CustomMap()
{
    MOUSEMSG m;		// ���������Ϣ

    bool temp = true;
    int Goods = 0;
    TCHAR  Sea[]    = _T("��");
    TCHAR  Grass[]  = _T("��");
    TCHAR  Brick[]  = _T("ש");
    TCHAR  Iron[]   = _T("��");  
    TCHAR  Str1[]   = _T("        ��������������");
    TCHAR  Str2[]   = _T("    ����м�������������");
    TCHAR  Str3[]   = _T("����Ҽ��������ÿ�ʼ��Ϸ");
    TCHAR  Str4[] = _T  ("������S�����浱ǰ�ĵ�ͼ");
    //�����ϼ�
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            ListMatrix.push_back(new CMatrix(276 + (i * 24), 550 + (j * 24)));
        }
    }

    while (temp)
    {
        //TCHAR s[] = { '\0' };
        /*�������� ��ʾ�ϼ�*/
        for (std::list<CItem*>::iterator it = ListMatrix.begin();
            it != ListMatrix.end(); )
        {
            if (true == (*it)->IsDisAppear())
            {
                delete *it;
                it = ListMatrix.erase(it);
                continue;
            }
            (*it)->Display();
            it++;
        }
        /*�������� ��ʾש��*/
        for (std::list<CItem*>::iterator it = ListBrick.begin();
            it != ListBrick.end(); )
        {
            if (true == (*it)->IsDisAppear())
            {
                delete *it;
                it = ListBrick.erase(it);
                continue;
            }
            (*it)->Display();
            it++;
        }

        /*�������� ��ʾ��*/
        for (std::list<CItem*>::iterator it = ListIron.begin();
            it != ListIron.end(); )
        {
            (*it)->Display();
            it++;
        }

        /*�������� ��ʾ��*/
        for (std::list<CItem*>::iterator it = ListGrass.begin();
            it != ListGrass.end(); )
        {
            (*it)->Display();
            it++;
        }

        /*�������� ��ʾ��*/
        for (std::list<CItem*>::iterator it = ListSea.begin();
            it != ListSea.end(); )
        {
            (*it)->Display();
            it++;
        }

        /*��ӡ�ַ���*/
        outtextxy(200, 250, Str1);
        outtextxy(200, 250 + 2*textheight(Str1), Str2);
        outtextxy(200, 250 + 2*(textheight(Str1) + textheight(Str2)), Str3);
        outtextxy(200, 250 + 2*(textheight(Str1) + textheight(Str2) + textheight(Str3)), Str4);

        // ��ȡһ�������Ϣ
        m = GetMouseMsg();
        if (m.x % 25 > 13)
        {
            m.x = m.x + 25 - m.x % 25;
        }
        else
        {
            m.x = m.x - m.x % 25;
        }

        if (m.y % 25 > 13)
        {
            m.y = m.y + 25 - m.y % 25;
        }
        else
        {
            m.y = m.y - m.y % 25;
        }

        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            switch (Goods)
            {
            case 0:
                ListSea.push_back(new CSea(m.x, m.y));
                break;
            case 1:
                ListBrick.push_back(new CBrick(m.x, m.y));
                break;
            case 2:
                ListGrass.push_back(new CGrass(m.x, m.y));
                break;
            case 3:
                ListIron.push_back(new CIron(m.x, m.y));
                break;
            default:
                break;
            }

            break;
        case WM_MBUTTONUP:
            Goods = (++Goods) % 4; //��������
            break;
        case WM_RBUTTONUP:
            temp = false;	// ������Ҽ��˳���ͼ
        }

        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case 's':
            case 'S':
                StoreMap();
                printf("StoreMap\r\n");
                break;
            default:
                break;
            }
        }

        switch (Goods)
        {
        case 0:
            setfillcolor(LIGHTBLUE);
            fillrectangle(700, 100, 750, 150);
            outtextxy(720, 160, Sea);
            break;
        case 1:
            setfillcolor(DARKGRAY);
            fillrectangle(700, 100, 750, 150);
            outtextxy(720, 160, Brick);
            break;
        case 2:
            setfillcolor(GREEN);
            fillrectangle(700, 100, 750, 150);
            outtextxy(720, 160, Grass);
            break;
        case 3:
            setfillcolor(BLACK);
            fillrectangle(700, 100, 750, 150);
            outtextxy(720, 160, Iron);
            break;
        }
    }

}

void SelectMap()
{
    bool Temp = true;

    while (Temp)
    {
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case 'd':
            case 'D':
                LoadMap();  //��ȡ��ͼ �������༭ģʽ
            case'w':
            case'W':
                CustomMap();//�Զ����ͼ
            case 13:
                Temp = false;
            default:
                break;
            }
        }

        TCHAR  Str1[] = _T("D����ȡ����ĵ�ͼ");
        TCHAR  Str2[] = _T("W�������ͼ�༭ģʽ");
        /*��ӡ�ַ���*/
        outtextxy(200, 250, Str1);
        outtextxy(200, 250 + 2 * textheight(Str1), Str2);
    }

}

void StoreMap()
{
    size_t nCount = 0; //������
    std::ofstream outFile("customMap.dat", std::ios::out | std::ios::binary);

    //�洢����������Ϣ
    nCount = ListSea.size();                                    //�洢���ĸ��� ��Ϊ��ȡ������
    outFile.write((char*)&nCount, sizeof(CMyPoint));            //д�����
    for (std::list<CItem*>::iterator it = ListSea.begin();      //д������
        it != ListSea.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    //�洢ש��������Ϣ
    nCount = ListBrick.size();                                   //�洢ש�ĸ��� ��Ϊ��ȡ������
    outFile.write((char*)&nCount, sizeof(CMyPoint));             //д�����
    for (std::list<CItem*>::iterator it = ListBrick.begin();
        it != ListBrick.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    //�洢�ݵ�������Ϣ
    nCount = ListGrass.size();                                   //�洢�ݵĸ��� ��Ϊ��ȡ������
    outFile.write((char*)&nCount, sizeof(CMyPoint));             //д�����
    for (std::list<CItem*>::iterator it = ListGrass.begin();
        it != ListGrass.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    //�洢����������Ϣ
    nCount = ListIron.size();                                   //�洢���ĸ��� ��Ϊ��ȡ������
    outFile.write((char*)&nCount, sizeof(CMyPoint));             //д�����
    for (std::list<CItem*>::iterator it = ListIron.begin();
        it != ListIron.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    IMAGE *pStroe = new IMAGE;

    loadimage(pStroe, _T("Stroe.jpg"));
    putimage(200, 200, pStroe);
    Sleep(2000);
    outFile.close();
    if (nullptr != pStroe)
    {
        delete pStroe;
    }
}

void LoadMap()
{
    int nCount = 0;  //������
    int nSeek = 0;   //�ļ�����ȡƫ��
    CMyPoint Ponit;  //������
    std::ifstream inFile("customMap.dat", std::ios::in | std::ios::binary);
    if (!inFile) 
    {
        return;
        //û��ֱ�������༭
    }

    inFile.read((char*)&nCount, sizeof(int));   //��ȡ���ķ������
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //�趨ƫ��ֵ
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListSea.push_back(new CSea(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }

    inFile.read((char*)&nCount, sizeof(int));   //��ȡש��ķ������
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //�趨ƫ��ֵ
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListBrick.push_back(new CBrick(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }

    inFile.read((char*)&nCount, sizeof(int));   //��ȡ�ݷ������
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //�趨ƫ��ֵ
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListGrass.push_back(new CGrass(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }


    inFile.read((char*)&nCount, sizeof(int));   //��ȡ���������
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //�趨ƫ��ֵ
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListIron.push_back(new CIron(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }

    inFile.close();
}