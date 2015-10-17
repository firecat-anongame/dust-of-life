struct loli_
{
    eqip_ eqip;

    int x,y;
    int pX, pY;

    int tincture[7][2];//[][0]-текущее значение, [][1]-максимальное значение
    /*
    0-золото
    1-серебро
    2-зелень
    3-червлень
    4-чернь
    5-пурпур
    6-лазурь
    */

    int hp, hpM;
    int ap, apM;

    int eat;//голод
    int water;//жажда
    int sleep;//сон, может и не нужен

    int speed;//скорость
    int force;//сила
    int magic;//магия
    int telo; //телосложение
    int vol;  //выносливость
    int smetka;//сметка

    int Fdamag;//физ атака
    int Mdamag;//маг атака
    int Fspeed;//скскорость физ атаки (складывается с типом оружия)
    int Mspeed;//скорость маг атаки
    int Fbron;//физ защита
    int Mbron;//маг защита
    int Sspeed;//скорость передвижения
    int accur;//точность - на луки и магию
    int fatigue;//предел усталости
    int stels;//скрытность (ака тихая ходьба и маскировка)
    int deads;//уровень обречённости (количество смертей)

    void create()
    {
        x=pX=400;
        y=pY=300;

        for(int kash=0; kash<7; kash++)
        {
            tincture[kash][0]=
            tincture[kash][1]=0;
        }

        sin=0;
        cos=0;
        hp=hpM=20;
        ap=apM=80;

        eat=100;//голод
        water=100;//жажда
        sleep=100;//сон, может и не нужен

        speed=5;//скорость
        force=3;//сила
        magic=0;//магия
        telo=2; //телосложение
        vol=2;  //выносливость
        smetka=3;//сметка

        Fdamag=force+force*(speed/3)+telo/3 ;//физ атака
//        Mdamag= ;//маг атака
        Fspeed=((telo/2)*speed)/force;//скорость физ атаки (складывается с типом оружия), отвечает за поглощение ap при ударах
//        Mspeed= ;//скорость маг атаки
//        Fbron= ;//физ защита
//        Mbron= ;//маг защита
        Sspeed=speed;//скорость передвижения
        accur=smetka+(force/3);//точность - на луки и магию
        fatigue=vol*3+telo ;//предел усталости
        stels=(speed/2)+smetka-1;//скрытность (ака тихая ходьба и маскировка)

        deads=0;//уровень обречённости (количество смертей)
    }


    float sin, cos;
    void freeStepSearch()
    {
        float sq;
        sq=sqrt((pX-x)*(pX-x)+(pY-y)*(pY-y));

        sin=(pY-y)/sq;
        if(sin<0) sin*=-1;

        cos=(pX-x)/sq;
        if(cos<0) cos*=-1;
    }

    bool freeStep()
    {
        if(x==pX && y==pY) return false;
        if(pX!=x)
        {
            if(x<pX)
            {
                if((pX-x)<Sspeed) { x=pX; }
                else { x+=Sspeed*cos; }
            }
            else
            {
                if((x-pX)<Sspeed) { x=pX; }
                else { x-=Sspeed*cos; }
            }
        }
        if(pY!=y)
        {
            if(y<pY)
            {
                if((pY-y)<Sspeed) { y=pY; }
                else { y+=Sspeed*sin; }
            }
            else
            {
                if((y-pY)<Sspeed) { y=pY; }
                else { y-=Sspeed*sin; }
            }
        }
        return true;
    }

    void crash(int dam)
    {
        hp-=dam;
    }

};

