#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<conio.h>

int impactflag = 0;

void background(int color)
{
 int i,j;

 for(i=0;i<=500;i++)
 {
     for(j=0;j<=700;j++)
     {
         putpixel(i,j,color);
     }
 }
}

void fillcircle(int x,int y,int r,int color)
{
    int i;
    for(i=1;i<=r;i++)
    {
        setlinestyle(SOLID_LINE,0,1);
        setcolor(color);
        circle(x,y,i);
    }
}

void projectile(int h, int rd, int pd, int ld, int id,int v,int &xp,int &yp, int &rp, int &xi,int &yi,int &ri)
{
    //Changing real values to screen scale
    int rpx = 1.0*rd*60/25;
    int hpx = 1.0*h*60/25;
    int r = 7.3*60/25;
    int xpx,ypx;


    //Set fill style
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);

    float mps = v*5.0/18;
    float z = 500.0;
    float t = pd/(mps*100);
    float y = 1.0*h;
    float a = 2*h/(t*t*100);
    int yspeed = a*t;
    float k;
    float x = rd;

    float t_i;

    int n = 0;

    //Loop for projectile
    for(t_i=0;t_i<=t;t_i+=0.01)
    {

        y = h - (0.5)*a*pow(t_i,2)*100;

        //Calculating distance in z direction
        z = mps*t_i*100;

        //Calculating distance in z direction
        x = rd + z*(1.0*ld)/pd;

        //Magnification factor with depth
        k = (70-2*((z+500)/100))/25;

        r = (int)(k*7.3);

        xpx = k*x;
        ypx = (int)(600 - (z*20/100)-k*y);

        if(n == 0)
        {
                    delay(100);
                    setcolor(WHITE);
                    circle(250+xpx,ypx,r);
                    fillcircle(250+xpx,ypx,r,WHITE);

                    delay(100);
                    setlinestyle(SOLID_LINE,0,2);
                    setcolor(LIGHTCYAN);
                    circle(250+xpx,ypx,r);
                    fillcircle(250+xpx,ypx,r,LIGHTCYAN);

                    delay(100);
                    setlinestyle(SOLID_LINE,0,1);
                    setcolor(BLACK);
                    line(250+xpx,ypx,250+xpx,ypx+k*y);
        }
        n = (n+1)%5;

        if(z >= 2000-id)
        {
            xi = xpx;
            yi = ypx;
            ri = r;

            fillcircle(250+xi,yi,ri,LIGHTRED);

            delay(1000);


            setcolor(WHITE);

            if(abs(xpx) < k*13)
                {
                    outtextxy(350,50,"Impact in-line");
            }
            else
            {
                    outtextxy(350,50,"Impact not in-line");
            }
            impactflag = 1;
        }

    }

    xp = xpx;
    yp = ypx;
    rp = r;

    setcolor(WHITE);

    if(abs(xpx) < k*13)
    {
        outtextxy(20,50,"Pitched Inside");
    }
    else{
        outtextxy(20,50,"Pitched Outside");
    }

}

