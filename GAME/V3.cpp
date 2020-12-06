
#include<bits/stdc++.h>


#include<graphics.h>

#include<dos.h>

#include<stdlib.h>

#include<string.h>

#include<math.h>

//1530,835

//#define qetaDefine 0
//#define PI 3.14159265


#include<iostream>

using namespace std;


struct Ball
{

    int v = 10;

    int qeta = 30;


    int leftx,lefty,rightx,righty,upx,upy,downx,downy;

    int cx;
    int cy;
    int upleftx,uplefty,uprightx,uprighty,downleftx,downlefty,downrightx,downrighty;

    int ulimit,llimit,rlimit;

    int xIncre=7;//=
    int yIncre=5;//=

    int lives;

    int radius;




    //removes the ball from previous frame

    void removePreviousBall()
    {

        setcolor(0);

        setfillstyle(1,0);

        fillellipse(abs(cx),abs(cy),radius,radius);

        setfillstyle(1,15);

        setcolor(15);

    }



    //draws the ball on the screen as per cx and cy

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



    //draws the bar as per the current location of the bar

    void drawBar()
    {

        //fillpoly(4,bar);


        setfillstyle(1,RED);

        fillpoly(4,bar);

    }



    //removes the bar for the previous frame

    void removePreviousBar()
    {

        setcolor(0);

        setfillstyle(1,0);

        fillpoly(4,bar);

        setfillstyle(1,15);

        setcolor(15);

    }



    //devices the new position co-ordinates for the bar

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



    //draws the bricks that are currently alive

    //with reference to the array isBricks

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
                //k=rand()%16;

                setfillstyle(1,k);
                if(isBrick[i][j]==2)

                {
                    setcolor(13);
                    fillpoly(4,brick);

                }


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



