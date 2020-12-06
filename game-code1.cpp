#include<bits/stdc++.h>

#include<conio.h>

#include<graphics.h>

#include<stdlib.h>

#include<string.h>

#include<math.h>
using namespace std;
char name[10];


struct scores
{
    char name[105];
    int score;

};
struct scores hiscore[7];
FILE *input;
FILE *output;




void sort_score()
{
    int i;
    for(int l=0; l<6-1; l++)
        for(i=0; i<6-l-1; i++)
        {
            if(hiscore[i].score<hiscore[i+1].score)
            {
                hiscore[6]=hiscore[i];
                hiscore[i]=hiscore[i+1];
                hiscore[i+1]=hiscore[6];
            }
        }
}

void highscore()
{
    cleardevice();
    char arr[100];
    int i;
    //readimagefile("menu.jpg",0,0,650,500);
    input = fopen("score.txt","r");
    for(i=0; i<5; i++)
    {
        fscanf(input,"%s",&hiscore[i].name);
        fscanf(input,"%d",&hiscore[i].score);
    }
    fclose(input);
    sort_score();

    output= fopen("score.txt","w");
    for (i=0; i<5; i++)
    {
        fprintf(output,"%s\n",hiscore[i].name);
        fprintf(output,"%d\n",hiscore[i].score);

    }
    fclose(output);


    settextstyle(1,HORIZ_DIR,3);
    for(i=0; i<5; i++)
    {
        sprintf(arr,"%d",hiscore[i].score);
        outtextxy(150,150+50*i,hiscore[i].name);

        outtextxy(4000,180+50*i,arr);
    }
    delay (100);
    getch();

}
void updatescore()
{
    char arr[100];
    int i;
    input = fopen("score.txt","r");
     for(i=0; i<4; i++)
    {
        fscanf(input,"%s",&hiscore[i].name);
        fscanf(input,"%d",&hiscore[i].score);
    }

    fclose(input);
    output= fopen("score.txt","w");
    for (i=0; i<5; i++)
    {
        fprintf(output,"%s\n",hiscore[i].name);
        fprintf(output,"%d\n",hiscore[i].score);

    }
    fclose(output);
    return;
}


struct Ball
{
    int leftx,lefty,rightx,righty,upx,upy,downx,downy;

    int cx;
    int cy;
    int upleftx,uplefty,uprightx,uprighty,downleftx,downlefty,downrightx,downrighty;

    int ulimit,llimit,rlimit;

    int xIncre;
    int yIncre;

    int lives;

    int radius;

    void removePreviousBall()
    {

        setcolor(0);

        setfillstyle(1,0);

        fillellipse(abs(cx),abs(cy),radius,radius);

        setfillstyle(1,15);

        setcolor(15);

    }





    void drawBall()
    {

        setfillstyle(SOLID_FILL,RED);

        fillellipse(abs(cx),abs(cy),radius,radius);

    }

};



struct Bar
{

    int left,right,up,down,bar[8],size,movement;

    int llimit,rlimit;




    void drawBar()
    {




        setfillstyle(1,RED);

        fillpoly(4,bar);

    }




    void removePreviousBar()
    {

        setcolor(0);

        setfillstyle(1,0);

        fillpoly(4,bar);

        setfillstyle(1,15);

        setcolor(15);

    }



    void rePositionBar(int ch)
    {

        up=460;



        if(ch==0)

            left=210;

        right=left+size;

        if(ch=='a'&&left>llimit)

            left=left-movement;

        if(ch=='s'&&right<rlimit)

            left=left+movement;

        bar[0]=bar[6]=left;

        bar[2]=bar[4]=left+size;

        bar[1]=bar[3]=up;

        bar[7]=bar[5]=up+20;

    }

};



struct Game
{

    int erase[8],score;

    char scoreString[5],livesString[2],livesRemain[3];

    int isBrick[20][8];

    Ball b;

    Bar br;

    int brickLen,brickBred;





