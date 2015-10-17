struct mob_
{
    int x, y;
    int w, h;
    int id;
    int ap, apM;

    int lvl;
    char *name;

    int hp, hpM;
    int mp, mpM;

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

    void create(int ID, int X, int Y)
    {
        switch(ID)
        {
        case 0:
            id=ID;
            name="slime";
            Sspeed=2;
            x=X;
            y=Y;
            w=16;
            h=23;
            hp=10;
            ap=apM=40;
            Fdamag=5;
            break;
        }
    }

    void step(int pX, int pY)
    {
        float fsin, fcos;
        float sq;
        sq=sqrt((pX-x)*(pX-x)+(pY-y)*(pY-y));

        fsin=(pY-y)/sq;
        if(fsin<0) fsin*=-1;

        fcos=(pX-x)/sq;
        if(fcos<0) fcos*=-1;

        if(pX!=x)
        {
            if(x<pX)
            {
                if((pX-x)<Sspeed) { x=pX; }
                else { x+=Sspeed*fcos; }
            }
            else
            {
                if((x-pX)<Sspeed) { x=pX; }
                else { x-=Sspeed*fcos; }
            }
        }
        if(pY!=y)
        {
            if(y<pY)
            {
                if((pY-y)<Sspeed) { y=pY; }
                else { y+=Sspeed*fsin; }
            }
            else
            {
                if((y-pY)<Sspeed) { y=pY; }
                else { y-=Sspeed*fsin; }
            }
         }
    }

    bool mouseClick(int mx, int my)
    {
        if(((y-h)<my) && (my<y) && (mx-w)<x && x<(mx+w))
        {
            return true;
        }
        return false;
    }
};
