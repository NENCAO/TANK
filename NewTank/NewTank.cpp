// NewTank.cpp : 定义控制台应用程序的入口点。
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

#define MAX_TANK 5 //最大敌人数

//敌人坦克list
std::list<CTank*> ListETank;

//敌人子弹list
std::list<CMyObject*> ListETankBullets;
//我的子弹list
std::list<CMyObject*> ListMyBullets;

//砖块list
std::list<CItem*> ListBrick;
//铁list
std::list<CItem*> ListIron;
//草list
std::list<CItem*> ListGrass;
//海list
std::list<CItem*> ListSea;
//老家list
std::list<CItem*> ListMatrix;

CMyTank *pMyTank = new CMyTank;

bool bLoop = true;  //游戏主循环
int nLife = 3;      //生命
int nScore = 0;     //游戏得分

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

    SelectMap(); //模式选择

    bool bSkip = false;//游戏暂停

    /*图片的指针*/
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
            //空格键
            case 32:
                if (bSkip) { break; }
                pMyTank->Shoot(ListMyBullets);
                break;
            /*暂停  Enter键*/
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
            /*退出程序  ESC键*/
            case 27:
                bLoop = false;
                break;
            /*开启作弊模式*/
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
            CheckCrash();        //子弹碰撞检测
            CheckTankCrash();    //坦克碰撞检测

            //putimage(200, 200, &pPause);
            /*显示分数*/
            TCHAR Score[5];
            _stprintf(Score, _T("得分:%d"), nScore);
            outtextxy(680, 100, Score);

            TCHAR Life[2];
            _stprintf(Life, _T("生命:%d"), nLife);
            outtextxy(680, 130, Life);


            /*显示操作指南*/
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

            /*遍历链表 显示海*/
            for (std::list<CItem*>::iterator it = ListSea.begin();
                it != ListSea.end(); )
            {
                (*it)->Display();
                it++;
            }

            /*遍历链表 让每个坦克都执行一次*/
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

            /*遍历链表 让每个子弹都执行一次 消失的子弹就再见*/
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

                //必须写到这里 不然 it会指向一个没有的地方
                it++;
            }
            /*自己发射的也要遍历*/
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

                //必须写到这里 不然 it会指向一个没有的地方
                it++;
            }


            /*遍历链表 显示砖块*/
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

            /*遍历链表 显示铁*/
            for (std::list<CItem*>::iterator it = ListIron.begin();
                it != ListIron.end(); )
            {
                (*it)->Display();
                it++;
            }

            /*遍历链表 显示草*/
            for (std::list<CItem*>::iterator it = ListGrass.begin();
                it != ListGrass.end(); )
            {
                (*it)->Display();
                it++;
            }

            /*遍历链表 显示老家*/
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
                EndBatchDraw(); //如果不执行缓冲刷新 后面的图可能读不出来
                break;
            }
            pMyTank = new CMyTank;
        }
        EndBatchDraw();
    }

    putimage(200, 200, &pOver);

    //销毁
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