    void drawBricks()
    {

        int brick[8];

        int k=1;

        setcolor(15);

        for(int i=0; i<20; i++)
        {

            for(int j=0; j<8; j++)
            {

                brick[0]=brick[6]=i*brickLen;

                brick[1]=brick[3]=j*brickBred;

                brick[2]=brick[4]=brick[0]+brickLen;

                brick[5]=brick[7]=brick[1]+brickBred;

                if(k==16)

                    k=2;

                setfillstyle(1,k);

                if(isBrick[i][j]==1)

                {
                    fillpoly(4,brick);

                }




                k++;

            }

            k=1;

        }

        setcolor(15);

    }
    void drawBricks2()
    {

        int brick[8];

        int k=1;

        setcolor(15);

        for(int i=0; i<20; i++)
        {

            for(int j=0; j<8; j++)
            {

                brick[0]=brick[6]=i*brickLen;

                brick[1]=brick[3]=j*brickBred;

                brick[2]=brick[4]=brick[0]+brickLen;

                brick[5]=brick[7]=brick[1]+brickBred;


                if(k==16||k==13)

                    k=2;


                setfillstyle(1,k);
                if(isBrick[i][j]==2)

                {

                    fillpoly(4,brick);

                }


                if(isBrick[i][j]==1)

                {
                    setcolor(13);

                    fillpoly(4,brick);

                }




                k++;

            }

            k=1;

        }

        setcolor(15);

    }





    void initializeVariables()
    {

        b.cx=b.cx+b.xIncre;

        b.cy=b.cy+b.yIncre;

        b.lefty=b.righty=abs(b.cy);

        b.leftx=abs(b.cx)-b.radius;

        b.rightx=abs(b.cx)+b.radius;

        b.upx=b.downx=abs(b.cx);

        b.upy=abs(b.cy)-b.radius;

        b.downy=abs(b.cy)+b.radius;

        b.downleftx=abs(b.cx)-b.radius*sin(0.785);

        b.downlefty=abs(b.cy)-b.radius*cos(0.785);

        b.downrightx=abs(b.cx)+b.radius*sin(0.785);

        b.downrighty=abs(b.cy)+b.radius*cos(0.785);


        if((b.downrightx==br.left&&b.downrighty==br.up)||(b.downlefty==br.up&&b.downleftx==br.right))
        {

            b.cx=b.cx*(-1);

            b.cy=b.cy*(-1);


        }

        if(abs(b.leftx)==b.llimit||abs(b.rightx)==b.rlimit)

            b.cx=b.cx*(-1);


        if(((abs(b.downy))==br.up)&&(abs(b.downx)>=br.left&&abs(b.downx)<=br.right))

            b.cy=b.cy*(-1);


        if(abs(b.upy)==b.ulimit)

            b.cy=b.cy*(-1);


        if(abs(b.downy>480))
        {

            settextstyle(0,0,1);

            b.lives--;

            if(b.lives<0)
            {



                getch();

                displayAbout();


                exit(1);

            }

            setLivesString();



            changeLives();

            b.cx=20;

            b.cy=240;

            br.removePreviousBar();

            br.rePositionBar(0);

            br.drawBar();


            setcolor(0);

            setfillstyle(1,0);




        }



    }





    void touchLeft()
    {




        b.cx=b.cx*(-1);
    }

    void touchRight()
    {

        b.cx=b.cx*(-1);
    }

    void touchUp()
    {

        b.cy=b.cy*(-1);
    }

    void touchDown()
    {

        b.cy=b.cy*(-1);
    }

    void touchCorner()
    {


        b.cx=b.cx*(-1);


    }