    //initializes the postion variables for ball

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
            /*b.xIncre*=(-1);

            b.cx=b.cx+b.xIncre;

            b.yIncre*=(-1);

            b.cy=b.cy+b.yIncre;
            */


        }

        if(abs(b.leftx)==b.llimit||abs(b.rightx)==b.rlimit)

            b.cx=b.cx*(-1);
        // b.xIncre*=(-1);

        //b.cx=b.cx+b.xIncre;

        if(((abs(b.downy))==br.up)&&(abs(b.downx)>=br.left&&abs(b.downx)<=br.right))

            b.cy=b.cy*(-1);
        // b.yIncre*=(-1);

        //b.cy=b.cy+b.yIncre;

        if(abs(b.upy)==b.ulimit)

            b.cy=b.cy*(-1);
        // b.yIncre*=(-1);

        //b.cy=b.cy+b.yIncre;

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

            setLivesString();//lives print kore

            //outtextxy(190,240,livesRemain);

            changeLives();//lives change kore

            b.cx=20;

            b.cy=240;

            br.removePreviousBar();

            br.rePositionBar(0);

            br.drawBar();


            setcolor(0);

            setfillstyle(1,0);

            // getch();


            /*erase[0]=erase[6]=200;

            erase[1]=erase[3]=240;

            erase[2]=erase[4]=400;

            erase[5]=erase[7]=260;

            fillpoly(4,erase);

            //setcolor(15);

            //setfillstyle(1,15);

            */
        }



    }



    //touch function determine the action to be

    //taken when a brick is touched

    void touchLeft()
    {

        // b.xIncre*=(-1);

        //b.cx=b.cx+b.xIncre;

        b.cx=b.cx*(-1);
    }

    void touchRight()
    {

        // b.xIncre*=(-1);

        //b.cx=b.cx+b.xIncre;
        b.cx=b.cx*(-1);
    }

    void touchUp()
    {

        //b.yIncre*=(-1);

        //b.cy=b.cy+b.yIncre;
        b.cy=b.cy*(-1);
    }

    void touchDown()
    {

        //b.yIncre*=(-1);

        //b.cy=b.cy+b.yIncre;
        b.cy=b.cy*(-1);
    }

    void touchCorner()
    {

        /*b.xIncre*=(-1);

        b.cx=b.cx+b.xIncre;

        b.yIncre*=(-1);

        b.cy=b.cy+b.yIncre;*/
        b.cx=b.cx*(-1);
        //b.cy=b.cy*(-1);

    }



    //determines whether the ball touches the brick

    //and takes the necessary action

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

                        //i=0,j=0;

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

                        //score=score+(10*abs(j-8));

                        //setScoreString();

                        int brick1[8];

                        setcolor(0);

                        brick1[0]=brick1[6]=brickLeft;

                        brick1[1]=brick1[3]=brickUp;

                        brick1[2]=brick1[4]=brickRight;

                        brick1[5]=brick1[7]=brickDown;

                        setfillstyle(1,13);

                        fillpoly(4,brick1);

                        rectangle(brick1[0],brick1[1],brick1[2],brick1[5]);

                        //drawBricks();

                        //i=0,j=0;

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





    //setString and change functions update score and lives display

    void setScoreString()
    {

//		itoa(score,scoreString,10);
        sprintf(scoreString,"%d",score);


    }

    void setLivesString()
    {

        livesString[1]='\0';

        livesString[0]=48+b.lives;

        //livesRemain[0]=49+b.lives;

    }

    void changeScore()
    {

        //setcolor(15);

        // setfillstyle(1,15);

        settextstyle(0,0,2);

        outtextxy(550,230,scoreString);

    }

    void changeLives()
    {

        //setcolor(12);

        //setfillstyle(4,14);

        settextstyle(10,0,2);

        outtextxy(560,350,livesString);

    }



    //displays the list of Programmers in this project

    void displayAbout()
    {

        cleardevice();

        settextstyle(0,0,3);
        char q=48;

        do
        {
            readimagefile("start.jpg",50,10,650,500);
            setcolor(12);
            settextstyle(0,0,4);
            outtextxy(50,100,"SCORE");

            settextstyle(0,0,3);

            //sprintf(scoreString,"%d",score);

            outtextxy(50,150,scoreString);

            outtextxy(90,300,"Game Over.Thank You.");



            outtextxy(90,500,"Press Space to Exit");


            q=getch();

        }

        while(q!=' ');

    }



    //function which centrally controls the execution of game
    void displayabout()
    {

        cleardevice();

        settextstyle(0,0,3);
        char q=48;

        do
        {
            //settextstyle(0,0,1);

            outtextxy(90,200,"Press Enter To Continue");



            outtextxy(90,240,"Press Space to Exit");


            q=getch();
            if(q==13)
                return ;
            if(q=' ')
            {
                getch();

                exit(0);

            }


        }
        while(q!=' ');




    }


    void gameHandler()
    {
        int page=0;


        //setcolor(GREEN);



        //settextstyle(0,0,2);




        //void putimage(int 50, int 50, void *bitmap, int op);






        //outtextxy(180,200,"DX Ball!!!!!!");



        //getch();

        //clearviewport();




        brickLen=25,brickBred=15;

        for(int i=0; i<20; i++)

            for(int j=0; j<8; j++)

                isBrick[i][j]=1;

        drawBricks();
        //int v = 4;

        /*int qeta = 30;


        {

        	qeta = (br.left + br.movement- b.cx) + 45;
        }

        */




        b.cx=20;

        b.cy=240;

        b.xIncre=2;//(int) v*cos(qeta*PI / 180);

        b.yIncre=2;//(int) v*cos(qeta*PI / 180);

        b.radius=8;

        br.size=80;

        br.movement=10;

        score=0;

        //livesRemain[0]=' ';

        //livesRemain[1]=' ';

        //strcat(livesRemain,"live(s) remaining.");

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

        //int ch='a';


        while(1)
        {
            //setactivepage(1-page);
            //setvisualpage(page);


            delay(2);

            b.removePreviousBall();

            changeScore();

            initializeVariables();

            whetherBallTouchesBrick();

            b.drawBall();

            br.removePreviousBar();

            br.drawBar();

            //line(500,0,500,480);

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


            /*while(!kbhit())
            {

                delay(4);

                b.removePreviousBall();

                changeScore();

                initializeVariables();

                whetherBallTouchesBrick();

                b.drawBall();

                br.removePreviousBar();

                br.drawBar();

                line(500,0,500,480);

            }

            ch=getch();

            if(ch=='a'||ch==75)
            {

                br.removePreviousBar();

                br.rePositionBar('a');

                br.drawBar();

            }

            if(ch=='s'||ch==77)
            {

                br.removePreviousBar();

                br.rePositionBar('s');

                br.drawBar();

            }

            if(ch=='p')

                ch=getch();

            if(ch=='q')
            {

                displayAbout();

                getch();

                exit(0);



            }*/
            // page=1-page;
            delay(4);
            //cleardevice();
        }
    }


    void gamehandler1()
    {
        // initwindow(1530,835,"dxball");
        //setcolor(GREEN);



        //settextstyle(0,0,2);




        //void putimage(int 50, int 50, void *bitmap, int op);


        //setfillstyle(SOLID_FILL,DARKGRAY);
        //floodfill(0,1,GREEN);
        //readimagefile("dxball.jpg",200,150,400,250);




        //outtextxy(180,200,"DX Ball!!!!!!");



        getch();

        clearviewport();

        brickLen=25,brickBred=15;

        for(int i=0; i<20; i++)

            for(int j=0; j<8; j++)

                isBrick[i][j]=2;

        drawBricks2();
        //int v = 4;

        /*int qeta = 30;


        {

        	qeta = (br.left + br.movement- b.cx) + 45;
        }

        */




        b.cx=20;

        b.cy=240;

        b.xIncre=2;//(int) v*cos(qeta*PI / 180);

        b.yIncre=2;//(int) v*cos(qeta*PI / 180);

        b.radius=8;

        br.size=80;

        br.movement=10;

        score=0;

        //livesRemain[0]=' ';

        //livesRemain[1]=' ';

        //strcat(livesRemain,"live(s) remaining.");

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
            //setactivepage(1-page);
            //setvisualpage(page);


            delay(2);

            b.removePreviousBall();

            changeScore();

            initializeVariables();

            whetherBallTouchesBrick2();

            b.drawBall();

            br.removePreviousBar();

            br.drawBar();

            //line(500,0,500,480);

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


            //page=1-page;
            delay(4);
            //cleardevice();
        }
    }

};
int interface1()
{





    //readimagefile("ins.jpg",0,0,650,500);
    readimagefile("Changmenu.jpg",100,100,650,500);
    setcolor(12);

    //setfillstyle(4,14);

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
        setcolor(7);

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
        setcolor(11);
        settextstyle(10,0,4);
        int tt;
        outtextxy(200,100,"Choose Difficulty,");
        outtextxy(200,150,"1.Easy");
        outtextxy(200,200,"2. Hard");
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
        clearviewport();
        //initwindow(300,300,"score");

        FILE *input=fopen("in.c","r");
        FILE *output=fopen("out.c","w");
        char temp[30];
        //fscanf(input,"%s%*c",temp[30]);
        char a[5+5][30];
        int score[5+5];

        int tscore;
        char tname[10];
        printf("Rank            Name          Score\n");
        for(int i=1; i<=5; i++)
            //fprintf(output," %-15d%-14s%d\n",i,a[i],score[i]);
            fclose(input);
        fclose(output);
        remove("in.c");
        rename("out.c","in.c");
        fclose(input);
        strcpy(a[1],"Anik");
        score[1]=6230;
        strcpy(a[2],"Muntaha");
        score[2]=6150;
        strcpy(a[3],"Navid");
        score[3]=6040;
        strcpy(a[4],"Aka");
        score[4]=5980;
        strcpy(a[5],"Lll");
        score[5]=5860;
        for(int i=1; i<=5; i++)
            printf(" %-15d%-14s%d\n",i,a[i],score[i]);

        getch();
        clearviewport();
        interface1();
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

    //setbkcolor(LIGHTGRAY);


    Game g;

    // setbkcolor(LIGHTGRAY);

    setfillstyle(SOLID_FILL,DARKGRAY);
    floodfill(0,1,BLUE);
    readimagefile("main.jpg",0,0,640,500);
    setcolor(7);
    settextstyle(10,0,8);
    outtextxy(50,200,"<<DX BALL>>");
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



    getch();
    return 0;

}


