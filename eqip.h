struct thing_
{
    int hp;
    int tip;// куда одевается
    char* name;

    thing_()
    {
        hp=0;
        tip=-1;
        name="";
    }
};

struct eqip_
{
    thing_ thing[11];
    /*
    0 butsi;
    1 nogi;
    2 poyas;
    3 tors;
    4 nakidka;
    5 maska;
    6 golova;
    7 naruchi;
    8 perchatki;
    9 Lruka;
    10 Rruka;*/


    eqip_()
    {
    }
};
