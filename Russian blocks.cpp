#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#define BS1 4
#define BS2 6
#define N 16
#define M 30 
#define BLK_NUM 2
using namespace std;

int direction=0;
int start;
char key;


void gotoxy(int x,int y){
	int xx=0x0b;
	HANDLE hOutput;
	COORD loc;
	loc.X=x;
	loc.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,loc);
}
class block_pos{
	public:
		int b_x;
		int b_y;
		block_pos(){
			b_x=0;
			b_y=0;
		}
		void initialize(int x, int y);
		
};

void block_pos::initialize(int x,int y)
{
	b_x=x;
	b_y=y;
}

block_pos tmp[2][8];

/////////////////////////////////////////////////////
class blocks//2*2 square
{
	
	public:
		block_pos bs1[2][8];
		int block_ind;
//		int lowest_point;
	
	
		blocks(int cls_ind);
		int get_left();
		int get_right();
		int get_bottom();
		void move(int direction);
		void initialize();
		void fall();
		bool is_blk(int x,int y);
		void rotate();//press a to rotate  clockwise
	
	
};

blocks::blocks(int cls_ind)
{
	block_ind=cls_ind;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<8;j++)
		{
			bs1[i][j].b_x=0;
			bs1[i][j].b_y=0;
		}
	}
	//0->square
	bs1[0][0].b_y=N/2;
	bs1[0][1].b_y=N/2+1;
	bs1[0][2].b_x=1;
	bs1[0][2].b_y=N/2;
	bs1[0][3].b_x=1;
	bs1[0][3].b_y=N/2+1;
	//1:skinny rect
	bs1[1][0].b_y=N/2-1;
	bs1[1][1].b_y=N/2;
	bs1[1][2].b_y=N/2+1;
	bs1[1][3].b_y=N/2+2;
	
}

void blocks::rotate()
{
	if(block_ind==0){
		;
	}
	else if(block_ind==1)
	{
		int center_x=bs1[1][1].b_x;
		int center_y=bs1[1][1].b_y;
		for(int j=0;j<4;j++)
		{
			int dx=bs1[1][j].b_x-center_x;
			int dy=bs1[1][j].b_y-center_y;
			int new_x=center_x-dy;
			int new_y=center_y+dx;
			bs1[1][j].b_x=new_x;
			bs1[1][j].b_y=new_y;
		}
		
	}
}
int blocks::get_left()
{
	int left_pos=N-1;
	for(int j=0;j<8;j++)
	{
		if(bs1[block_ind][j].b_x==0 && bs1[block_ind][j].b_y==0)
		{
			continue;
		}
		if(bs1[block_ind][j].b_y<left_pos)
		{
			left_pos=bs1[block_ind][j].b_y;
		}
	}
	return left_pos;
}

