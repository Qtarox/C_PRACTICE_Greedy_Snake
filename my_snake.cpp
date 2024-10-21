#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#define  N 22
#define speed 2000
using namespace std;
int start;
int cnt=0;
char key;
int direction=3;
void gotoxy(int x,int y);
class snake_pos{
public:
    int s_x;
    int s_y;
    snake_pos(){
        s_x=0;
        s_y=0;
    };
    void initialize(int &);
};

void snake_pos::initialize(int &j)
{
    s_x = 1;
    s_y = j;
}
////////////////////////////////////////////
class Snake {
private:

    int direction=3;  // 0'U' (up), 1'D' (down), 2'L' (left), 3'R' (right)
    int length;
    snake_pos position[(N-2)*(N-2)+1];
public:
    // Body segments of the snake
    Snake();  // Constructor to initialize the snake
    void move();  // Move the snake in the current direction
    void changeDirection(int newDirection);  // Change the snake's direction
    void grow();  // Grow the snake
    bool checkCollision(int boardWidth, int boardHeight);  // Check collision with walls or itself
    bool getBody(int x1,int y1) const;  // check if the snake's current body position covers (i,j)
    int getLength();
};

Snake::Snake()
{
    position[0].s_x=8;
    position[0].s_y=8;
    length=1;
    direction=3;
}

int Snake::getLength()
{
	return length;
}
void Snake::move()
{
    for(int i=length-1;i>0;i--)
    {
        position[i].s_x=position[i-1].s_x;
        position[i].s_y=position[i-1].s_y;

    }
//    cout<<"direct: "<<direction<<endl;
    if(direction==2)
    {
//    	cout<<position[0].s_x<<",  "<<position[0].s_y<<endl;
        position[0].s_y=position[0].s_y-1;
    }
    else if(direction==3)
    {
//    	cout<<position[0].s_x<<",  "<<position[0].s_y<<endl;
        position[0].s_y=position[0].s_y+1;
    }
    else if(direction==0)
    {
//    	cout<<position[0].s_x<<",  "<<position[0].s_y<<endl;
        position[0].s_x=position[0].s_x-1;
    }
    else if(direction==1)
    {
//    	cout<<position[0].s_x<<",  "<<position[0].s_y<<endl;
        position[0].s_x=position[0].s_x+1;
    }
//    cout<<position[0].s_x<<",  "<<position[0].s_y<<endl;
}

void Snake::changeDirection(int newDirection)
{
    direction=newDirection;
//    move();
}

void Snake::grow()
{
    for(int i=length;i>0;i--)
    {
        position[i].s_x=position[i-1].s_x;
        position[i].s_y=position[i-1].s_y;
    }
    if(direction==2)
    {
        position[0].s_y=position[0].s_y-1;
    }
    else if(direction==3)
    {
        position[0].s_y=position[0].s_y+1;
    }
    else if(direction==0)
    {
        position[0].s_x=position[0].s_x-1;
    }
    else if(direction==1)
    {
        position[0].s_x=position[0].s_x+1;
    }

    length++;
}

bool Snake::getBody(int x1, int y1) const
{
//	cout<<"( "<<x1<<" , "<<y1<<" )";
    for(int i=0;i<length;i++)
    {
        if((position[i].s_x==x1) && (position[i].s_y==y1))
        {
        	
            return true;
        }
    }
    return false;

}

bool Snake::checkCollision(int boardWidth, int boardHeight) // true== collid , false== normal
{
    //check collid itself
    for(int i=1;i<length;i++)
    {
        if((position[0].s_x==position[i].s_x) && (position[0].s_y==position[i].s_y))
        {
            return true;
        }
    }
    if(position[0].s_x<=0 || position[0].s_x>=boardWidth-1 || position[0].s_y<=0 || position[0].s_y>=boardHeight-1)
    {
        return true;
    }
    return false;
}

////////////////////////////////////define food
class Food {
public:
    int x=0;
    int y=0;  // Position of the food
    void generateFood(int boardWidth, int boardHeight,const Snake& snake);  // Randomly place food on the board
};

void Food::generateFood(int boardWidth, int boardHeight, const Snake& snake )
{
    srand(time(0));
    do
    {

        x = rand() % (boardWidth-2) + 1;

        y = rand() % (boardHeight-2) + 1;
    }while( snake.getBody(x,y)!=0);

}


///////////////////////////////////define board

class Board {
private:
    int width, height;

public:
    Board();  // Constructor to set board dimensions
    void draw(const Snake& snake, const Food& food, const int score, const int length) const;  // Draw the board, snake, and food
};

Board::Board()
{
    width=N;
    height=N;
}

