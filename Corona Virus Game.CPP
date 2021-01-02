#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<graphics.h>
#include <ctime>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13

#define leftEdge 180
#define rightEdge 420

using namespace std;

typedef struct PLayer_s
{
    char name[50];
    int point;
} Player;

Player player[50];
int player_index = 0;

class Car
{
public:
    int xPos,yPos;
    int speed;
    int life;
public:
    Car(int x,int y,int speed)
    {
        xPos = x;
        yPos = y;
        this->speed = speed;
        life = 3;
    }
    void moveUp()
    {
        if(yPos>20)
        {
            yPos-=speed;
        }
    }
    void moveDown()
    {
        if(yPos<450)
        {
            yPos+=speed;
        }
    }
    void moveRight()
    {
        if ( xPos < rightEdge )
        {
            xPos += speed;
        }
    }
    void moveLeft()
    {
        if ( xPos > leftEdge )
        {
            xPos -= speed;
        }
    }
    void draw()
    {
        setcolor(2);
        setfillstyle(1,2);
        sector(xPos,yPos,0,180,20,20);
        setfillstyle(1,4);
        bar(xPos-20,yPos,xPos+20,yPos+30);
    }
};
class EnemiesCar
{
public:
    int xPos;
    int yPos;
    int speed;
public:
    EnemiesCar(int x,int y,int speed)
    {
        xPos=x;
        yPos=y;
        this->speed =speed;
    }
    void appear()
    {
        if(yPos>=480+35)
            xPos = 180+35 + rand() % (420- (180+35)+1);
    }
    void draw()
    {
        const int a =20;
        const int b =35;
        setfillstyle( 1, RED );
        bar( xPos-a, yPos-a, xPos + a, yPos + a );
        setcolor(GREEN);
        setfillstyle(1, 2);
        sector(xPos-10,yPos -5,0,360,5,5);
        sector(xPos+10,yPos -5,0,360,5,5);
        fillellipse(xPos,yPos+10,10,5);
        setcolor(WHITE);
        line(xPos-a,yPos-a,xPos-b,yPos-b);
        line(xPos-a,yPos+a,xPos-b,yPos+b);
        line(xPos+a,yPos-a,xPos+b,yPos-b);
        line(xPos+a,yPos+a,xPos+b,yPos+b);
    }
    void move()
    {
        if ( yPos < 480+35 )
        {
            yPos += speed;
        }
        else
        {
            srand(time(NULL));
            yPos = 0;
            speed = 10 + rand()%(25-5+1);
        }
    }
    void checkCollusion(Car *car, int& life)
    {
        int m = -10;
        if((car->xPos > xPos-30-35-m && car->xPos < xPos+30+35+m) && (car->yPos < yPos+35+20+m && car->yPos > yPos-35-20-m))
        {
            life--;
            yPos = -20;
        }
    }

};

class Item
{
public:
    int xPos,yPos;
    int speed;
    bool isColision;
public:
    Item(int x,int y,int speed)
    {
        xPos = x;
        yPos = y;
        this->speed = speed;
        isColision = false;
    }
    void resetItem(int &pointMarker,int point)
    {
        if(yPos>480+20 || point == pointMarker*2|| isColision == true)
        {
            yPos=-20;
            pointMarker*=2;
            isColision= false;
            xPos = 180+35 + rand() % (420- (180+35)+1);
        }

    }
    void move()
    {
        yPos+=speed;
    }
    void draw()
    {
        setcolor(2);
        setfillstyle(1,2);
        sector(xPos,yPos,0,360,10,10);
    }
     void checkCollusion(Car *car, int &life)
    {
        if((car->xPos -20 < xPos && car->xPos +20 > xPos) && (car->yPos-35 < yPos && car->yPos + 15 > yPos))
        {
            life +=1;
            cout<<"da va cham hoa qua";
            isColision = true;
        }
    }
};


void Road()
{
    setfillstyle(1,1);
    bar(180-20,0,420+20,479);
}