int blocks::get_right()
{
	int right_pos=0;
	for(int j=0;j<8;j++)
	{
		if(bs1[block_ind][j].b_x==0 && bs1[block_ind][j].b_y==0)
		{
			continue;
		}
		if(bs1[block_ind][j].b_y>right_pos)
		{
			right_pos=bs1[block_ind][j].b_y;
		}
	}
	return right_pos;
}
int blocks::get_bottom()
{
	int btm_pos=0;
	for(int j=0;j<8;j++)
	{
		if(bs1[block_ind][j].b_x==0 && bs1[block_ind][j].b_y==0)
		{
			continue;
		}
		if(bs1[block_ind][j].b_x>btm_pos)
		{
			btm_pos=bs1[block_ind][j].b_x;
		}
	}
	return btm_pos;
}
void blocks::initialize()
{
	srand(time(0));
	block_ind=rand()%2;
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<8;j++)
		{
			bs1[i][j].b_x=0;
			bs1[i][j].b_y=0;
		}
	}
	bs1[0][0].b_y=N/2;
	bs1[0][1].b_y=N/2+1;
	bs1[0][2].b_x=1;
	bs1[0][2].b_y=N/2;
	bs1[0][3].b_x=1;
	bs1[0][3].b_y=N/2+1;
	
	bs1[1][0].b_y=N/2-1;
	bs1[1][1].b_y=N/2;
	bs1[1][2].b_y=N/2+1;
	bs1[1][3].b_y=N/2+2;
	
}
bool blocks::is_blk(int x,int y)
{
	for(int j=0;j<8;j++)
	{
		if(bs1[block_ind][j].b_x==x && bs1[block_ind][j].b_y==y)
		{
			return true;
		}
	}
	return false;
}
void blocks::move(int direction)
{

	
	if(direction==1)//fall
	{
//		if(this->get_bottom()<M-2)
//		{for(int j=0;j<8;j++)
//		{
//			if(bs1[block_ind][j].b_x!=0 || bs1[block_ind][j].b_y!=0){
//				
//					bs1[block_ind][j].b_x+=1;
//				}
//			}
//		}

	}
	else if(direction==3)//right
	{
		if(this->get_right()<N-2)
		{for(int j=0;j<8;j++) 
		{
			if(bs1[block_ind][j].b_x!=0 || bs1[block_ind][j].b_y!=0){
					bs1[block_ind][j].b_y+=1;	
				}
							
			}
			
		}
	}
	else if(direction==2)//left
	{
		if(this->get_left()>1)
		{
		for(int j=0;j<8;j++) 
		{
			if(bs1[block_ind][j].b_x!=0 || bs1[block_ind][j].b_y!=0)
			{	
					bs1[block_ind][j].b_y-=1;	
			}

		}
		}
	}
	else
	{
		;
	}
	
 } 
 
void blocks::fall()
 {
 	for(int j=0;j<8;j++) 
	{
		if(bs1[block_ind][j].b_x!=0 || bs1[block_ind][j].b_y!=0){
			bs1[block_ind][j].b_x+=1;
		}
	}
//	cout<<"fall!";
 }
 

/////////////////////////////////////


class dump{
	private:
		int dump_body[M][N];
	public:
		dump();
		bool is_dump(int x,int y);
		void dump_absorb(blocks cur_blk);
		void dump_refresh();
		
		
		
};

dump::dump()
{
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==M-1)
			{
				dump_body[i][j]=1;					
			}
			else{
				dump_body[i][j]=0;		
			}
			
		}	
	}
}


bool dump::is_dump(int x,int y)
{
	if(dump_body[x][y]==1)
	{
		return true;
	}
	else{
		return false;
	}
}

void dump::dump_absorb(blocks cur_blk)
{
	for(int j=0;j<8;j++)
	{
		if(cur_blk.bs1[cur_blk.block_ind][j].b_x==0 && cur_blk.bs1[cur_blk.block_ind][j].b_y==0)
		{
			;
		}
		else
		{
			dump_body[cur_blk.bs1[cur_blk.block_ind][j].b_x][cur_blk.bs1[cur_blk.block_ind][j].b_y]=1;
		}
	}
}

void dump::dump_refresh()
{
	for(int i=M-2;i>0;i--)
	{
		bool tmp_flg=true;
		for(int j=1;j<N-1;j++)
		{
			if(dump_body[i][j]==0)
			{
				tmp_flg=false;
				break;
			}
		}
		if(tmp_flg)
		{
			for(int i1=i;i1>0;i1--)//delete this row and move all dump above one level down
			{
				for(int j1=1;j1<N-1;j1++)
				{
					dump_body[i1][j1]=dump_body[i1-1][j1];
				}
			}
			for(int j1=0;j1<N;j1++)
			{
				dump_body[0][j1]=0;
			}
			i=i+1;
			
		}
	}
}

/////////////////////////////////////
class board{
	
	private:
		int width=N;
		int height=M;
	public:
		void show_board(blocks cur_blk,dump cur_dump);
		bool is_collid(blocks cur_blk,dump cur_dump);
	
};

void board::show_board(blocks cur_blk,dump cur_dump)
{
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==0||i==M-1)
			{
				cout<<"==";
			}
			else if(j==0)
			{
				cout<<"| ";
			}
			else if(j==N-1)
			{
				cout<<" |";
			}
			else if( cur_blk.is_blk(i,j) )
			{
				cout<<" *";
			}
			else if(cur_dump.is_dump(i,j))
			{
				cout<<" +";
			}
			else
			{
				cout<<"  ";
			}
		}
		cout<<endl;
		
	}
}