void Board::draw(const Snake& snake, const Food& food, const int score, const int length) const
{
	int score_wd=12;
    for(int i=0;i<height;i++)
    {
    	int tmp_flg=0;
        for(int j=0;j<width+score_wd;j++)
        {
            if(i==0 || i==height-1)
            {
                cout<<"==";
            }
            else if(j==0 || j==width-1 )
            {
                cout<<" |";
            }
            else if(j>=width and i==8 and tmp_flg==0)
            {
            cout<<" Score: "<<score;
            tmp_flg=1;
				
			}  
			else if(j>=width and i==13 and tmp_flg==0)
            {
            cout<<" length: "<<length;
            tmp_flg=1;
				
			}            
            else
            {
                if(snake.getBody(i,j)==1)
                {
                    cout<<" *";
                }
                else if(food.x==i && food.y==j)
                {
                    cout << " бя";
                }
                else
                {
                    cout<<"  ";
                }
            }
        }
        cout<<'\n';
    }
}


//define games
//
class Game {
private:
    Snake snake;
    Food food;
    int score;
    Board board;
    int game_speed;
    bool gameOver;

public:
    Game(int boardWidth, int boardHeight,int spd);  // Initialize the game
    int run();  // Main game loop
//    void processInput();  // Handle user input
    bool update();  // Update game state
//    void render();  // Draw the game state
};
Game::Game(int boardWidth, int boardHeight,int spd)
{

    food.generateFood(boardWidth,boardHeight,snake);
	score=0;
    gameOver= false;
    game_speed=spd;
}

int Game::run()
{
    while(!gameOver)
    {

        
//		system("cls");
		gotoxy(0,0); 
        board.draw(snake,food,score , snake.getLength());
		update();
        

    }
    return 0;

}
int game_run=0;
bool Game::update()
{


	game_run=1;
    start = clock();

    while((clock()-start<=game_speed)&&!kbhit());
//	getch();
//    key = getch();
    if(clock()-start<=game_speed)  
    {
        getch();  

        key = getch();  
    }  
    if(key == ' ')
    {
        while(getch()!=' '){};
    }
    switch(key)
    {
        case 72: direction=0;break;
        case 80:  direction=1;break;
        case 75:  direction=2;break;
        case 77:  direction=3;
    }
    snake.changeDirection(direction);
    if(snake.checkCollision(N,N))
    {
        gameOver= true;
    }
    if(snake.getBody(food.x,food.y))
    {
        snake.grow();
        score+=50*400/game_speed;
        food.generateFood(N,N,snake);
    }
    snake.move();
    

//	cout<<"game_flg  "<<gameOver;

    return  gameOver;
}

int choose_mod()
{

	char tmp_key='0';
	do
	{ 
		system("cls");
		cout << "\n\n\n\n\n\t\t\t Choose your game mode!" << endl;
		cout << "\n\t\t\t 1. Easy (speed slow)" << endl;
		cout << "\n\t\t\t 2. Medium (normal speed)" << endl;
		cout << "\n\t\t\t 3. Hard (fast speed)" << endl;
		
		cout << "\n\t\t\t (Input number to choose model)" << endl;
		tmp_key=getch();
	}while(tmp_key!='1' &&tmp_key!='2' &&tmp_key!='3' );
	if(tmp_key=='1')
	{
		return 400;
	}
	else if(tmp_key=='2')
	{
		return 200;
	}
	else
	{
		return 100;
	}
	
}

void move(int x,int y)
{
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos={x,y};
SetConsoleCursorPosition(hOut,pos);
}

void hideCursor() {
    // Get console handle
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Get current cursor info
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    
    // Set the cursor visibility to false (hide cursor)
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void gotoxy(int x,int y){
	int xx=0x0b;
	HANDLE hOutput;
	COORD loc;
	loc.X=x;
	loc.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,loc);
}
int main() {
    char ctn = 'y';

    int nodead;

    cout << "\n\n\n\n\n\t\t\t Welcome to the Greedy Snake!" << endl;
    cout << "\n\n\n\t\t\t Press any keys to start" << endl;//starting
    getch();  //just press
    int input_speed=choose_mod();

    hideCursor();
    while (ctn == 'y')
    {
    	Game game1(N,N,input_speed);
    	int flg=1;
//        system("cls");
//        cout<<"let's play";
        flg=game1.run();
        if(flg==0)
        {
        	system("cls");
            cout<<" \n\n\n\n\n\t\t\tgame over!"<< endl;
            cout<<" \n\n\n\n   Play Again? y  or  n  ?"<<endl;
            ctn=getch();
        }



    }
}
