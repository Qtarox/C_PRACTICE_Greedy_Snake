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
};

Snake::Snake()
{
    position[0].s_x=2;
    position[0].s_y=2;
    length=1;
    direction=3;
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
    if(position[0].s_x<=0 || position[0].s_x>=boardWidth || position[0].s_y<=0 || position[0].s_y>=boardHeight)
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
    void draw(const Snake& snake, const Food& food) const;  // Draw the board, snake, and food
};

Board::Board()
{
    width=N;
    height=N;
}

void Board::draw(const Snake& snake, const Food& food) const
{
    for(int i=0;i<width;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(i==0 || i==height-1)
            {
                cout<<" =";
            }
            else if(j==0 || j==width-1)
            {
                cout<<" |";
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

    gameOver= false;
    game_speed=spd;
}

int Game::run()
{
    while(!gameOver)
    {

        system("cls");
        board.draw(snake,food);
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

int main() {
    char ctn = 'y';

    int nodead;

    cout << "\n\n\n\n\n\t\t\t Welcome to the Greedy Snake!" << endl;
    cout << "\n\n\n\t\t\t Press any keys to start" << endl;//starting
    getch();  //just press
    int input_speed=choose_mod();
    Game game1(N,N,input_speed);
    int flg=1;
    while (ctn == 'y')
    {
//        system("cls");
//        cout<<"let's play";
        flg=game1.run();
        if(flg==0)
        {
            cout<<" game over!";
            break;
        }



    }
}