bool board::is_collid(blocks cur_blk,dump cur_dump){
	int x,y;
	for(int j=0;j<8;j++)
	{
		x=cur_blk.bs1[cur_blk.block_ind][j].b_x;
		y=cur_blk.bs1[cur_blk.block_ind][j].b_y;
		if(x>=M-1)
		{
			return true;
		}
		if(cur_dump.is_dump(x,y))
		{
			return true;
		}
	}
	return false;
}

/////////////////////////////////



class Game{
	private:
		int game_speed;
		board game_board;
		dump game_dump;
		blocks game_block;
		bool gameOver;
	
	public:
		Game():game_block(0)
		{
			game_speed=250;
			gameOver= false;
		}
		int run();
		bool update();
		
		
};

bool Game::update()
{
	for(int i=0;i<BLK_NUM;i++)
	{
		for(int j=0;j<8;j++)
		{
			tmp[i][j].b_x=game_block.bs1[i][j].b_x;
			tmp[i][j].b_y=game_block.bs1[i][j].b_y;
		}
	}
	key=70;
	start=clock();
    while((clock()-start<=game_speed)&&!kbhit());
	int time=clock()-start;
    if(time<=game_speed)  
    {
        getch();  
        key = getch();  
    }	
    switch(key)
    {
        case 72: direction=4;break;//rotate
        case 80:  direction=1;break;//down
        case 75:  direction=2;break;//left
        case 77:  direction=3;//right
    }
    if(direction!=0)
	{
		if(direction==4)
		{
			game_block.rotate();
		}
		else
		{
			game_block.move(direction);
		}
		
		direction=0;
    }
	
	
    
    if(game_board.is_collid(game_block,game_dump))
    {
    	for(int i=0;i<BLK_NUM;i++)
		{
			for(int j=0;j<8;j++)
			{
				game_block.bs1[i][j].b_x=tmp[i][j].b_x;
				game_block.bs1[i][j].b_y=tmp[i][j].b_y;
			}
		}
        game_dump.dump_absorb(game_block);
        game_dump.dump_refresh();
        game_block.initialize();
        return  gameOver;
    }
    if(time>0.5*game_speed)
    {
    	game_block.fall();	
	}
	
    if(game_board.is_collid(game_block,game_dump))
    {
    	for(int i=0;i<BLK_NUM;i++)
		{
			for(int j=0;j<8;j++)
			{
				game_block.bs1[i][j].b_x=tmp[i][j].b_x;
				game_block.bs1[i][j].b_y=tmp[i][j].b_y;
			}
		}
        game_dump.dump_absorb(game_block);
        game_dump.dump_refresh();
        game_block.initialize();
        return  gameOver;
    }

//	cout<<"game_flg  "<<gameOver;

    return  gameOver;
}

int Game::run()
{
//	int start;
//	start=clock();
	while(!gameOver)
    {
		
        direction=0;
//		system("cls");
		gotoxy(0,0); 
        game_board.show_board(game_block,game_dump);
		update();
		cout<<"run!";        

    }
    return 0;
	
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

int main()
{
	cout<<"================================================="<<endl;
	cout<<endl<<endl;
	cout<<"            Welcome to Russian Blocks"<<endl;
	cout<<endl<<endl;
	cout<<"             Press Any Key to Start"<<endl;
	cout<<endl<<endl;
	cout<<"================================================="<<endl;
	getch();
	
	hideCursor();
	char ctn='y';
    while (ctn == 'y')
    {
    	Game myGame;
    	int flg=1;
//        system("cls");
//        cout<<"let's play";
        flg=myGame.run();
        if(flg==0)
        {
        	system("cls");
            cout<<" \n\n\n\n\n\t\t\tgame over!"<< endl;
            cout<<" \n\n\n\n   Play Again? y  or  n  ?"<<endl;
            ctn=getch();
        }
    }
	
	
	
	
 } 