    void whetherBallTouchesBrick()
    {

        for(int i=0; i<20; i++)
        {

            for(int j=0; j<8; j++)
            {

                if(isBrick[i][j]==1&&b.cy<240)
                {

                    int touchCx=abs(b.cx+12);

                    int touchCy=abs(b.cy+12);

                    int brickLeft=i*brickLen;

                    int brickRight=brickLeft+brickLen;

                    int brickUp=j*brickBred;

                    int brickDown=brickUp+brickBred;

                    if((touchCx==brickRight)&&(abs(b.upy-brickUp)<=abs(brickBred-b.radius)&&abs(b.downy-brickDown)<=abs(brickBred-b.radius)))
                    {

                        touchLeft();

                        isBrick[i][j]=0;

                    }

                    else if((touchCx==brickLeft)&&(abs(b.upy-brickUp)<=abs(brickBred-b.radius)&&abs(b.downy-brickDown)<=abs(brickBred-b.radius)))
                    {

                        touchRight();

                        isBrick[i][j]=0;

                    }

                    else if((touchCy==brickDown)&&(abs(b.leftx-brickLeft)<=abs(brickLen-b.radius)&&abs(b.rightx-brickRight)<=abs(brickLen-b.radius)))
                    {

                        touchUp();

                        isBrick[i][j]=0;

                    }

                    else if((touchCy==brickUp)&&(abs(b.leftx-brickLeft)<=abs(brickLen-b.radius)&&abs(b.rightx-brickRight)<=abs(brickLen-b.radius)))
                    {

                        touchDown();

                        isBrick[i][j]=0;

                    }

                    else if((abs(abs(b.cx)-brickLeft)+abs(abs(b.cx)-brickRight)==brickLen)&&(abs(abs(b.cy)-brickUp)+abs(abs(b.cy)-brickDown)==brickBred))
                    {

                        touchCorner();

                        isBrick[i][j]=0;

                    }



                    if(isBrick[i][j]==0)
                    {

                        score=score+(10*abs(j-8));

                        setScoreString();

                        int brick[8];

                        setcolor(0);

                        brick[0]=brick[6]=brickLeft;

                        brick[1]=brick[3]=brickUp;

                        brick[2]=brick[4]=brickRight;

                        brick[5]=brick[7]=brickDown;

                        setfillstyle(1,0);

                        fillpoly(4,brick);

                        rectangle(brick[0],brick[1],brick[2],brick[5]);

                        drawBricks();



                    }

                }

            }

        }

    }
    void whetherBallTouchesBrick2()
    {

        for(int i=0; i<20; i++)
        {

            for(int j=0; j<8; j++)
            {

                if(isBrick[i][j]==1||isBrick[i][j]==2&&b.cy<240)
                {

                    int touchCx=abs(b.cx+12);

                    int touchCy=abs(b.cy+12);

                    int brickLeft=i*brickLen;

                    int brickRight=brickLeft+brickLen;

                    int brickUp=j*brickBred;

                    int brickDown=brickUp+brickBred;

                    if((touchCx==brickRight)&&(abs(b.upy-brickUp)<=abs(brickBred-b.radius)&&abs(b.downy-brickDown)<=abs(brickBred-b.radius)))
                    {

                        touchLeft();

                        isBrick[i][j]--;

                    }

                    else if((touchCx==brickLeft)&&(abs(b.upy-brickUp)<=abs(brickBred-b.radius)&&abs(b.downy-brickDown)<=abs(brickBred-b.radius)))
                    {

                        touchRight();

                        isBrick[i][j]--;

                    }

                    else if((touchCy==brickDown)&&(abs(b.leftx-brickLeft)<=abs(brickLen-b.radius)&&abs(b.rightx-brickRight)<=abs(brickLen-b.radius)))
                    {

                        touchUp();

                        isBrick[i][j]--;

                    }

                    else if((touchCy==brickUp)&&(abs(b.leftx-brickLeft)<=abs(brickLen-b.radius)&&abs(b.rightx-brickRight)<=abs(brickLen-b.radius)))
                    {

                        touchDown();

                        isBrick[i][j]--;

                    }

                    else if((abs(abs(b.cx)-brickLeft)+abs(abs(b.cx)-brickRight)==brickLen)&&(abs(abs(b.cy)-brickUp)+abs(abs(b.cy)-brickDown)==brickBred))
                    {

                        touchCorner();

                        isBrick[i][j]--;

                    }



                    if(isBrick[i][j]==1)
                    {



                        int brick1[8];

                        setcolor(0);

                        brick1[0]=brick1[6]=brickLeft;

                        brick1[1]=brick1[3]=brickUp;

                        brick1[2]=brick1[4]=brickRight;

                        brick1[5]=brick1[7]=brickDown;

                        setfillstyle(1,13);

                        fillpoly(4,brick1);

                        rectangle(brick1[0],brick1[1],brick1[2],brick1[5]);



                    }

                    if(isBrick[i][j]==0)
                    {

                        score=score+(10*abs(j-8));

                        setScoreString();

                        int brick[8];

                        setcolor(0);

                        brick[0]=brick[6]=brickLeft;

                        brick[1]=brick[3]=brickUp;

                        brick[2]=brick[4]=brickRight;

                        brick[5]=brick[7]=brickDown;

                        setfillstyle(1,0);

                        fillpoly(4,brick);

                        rectangle(brick[0],brick[1],brick[2],brick[5]);

                        drawBricks();

                        i=0,j=0;

                    }

                }

            }

        }

    }






    void setScoreString()
    {


        sprintf(scoreString,"%d",score);


    }

    void setLivesString()
    {

        livesString[1]='\0';

        livesString[0]=48+b.lives;


    }

    void changeScore()
    {

        settextstyle(0,0,2);

        outtextxy(550,230,scoreString);

    }

    void changeLives()
    {

        settextstyle(10,0,2);

        outtextxy(560,350,livesString);

    }