void over()
{
    cleardevice();
    settextstyle( 1, RED, 6 );
    setcolor( RED );
    outtextxy( 10, 100, "!!!GAME OVER!!!" );
    Sleep(1000);
}
void about()
{
    cleardevice();
    Car car = Car(180,300,10);
    EnemiesCar cc1 = EnemiesCar(180+35,100,10);
    EnemiesCar cc3 = EnemiesCar(330,100,5);
    cc1.draw();
    car.draw();
    cc3.draw();
    getch();
}
void highScore()
{
    cleardevice();
    while ( !kbhit() )
    {
        settextstyle( 1, RED, 1);
        setcolor( RED );
        outtextxy(50,20,"Ten");
        outtextxy(400,20,"Diem So");
        int line_pos = 50;
        char text1[50];
        char text2[50];
        for(int i=0; i<player_index; i++)
        {
            sprintf(text1,"%s", player[i].name);
            sprintf(text2, "%d",player[i].point);
            outtextxy( 50, line_pos, text1 );
            outtextxy( 400, line_pos, text2 );
            line_pos+=30;
        }


    }
    getch();
}
void increasePoint(EnemiesCar &cc,int &p)
{
    if(cc.yPos >= 480+35)
    {
        p+=10;
        cc.appear();
    }
}
// sap xep diem so
void swap(Player &x, Player &y)
{
    Player temp = x;
    x= y;
    y= temp;

}
void sortArray(Player A[], int n)
{
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (A[j].point > A[min].point)
                min = j;
        if (min != i)
            swap(A[i], A[min]);
    }
}
int play()
{
    // tao cac doi tuong
    Car car = Car(180,450,10);
    EnemiesCar cc1 = EnemiesCar(180+35,30,5);
    EnemiesCar cc3 = EnemiesCar(330,30,10);
    bool isRunning = true;
    Item *item1 = new Item(190,60,5);
    int pointMarker = 100;
    int point = 0;
    int life = 3;
    while(isRunning)
    {
        cleardevice();
        Road();
        car.draw();
        cc1.appear();
        cc1.draw();
        cc1.move();
        //corona 2

		if(point >= pointMarker)
        {
            item1->move();
            item1->draw();
            item1->resetItem(pointMarker,point);
        }
        //corona3
        cc3.appear();
        cc3.draw();
        cc3.move();
        //
        cc1.checkCollusion(&car,life);
        cc3.checkCollusion(&car,life);
        //
        if(life == 0)
        {
            isRunning = false;
        }
        increasePoint(cc1,point);
        increasePoint(cc3,point);
        //
        item1->checkCollusion(&car,life);
        //hien thi diem so
        char text2[30]="Life: 3";
        sprintf(text2, "Life: %d", life);
        setcolor(GREEN);
        outtextxy(5, 55, text2);
        char text1[30]="Point: 0";
        sprintf(text1, "Point: %d", point);
        setcolor(GREEN);
        outtextxy(5, 30, text1);
        // di chuyen
        if (GetAsyncKeyState(VK_LEFT))
        {
            car.moveLeft();
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            car.moveRight();
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            car.moveUp();
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            car.moveDown();
        }
        Sleep(60);
    }
    if(isRunning==false)
    {
        Sleep(1000);
        system("cls");
        fflush(stdin);
        cout<<"Nhap ten nguoi choi: ";
        cin.getline(player[player_index].name,50);
        player[player_index].point = point;
        point = 0;
        player_index++;
        if(player_index + 1 > 1)
        {
            sortArray(player,player_index);

        }

        over();
    }
    return 0;

}


void menu()//for the menu appearance
{

    int s = 1, t = 0, a, p = 135;//here s is for keystroke selection in switch case
    do//to contiue the program after finish
    {
        //here a is for the rectangle to move up and down
        do          //p for rectangle use in menu
        {
            cleardevice();
            setcolor( YELLOW );
            settextstyle( 1, 0, 4 );
            outtextxy( 40, 30, "CORONA VIRUS GAME" );
            setfillstyle( 1, 2 );
            settextstyle( 1, 0, 1 );
            setcolor( 10 );
            outtextxy( 220, 137, "PLAY GAME" );
            outtextxy( 220,167, "HIGH SCORE" );
            outtextxy( 220,167+30, "ABOUT" );
            outtextxy( 220,197+30, "EXIT" );
            setcolor( RED );
            rectangle( 210, p, 400, p + 20 );//for rectangle using rectangle func
            a = getch();
            switch ( a ) //for up and down movemen if rectangle using keyboard
            {
            case UP:
                if ( p > 140 )
                {
                    p -= 30;
                    s--;

                }
                break;
            case DOWN:
                if ( p < 220 )
                {
                    p += 30;
                    s++;
                };
                break;
            case ENTER:
                a = 1;
                break;
            default:
                break;
            }
        }
        while ( a != 1 );
        switch ( s )
        {
        case 1:
            play();
            break;
        case 2:
            highScore();
            break;
        case 3:
            about();
            break;
        case 4:
            exit(0);
            break;
        }
    }
    while ( t == 0 );
}
int main()
{
    int gdriver = DETECT, gmode;
    initgraph( &gdriver, &gmode, "C:\\TC\\bgi" );
    menu();
    play();
}


