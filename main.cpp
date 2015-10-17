#include <iostream>
#include "myIrrlicht.h"
#include "receiverEvent.h"
#include "item.h"
#include "eqip.h"
#include "loli.h"
#include "loli_bot.h"
#include "mob.h"

using namespace std;

struct fps_
{
    irr::s32 framelimit;
    irr::s32 now;
    irr::u32 sceneStartTime;
    irr::u32 sceneSkipTime;

    fps_()
    {
        framelimit = 60;
        now = 0;
        sceneStartTime = 0;
        sceneSkipTime = 1000/framelimit;
    }

    bool schet(myIrrlicht_ *ir)
    {
        now = ir->device->getTimer()->getTime();
        if (now - sceneStartTime > sceneSkipTime)
        {
            sceneStartTime = ir->device->getTimer()->getTime();
            return true;
        }
        return false;
    }
};

bool knopkaBox(int x, int y, int xx, int yy, int mx, int my)
{
    if( mx<xx && mx>x && my<yy && my>y )
    {
        return true;
    }
    return false;
}

bool knopkaSphere(int x, int y, int r, int mx, int my)
{
    if( sqrt((mx-x)*(mx-x)+(my-y)*(my-y))<r )
    {
        return true;
    }
    return false;
}

struct myAnimatorSost//тут прописаны абсолютно все состояния анимации и эффектов
{

};

struct battleFunction
{
    void mobStroke(loli_ *lo, mob_ *mob)
    {
        lo->crash(mob->Fdamag);
    }

    bool mob_ai_0(loli_ *lo, mob_ *mob)
    {
        if(sqrt((lo->pX-mob->x)*(lo->pX-mob->x)+(lo->pY-mob->y)*(lo->pY-mob->y))>32)
        {
            if(mob->ap>0)
            {
                mob->step(lo->pX, lo->pY);
                mob->ap--;
                return true;
            }
        }
        else
        {
            if(mob->ap>8)
            {
                mobStroke(lo, mob);
                mob->ap-=8;
                return true;
            }
        }
        ///никаких действий не произошло
        mob->ap=0;
        return false;
    }
    bool loliMagStroke(loli_ *lo, mob_ *mob)
    {
        if(lo->ap>15)
        {
            lo->ap-=15;
            mob->hp-=4;
            return true;
        }
        return false;
    }
};