    void displayAbout()
    {
        int ttt=0;
        cleardevice();//image
        readimagefile("start.jpg",50,10,650,500);
        setcolor(12);
        settextstyle(0,0,2);
        outtextxy(10,100,"Enter Your Name in Console");
        scanf("%s",name);
        if(score>hiscore[4].score)
        {
            hiscore[4].score=score;
            strcpy(hiscore[4].name,name);
            ttt=1;
        }
        getch();

        cleardevice();

        settextstyle(0,0,3);
        char q=48;

        do
        {
            readimagefile("game-over.jpg",50,10,650,500);

            setcolor(4);
            if(ttt==1)
            outtextxy(50,100,"Congratulations,High Score!!!");
            setcolor(12);

            settextstyle(3,0,4);

            outtextxy(50,120,name);

            outtextxy(50,100,"SCORE");

            settextstyle(3,0,4);

            outtextxy(50,150,scoreString);

            settextstyle(3,0,4);

            outtextxy(90,400,"Press Space to Exit");
            getch();
            updatescore();


            q=getch();
            exit(1);

        }

        while(q!=' ');

    }



    void displayabout()
    {
        int warning[8];
        warning[0]=warning[6]=20;

        warning[1]=warning[3]=300;

        warning[2]=warning[4]=400;

        warning[5]=warning[7]=180;


        cleardevice();

        settextstyle(0,0,3);
        char q=48;

       do
        {
            settextstyle(0,0,2);

            outtextxy(20,220,"Press Enter To Continue");



            outtextxy(20,240,"Press Space to Exit");


            q=getch();
            if(q==13)
            {

                getch();

                exit(0);

            }
            if(q=' ')
            {
                setcolor(0);

                setfillstyle(1,0);

                fillpoly(4,warning);

                setfillstyle(1,15);

                setcolor(15);
                continue;


            }


        }
        while(q!=' ');




    }

    //level 1