/*检测子弹碰到东西*/
void CheckCrash()
{
    /*我方子弹打中敌人坦克*/
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

    /*敌人打中我方坦克*/
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

    /*我方子弹和敌人子弹抵消*/
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

    /*我方子弹打中砖块*/
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

    /*敌方子弹打中砖块*/
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

    /*我方子弹打中铁*/
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

    /*敌方子弹打中铁*/
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

    /*敌方子弹打中老家*/
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

    /*我方子弹打中老家*/
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

/*检测敌人坦克的碰撞*/
void CheckTankCrash()
{
    //坦克间的碰撞
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

    //碰到我方坦克
    for (std::list<CTank*>::iterator it = ListETank.begin();
        it != ListETank.end(); it++)
    {
        if (COverLap::CheckTankInterSect((*it)->GetSphere(), pMyTank->GetSphere()))
        {
            (*it)->SetCanmove(false);
            (*it)->Move();
        }
    }

    //碰到砖
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

    //碰到铁
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


    //碰到海
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
    //碰到老家
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

/*玩家碰撞检测*/
bool MyTankCrash()
{
    //碰到其他坦克
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

    //碰到砖块
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

    //碰到铁
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

    //碰到海
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

    //碰到老家
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

/*自定义地图*/
void CustomMap()
{
    MOUSEMSG m;		// 定义鼠标消息

    bool temp = true;
    int Goods = 0;
    TCHAR  Sea[]    = _T("海");
    TCHAR  Grass[]  = _T("草");
    TCHAR  Brick[]  = _T("砖");
    TCHAR  Iron[]   = _T("铁");  
    TCHAR  Str1[]   = _T("        鼠标左键放置物体");
    TCHAR  Str2[]   = _T("    鼠标中键更换物体种类");
    TCHAR  Str3[]   = _T("鼠标右键结束放置开始游戏");
    TCHAR  Str4[] = _T  ("按键盘S键保存当前的地图");
    //创建老家
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
        /*遍历链表 显示老家*/
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
        /*遍历链表 显示砖块*/
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

        /*遍历链表 显示铁*/
        for (std::list<CItem*>::iterator it = ListIron.begin();
            it != ListIron.end(); )
        {
            (*it)->Display();
            it++;
        }

        /*遍历链表 显示草*/
        for (std::list<CItem*>::iterator it = ListGrass.begin();
            it != ListGrass.end(); )
        {
            (*it)->Display();
            it++;
        }

        /*遍历链表 显示海*/
        for (std::list<CItem*>::iterator it = ListSea.begin();
            it != ListSea.end(); )
        {
            (*it)->Display();
            it++;
        }

        /*打印字符串*/
        outtextxy(200, 250, Str1);
        outtextxy(200, 250 + 2*textheight(Str1), Str2);
        outtextxy(200, 250 + 2*(textheight(Str1) + textheight(Str2)), Str3);
        outtextxy(200, 250 + 2*(textheight(Str1) + textheight(Str2) + textheight(Str3)), Str4);

        // 获取一条鼠标消息
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
            Goods = (++Goods) % 4; //物体类型
            break;
        case WM_RBUTTONUP:
            temp = false;	// 按鼠标右键退出画图
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
                LoadMap();  //读取地图 读完进入编辑模式
            case'w':
            case'W':
                CustomMap();//自定义地图
            case 13:
                Temp = false;
            default:
                break;
            }
        }

        TCHAR  Str1[] = _T("D键读取保存的地图");
        TCHAR  Str2[] = _T("W键进入地图编辑模式");
        /*打印字符串*/
        outtextxy(200, 250, Str1);
        outtextxy(200, 250 + 2 * textheight(Str1), Str2);
    }

}

void StoreMap()
{
    size_t nCount = 0; //计数器
    std::ofstream outFile("customMap.dat", std::ios::out | std::ios::binary);

    //存储海的坐标信息
    nCount = ListSea.size();                                    //存储海的个数 作为读取的依据
    outFile.write((char*)&nCount, sizeof(CMyPoint));            //写入个数
    for (std::list<CItem*>::iterator it = ListSea.begin();      //写入坐标
        it != ListSea.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    //存储砖的坐标信息
    nCount = ListBrick.size();                                   //存储砖的个数 作为读取的依据
    outFile.write((char*)&nCount, sizeof(CMyPoint));             //写入个数
    for (std::list<CItem*>::iterator it = ListBrick.begin();
        it != ListBrick.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    //存储草的坐标信息
    nCount = ListGrass.size();                                   //存储草的个数 作为读取的依据
    outFile.write((char*)&nCount, sizeof(CMyPoint));             //写入个数
    for (std::list<CItem*>::iterator it = ListGrass.begin();
        it != ListGrass.end(); it++)
    {
        outFile.write((char*)&(*it)->GetPoint(), sizeof(CMyPoint));
    }

    //存储铁的坐标信息
    nCount = ListIron.size();                                   //存储铁的个数 作为读取的依据
    outFile.write((char*)&nCount, sizeof(CMyPoint));             //写入个数
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
    int nCount = 0;  //计数器
    int nSeek = 0;   //文件流读取偏移
    CMyPoint Ponit;  //接收器
    std::ifstream inFile("customMap.dat", std::ios::in | std::ios::binary);
    if (!inFile) 
    {
        return;
        //没打开直接正常编辑
    }

    inFile.read((char*)&nCount, sizeof(int));   //读取海的方块个数
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //设定偏移值
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListSea.push_back(new CSea(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }

    inFile.read((char*)&nCount, sizeof(int));   //读取砖块的方块个数
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //设定偏移值
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListBrick.push_back(new CBrick(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }

    inFile.read((char*)&nCount, sizeof(int));   //读取草方块个数
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //设定偏移值
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListGrass.push_back(new CGrass(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }


    inFile.read((char*)&nCount, sizeof(int));   //读取铁方块个数
    nSeek += 8;
    inFile.seekg(nSeek, std::ios::beg);         //设定偏移值
    for (int i = 0; i < nCount; i++)
    {
        inFile.read((char*)&Ponit, sizeof(CMyPoint));
        ListIron.push_back(new CIron(Ponit.GetX(), Ponit.GetY()));
        nSeek += sizeof(CMyPoint);
    }

    inFile.close();
}