int main()
{
    myIrrlicht_ ir;
    ir.create();

    battleFunction bf;

    int gameSost=0;

    vector<mob_> mob;//активные в игре
    mob_ kashMob;
    mob.push_back(kashMob);
    mob.push_back(kashMob);
    mob.push_back(kashMob);
    mob[0].create(0, 100, 200);
    mob[1].create(0, 150, 200);
    mob[2].create(0, 200, 200);

    loli_ loli;
    loli.create();

    int run=1;

    position2d<s32> cursor;

    int receiverFlag=0;
    int mouseSost=0;

    int step=1;
    int mouseAut=0;

    int acticeMobId=-1;//номер в векторе


    int lastFPS = -1;
    int fps=0;
    fps_ myFps;


    while(ir.device->run() && run==1)
    {
    if(myFps.schet(&ir))
    {

        fps = ir.driver->getFPS();
        if (lastFPS != fps)
		{
			core::stringw tmp(L"fps: ");
			tmp += fps;

			ir.device->setWindowCaption(tmp.c_str());
			lastFPS = fps;
		}


        ir.sceneStart();
        cursor=ir.device->getCursorControl()->getPosition();

        if(receiverEvent(&ir)==0x52)
        {
            gameSost=0;
            mob.clear();
            mob.push_back(kashMob);
            mob.push_back(kashMob);
            mob.push_back(kashMob);
            mob[0].create(0, 100, 200);
            mob[1].create(0, 150, 200);
            mob[2].create(0, 200, 200);
            loli.create();
            step=1;
        }

        if(mouseAut>0) mouseAut--;
        switch(gameSost)
        {
        case -1:
            gameSost=0;
            mob.clear();
            mob.push_back(kashMob);
            mob[0].create(0, 130, 200);
            loli.create();
            step=1;
            break;
        case 0://main menu
            myDrawF(ir.driver, ir.Tface, 0, 0, 800, 600);

            if(receiverEvent(&ir)==0x01) gameSost=2;

            if(ir.receiver.GetMouseState().LeftButtonDown)
            {
                if(cursor.X<500 && cursor.X>300 && cursor.Y<220 &&cursor.Y>120)
                if(knopkaBox(300, 120, 500, 300, cursor.X, cursor.Y))
                {
                    gameSost=2;
                    mouseAut=30;
                }
            }

            break;
        case 1://меню загрузки
            break;
        case 2://собственно процесс

            switch(receiverEvent(&ir))
            {
            case 0x01:
                if(receiverFlag==0)
                {
                    gameSost=3;
                    receiverFlag=1;
                }
                break;
            }
            if(receiverEvent(&ir)!=0x01) receiverFlag=0;

            switch(step)
            {
            case -1://нет мобов, свободная  ходьба
                if(ir.receiver.GetMouseState().LeftButtonDown && mouseAut==0)
                {
                    loli.pX=cursor.X;
                    loli.pY=cursor.Y;
                    loli.freeStepSearch();
                    mouseAut=20;
                }
                loli.freeStep();
                if(mob.size()!=0) step=2;

                break;
            case 0://анимированое событие на игровой карте
                break;
            case 1://ход игрока
                if(mob.size()==0) step=-1;
                if(ir.receiver.GetMouseState().LeftButtonDown && mouseAut==0)
                {
                    mouseAut=30;

                    if(mouseSost==-1) mouseSost=0;

                    if(knopkaSphere(40, 559, 40, cursor.X, cursor.Y))
                    {
                        loli.ap=loli.apM;
                        loli.pX=loli.x;
                        loli.pY=loli.y;
                        step=2;
                        mouseSost=-1;
                    }
                    if(knopkaBox(81, 556, 124, 599, cursor.X, cursor.Y))
                    {
                        if(loli.ap>15) mouseSost=1;
                    }
                    if(mouseSost==0)
                    {
                        loli.pX=cursor.X;
                        loli.pY=cursor.Y;
                        loli.freeStepSearch();
                    }
                    if(mouseSost==1)//каст на цель
                    {
                        for(int kash=0; kash<mob.size(); kash++)
                        {
                            if(mob[kash].mouseClick(cursor.X, cursor.Y))
                            {
                                //каст по мобу
                                //loli.kast(1); - по площади, фаерболы и подобное
                                //loli.stroke - физ удар
                                //loli.magStroke - магический удар, не фаерболоподобный
                                bf.loliMagStroke(&loli, &mob[kash]);
                                mouseSost=0;
                            }
                        }
                    }
                }
 ///               if(ir.receiver.GetMouseState().RightButtonDown)
 ///               {
 ///                   mouseSost=0;
 ///               }
                if(loli.ap>0 && loli.freeStep())
                {
                    loli.ap--;
                }
                if(receiverEvent(&ir)==0x51)
                {
                    mob[0].hp=0;
                }

                for(int kash=0; kash<mob.size(); kash++)
                {
                    if(mob[kash].hp<=1)
                    {
                        mob.erase(mob.begin()+kash);
                        kash--;
                    }
                }

                if(mob.size()==0) step=-1;

                break;
            case 2://ход мобов
                for(int kash=0; kash<mob.size(); kash++)
                {
                    if(mob[kash].hp>0)
                    {
                        if(bf.mob_ai_0(&loli, &mob[kash])==false)
                        {
                            mob[kash].ap=mob[kash].apM;
                            step=1;
                        }
                        else
                        {
                            //kash--;
                            //break;
                        }
                    }
                    else
                    {
                        mob.erase(mob.begin()+kash);
                        kash--;
                    }
                }

                break;
            }

            if(loli.hp<0) gameSost=-1;

            ///render
            myDrawF(ir.driver, ir.Tmap1, 0, 0, 1000, 1000);

            myDrawF(ir.driver, ir.Tloli,
                loli.x-16,
                loli.y-100,
                32, 100);

            for(int mk=0; mk<mob.size(); mk++)
            {
                myDrawF(ir.driver, ir.Tmob1,
                    mob[mk].x-mob[mk].w,
                    mob[mk].y-mob[mk].h,
                    mob[mk].w*2, mob[mk].h);
            }

            if(mouseSost==1)
            {
                myDrawF(ir.driver, ir.TcursorMagik,
                    cursor.X-12,
                    cursor.Y-12,
                    24, 24);
            }

            myDrawF(ir.driver, ir.Tgui, 0, 0, 800, 600);
            ///render end

            break;//switch gameSost==2

        case 3:
            myDrawF(ir.driver, ir.Tescape, 0, 0, 800, 600);

            if(receiverEvent(&ir)==0x01 && receiverFlag==0)
            {
                gameSost=2;
                receiverFlag=1;
            }

            if(receiverEvent(&ir)!=0x01)
            {
                receiverFlag=0;
            }

            if(ir.receiver.GetMouseState().LeftButtonDown && mouseAut==0)
            {
                if(knopkaBox(250, 160, 549, 189, cursor.X, cursor.Y))
                {
                    //сохранение и выход
                    run=0;
                }
                if(knopkaBox(250, 240, 549, 269, cursor.X, cursor.Y))
                {
                    mouseAut=30;
                    gameSost=2;
                }
            }

            break;
        }

        ir.sceneEnd();
    }
    }

    ir.removeIr();
    return 0;
}