void afterpitch(int hv, int vv, float cor, float cof, int rd, int pd, int ld, int pld,int id, float a,int &xi,int &yi,int &ri)
{
    vv = cor*vv;

    int sd = rd + ld;

	float t,t_i;

	float mps = hv*5.0/18 -cof*a*0.01;

	float vmps = vv*5.0/18;

    float z = pd;
    float x = sd;
    float y = 0;

    float k,r;

    int xpx,ypx;

	int n = 0;

	t = 1.0*(2000 - pd)/(mps*100);

	for(t_i=0;t_i<=t;t_i+=0.0005)
	{
		y = vmps*100*t_i + 0.5*a*pow(t_i,2)*100;

		z = pd + mps*t_i*100;

		x = sd + (z-pd)*(1.0*pld)/(2000-pd);

		k = (70-2*((z+500)/100))/25;

		r = (int)(k*7.3);

        xpx = k*x;
        ypx = (int)(600 - (z*20/100)-k*y);

		if(n == 0)
        {
                    delay(100);
                    setlinestyle(SOLID_LINE,0,2);
                    setcolor(WHITE);
                    circle(250+xpx,ypx,r);
                    fillcircle(250+xpx,ypx,r,WHITE);


                    delay(100);
                    setlinestyle(SOLID_LINE,0,2);
                    setcolor(LIGHTCYAN);
                    circle(250+xpx,ypx,r);
                    fillcircle(250+xpx,ypx,r,LIGHTCYAN);

                    delay(100);
                    setlinestyle(SOLID_LINE,0,1);
                    setcolor(BLACK);
                    line(250+xpx,ypx,250+xpx,ypx+k*y);
        }
        n = (n+1)%50;

        if(z >= 2000-id && !impactflag)
        {
            xi = xpx;
            yi = ypx;
            ri = r;

            fillcircle(250+xi,yi,ri,LIGHTRED);

            delay(1000);

            setcolor(WHITE);

            if(abs(xpx) < k*13)
                {
                    outtextxy(350,50,"Impact in-line");
            }
            else
            {
                    outtextxy(340,50,"Impact not in-line");
            }
            impactflag = 1;

        }

	}

	setcolor(BLACK);
    circle(250+xpx,ypx,r);
    fillcircle(250+xpx,ypx,r,BLACK);

    setcolor(WHITE);

    if(abs(xpx) < k*15 && y < 69)
    {
        outtextxy(195,650,"Hitting Stumps");
    }
    else
    {
        outtextxy(195,650,"Missing Stumps");
    }



}




main()
{
    int gd=DETECT,gm;
    //initgraph(&gd,&gm,"..\\bgi");
    initwindow(500,700);
    background(LIGHTGREEN);

    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    int pitch[]={200,200,300,200,400,600,100,600,200,200};

    setfillstyle(SOLID_FILL,YELLOW);
    fillpoly(5,pitch);

    int stumpsline[]={220,600,280,600,260,200,240,200,220,600};

    setfillstyle(SOLID_FILL,LIGHTGRAY);
    fillpoly(5,stumpsline);


    setlinestyle(SOLID_LINE,0,9);
    setcolor(MAGENTA);
    line(220,600,220,450);
    line(250,600,250,450);
    line(280,600,280,450);
    line(220,450,280,450);

    setlinestyle(SOLID_LINE,0,3);
    setcolor(MAGENTA);
    line(240,200,240,150);
    line(250,200,250,150);
    line(260,200,260,150);
    line(240,150,260,150);


    delay(1000);

    int v, h, rd, pd, ld, pld, id, xp, yp, xi, yi, r, ri;

    float cor, cof;

    v = 90;
    h = 150;
    rd = -50;
    pd = 1000;
    ld = 20;
    pld = 30;
    id = 200;
    cor = 0.9;
    cof = 0.35;

    /*

    printf("\nEnter the following values : \n");
    printf("Bowling speed (KMPH) :");
    scanf("%d",&v);
    printf("Release Height from ground(cm) :");
    scanf("%d",&h);
    printf("Pitching Distance from Bowler's End(cm) :");
    scanf("%d",&pd);
    printf("Release Distance from Middle Stump(cm) :");
    scanf("%d",&rd);
    printf("Lateral Deviation at Pitching (cm) :");
    scanf("%d",&ld);
    printf("Lateral Deviation after Pitching (cm) :");
    scanf("%d",&pld);
    printf("Impact distance from Batting Stumps (cm) :");
    scanf("%d",&id);
    */


    float mps = v*5.0/18;
    float t = pd/(mps*100);
    float y = 1.0*h;
    float a = 2*h/(t*t*100);
    int yspeed = a*t;

    projectile(h,rd,pd,ld,id,v,xp,yp,r,xi,yi,ri);

    fillcircle(250+xp,yp,r,BLUE);

	delay(1000);

	afterpitch(v,yspeed,cor,cof,rd,pd,ld,pld,id,a,xi,yi,ri);

	fillcircle(250+xp,yp,r,BLUE);

	fillcircle(250+xi,yi,ri,LIGHTRED);


    getch();
    closegraph();
    return 0;
}