    void gameHandler()
    {
        int page=0;










        brickLen=25,brickBred=15;

        for(int i=0; i<20; i++)

            for(int j=0; j<8; j++)

                isBrick[i][j]=1;

        drawBricks();





        b.cx=20;

        b.cy=240;

        b.xIncre=4;

        b.yIncre=4;

        b.radius=8;

        br.size=80;

        br.movement=10;

        score=0;


        b.lives=3;

        line(500,0,500,480);

        settextstyle(0,0,2);

        outtextxy(535,200,"Score:");

        settextstyle(0,0,2);

        setScoreString();

        outtextxy(535,230,scoreString);

        outtextxy(535,320,"Lives:");

        setLivesString();

        outtextxy(565,350,livesString);

        b.ulimit=0;

        b.llimit=0;

        b.rlimit=500;

        br.llimit=0;

        br.rlimit=500;

        br.rePositionBar(0);

        br.drawBar();



        while(1)
        {



            delay(2);

            b.removePreviousBall();

            changeScore();

            initializeVariables();

            whetherBallTouchesBrick();

            b.drawBall();

            br.removePreviousBar();

            br.drawBar();



            if(GetAsyncKeyState(VK_RIGHT))
            {
                br.removePreviousBar();

                br.rePositionBar('s');

                br.drawBar();
            }

            if(GetAsyncKeyState(VK_LEFT))
            {
                br.removePreviousBar();

                br.rePositionBar('a');

                br.drawBar();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {

                displayabout();


            }



            delay(4);

        }
    }

    //level 2

    void gamehandler1()
    {


        getch();

        clearviewport();

        brickLen=25,brickBred=15;

        for(int i=0; i<20; i++)

            for(int j=0; j<8; j++)

                isBrick[i][j]=2;

        drawBricks2();

        b.cx=20;

        b.cy=240;

        b.xIncre=4;

        b.yIncre=4;

        b.radius=8;

        br.size=80;

        br.movement=10;

        score=0;

        b.lives=3;

        line(500,0,500,480);

        settextstyle(0,0,2);

        outtextxy(535,200,"Score:");

        settextstyle(0,0,2);

        setScoreString();

        outtextxy(535,230,scoreString);

        outtextxy(535,320,"Lives:");

        setLivesString();

        outtextxy(565,350,livesString);

        b.ulimit=0;

        b.llimit=0;

        b.rlimit=500;

        br.llimit=0;

        br.rlimit=500;

        br.rePositionBar(0);

        br.drawBar();

        int ch='a';

        while(1)
        {
            delay(2);

            b.removePreviousBall();

            changeScore();

            initializeVariables();

            whetherBallTouchesBrick2();

            b.drawBall();

            br.removePreviousBar();

            br.drawBar();


            if(GetAsyncKeyState(VK_RIGHT))
            {
                br.removePreviousBar();

                br.rePositionBar('s');

                br.drawBar();
            }

            if(GetAsyncKeyState(VK_LEFT))
            {
                br.removePreviousBar();

                br.rePositionBar('a');

                br.drawBar();
            }
            if(GetAsyncKeyState(VK_ESCAPE))
            {

                displayabout();

                getch();

                exit(0);

            }


            delay(4);

        }
    }

};
int interface1()
{
    readimagefile("Changmenu.jpg",100,100,650,500);

    setcolor(12);

    settextstyle(10,0,6);

    outtextxy(200,50,"1.New Game");

    outtextxy(200,125,"2.High Score");

    outtextxy(200,300,"4.About");

    outtextxy(200,210,"3.Instructions");

    outtextxy(200,400,"5.Exit");

    int choice=getch();

    if (choice==51)
    {
        readimagefile("ins.jpg",0,65,650,500);

        setcolor(12);

        setfillstyle(4,14);

        settextstyle(10,0,5);

        outtextxy(150,50,"Instructions");

        settextstyle(10,0,3);

        outtextxy(10,120,"Press left and right arrow keys to move the");

        outtextxy(30,150,"Bar.Use the bar to reflect the ball.");

        settextstyle(10,0,4);

        outtextxy(100,200,"Dont loose the ball!! ");

        getch();

        clearviewport();

        interface1();
    }
    else if(choice==49)
    {
        clearviewport();

        setcolor(12);

        settextstyle(10,0,4);

        int tt;

        readimagefile("about.jpg",0,70,650,500);

        outtextxy(200,100,"Choose Difficulty");

        outtextxy(200,150,"1.Easy");

        outtextxy(200,200,"2.Hard");

        tt=getch();

        if(tt==49)
        {

            return 1;

        }

        if(tt=50)

        {

            return 2;

        }

    }

    else if(choice==52)

    {

        clearviewport();

        readimagefile("about.jpg",50,10,650,500);

        setcolor(13);

        settextstyle(10,0,5);

        outtextxy(250,50,"ABOUT ");

        setcolor(13);

        settextstyle(10,0,3);

        outtextxy(50,150,">This is a console based PC game.");

        outtextxy(50,200,">Devloped By MUNTAHA TASNIM(19) and");

        outtextxy(50,250,"MD.AZAHER UDDIN (31)");

        settextstyle(10,0,5);

        outtextxy(100,300,"CSEDU-23 ");

        getch();

        clearviewport();

        interface1();

    }


    else if(choice==53)

    {
        exit(0);
    }


    else if(choice==50)

    {
         return 3;
    }


    else
    {
        int lll;

        clearviewport();

        readimagefile("danger.jpg",50,10,650,500);

        setcolor(11);

        settextstyle(10,0,4);

        outtextxy(10,100,"PLEASE  PRESS 1 OR ENTER FOR'NEW");

        outtextxy(10,150,"GAME'");

        outtextxy(10,200,"OR PRESS 2 FOR 'INSTRUCTIONS' ");

        outtextxy(10,250,"OR PRESS 3 FOR 'ABOUT' ");

        outtextxy(10,300,"OR PRESS 4 TO EXIT' ");

        outtextxy(10,350,"OR PRESS 'ESC' IF U WANNA QUIT");

        outtextxy(10,400,"IN THE MIDDLE OF THE GAME");

        lll=getch();

        clearviewport();

        if(lll==13||lll==49)
        {
            clearviewport();

            setcolor(11);

            settextstyle(10,0,4);

            int tt;

            outtextxy(200,100,"Choose Difficulty,");

            outtextxy(200,150,"1.Easy");

            outtextxy(200,200,"2.Hard");

            tt=getch();

            if(tt==49)
            {
                return 1;
            }

            if(tt=50)
            {
                return 2;
            }
        }

        else interface1();
    }

    getch();

    clearviewport();

}

int main()

{

    int gDriver=DETECT,gMode;

    detectgraph(&gDriver,&gMode);

    initgraph(&gDriver,&gMode,"");

    int p;

    Game g;

    readimagefile("front.jpg",0,0,640,500);

    setcolor(7);

    settextstyle(10,0,8);

    //outtextxy(50,200,"<<DX BALL>>");

    getch();

    clearviewport();

    p=interface1();

    if(p==1)
    {

        clearviewport();

        g.gameHandler();

    }

    if(p==2)
    {
        clearviewport();

        g.gamehandler1();
    }
    if(p==3)
    {
        clearviewport;
        highscore();
        getch();
        interface1();

    }


    getch();

    return 0;

}


