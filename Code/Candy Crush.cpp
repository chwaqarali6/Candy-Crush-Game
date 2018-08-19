#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>

#include "Header.h"
#include "Console.h"


//Defining Constants
#define UP		72
#define DOWN	80
#define RIGHT	77
#define LEFT	75
#define ENTER	13

#define RED		12
#define YELLOW	14
#define GREEN	10
#define BLUE	9
#define WHITE	15
#define BLINK	128

using namespace std;

//Protype Of Function 
void FrontPage();
void PrintTable(int Row, int Col, int Width);
void CandyPlace(int RowArray[][6], int ColArray[][6], int Row, int Col);
void GenerateCandy(char Candy[][6], int Row, int Col);
void PlaceCandies(char Candy[][6], int RowArray[][6], int ColArray[][6], int Row, int Col, int Width);
void Pointer(char Candy[][6], int RowArray[][6], int ColArray[][6], int Row, int Col, int Width, int &i, int &j, int &m, int &n);
void Swap(char &Candy1, char &Candy2);
void Check(char Candy[][6],int &Score);
void RowPopper(char Candy[][6],int StartX, int StartY, int EndX, int EndY, int &Score);
void ColPopper(char Candy[][6],int StartX, int StartY, int EndX, int EndY, int &Score);
void HighScore(int Score);

void main()
{
	const int Width=40;
	const int Row=6, Col=6;
	char Candy[Row][Col]={0};
	int RowArray[Row][Col]={0};
	int ColArray[Row][Col]={0};
	int Score=0;
	int i=0,j=0,m=0,n=0;

	FrontPage();
	clrscr();
	PrintTable(Row, Col, Width);
	CandyPlace(RowArray, ColArray, Row, Col);
	GenerateCandy(Candy, Row, Col);
	PlaceCandies(Candy, RowArray, ColArray, Row, Col, Width);

	for (int Moves=10; Moves>0;)
	{
		i=0,j=0,m=0,n=0;
		Pointer(Candy, RowArray, ColArray, Row, Col, Width, i, j, m, n);
		Swap(Candy[i][j],Candy[m][n]);
		Check(Candy,Score);
		Check(Candy,Score);
		Check(Candy,Score);
		Check(Candy,Score);
		PlaceCandies(Candy, RowArray, ColArray, Row, Col, Width);		
		Moves--;
		gotoxy(0,16);
		textcolor(10);
		cout<<"Score:\t\t"<<Score<<endl;
		cout<<"Moves Left:\t"<<Moves<<endl;		
	}
	HighScore(Score);

	_getch();
}

void FrontPage() //FRONT PAGE OF  PROGRAM
{
	cout<<"  CANDYCRUSH CANDY CRUSH   	CANDYCRUSH CANDY CRUSH"<<endl; 
    cout<<"  CANDYCRUSH CANDY CRUSH   	CANDYCRUSH CANDY CRUSH"<<endl;  
	cout<<"  CANDYCRUSH CANDY CRUSH   	CANDYCRUSH CANDY CRUSH"<<endl; 
    cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl;
	cout<<"  CANDYCRUSH		  	CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl;
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH			CANDYCRUSH"<<endl; 
	cout<<"  CANDYCRUSH CANDY CRUSH   	CANDYCRUSH CANDY CRUSH"<<endl; 
	cout<<"  CANDYCRUSH CANDY CRUSH   	CANDYCRUSH CANDY CRUSH"<<endl;   
	cout<<"  CANDYCRUSH CANDY CRUSH   	CANDYCRUSH CANDY CRUSH"<<endl; 
	cout << endl;
	cout << "INSTRUCTIONS:-" << endl;
	cout << "1. Use Arrows to Move" << endl;
	cout << "2. Press Enter to Select First Candy" << endl;
	cout << "3. Use Arrow to Swap with Second Candy" << endl;
	cout<<endl<<endl;
	cout<<"PLEASE PRESS ENTER TO PLAY:-"; 
	int Input=getch();
}

void PrintTable(int Row, int Col, int Width) //PRINT SOLID TABLE
{
	int XCord1=0, YCord1=0, XCord2=Width, YCord2=Width;	
	for(int i=0; i<Row; i++)
	{
		for(int j=0; j<Col; j++)
		{
			myRect(XCord1,YCord1,XCord2,YCord2,RGB(255,255,255),RGB(0,0,0));
			XCord1=XCord1+Width;
			XCord2=XCord2+Width;
		}		
		XCord1=0;
		XCord2=Width;
		YCord1=YCord1+Width-14;
		YCord2=YCord2+Width-14;
	}
}

void CandyPlace(int RowArray[][6], int ColArray[][6], int Row, int Col)  //GETS LOCATION OF CANDY
{
	int PointerX=2;
	int PointerY=1;
	int Inc_DecX=5;
	int Inc_DecY=2;
	
	for(int i=0;i<Row;i++)
	{
		for(int j=0;j<Col;j++)
		{
			RowArray[i][j]=PointerX;
			ColArray[i][j]=PointerY;
			PointerX=PointerX +Inc_DecX;
		}
		PointerX=2;
		PointerY=PointerY+Inc_DecY;
	}
}

void GenerateCandy(char Candy[][6], int Row, int Col) //GENERATE RANDOM CANDIES
{
	const int NumberOfCandies=4;
	char Candies[NumberOfCandies]={'R','Y','G','B'};
	int Select=0, Seed=0;
	time_t t;
	Seed=time(&t);

	for(int i=0; i<Row; i++)
	{
		for(int j=0; j<Col; j++)
		{				
			srand(Seed);			
			Select=rand()%4;
			Candy[i][j]=Candies[Select];
			Seed=Seed+2;		
		}
	}
}

void PlaceCandies(char Candy[][6], int RowArray[][6], int ColArray[][6], int Row, int Col, int Width) // PRINT CANDIES
{
	PrintTable(Row, Col, Width);
	for(int i=0; i<Row; i++)
	{

		for(int j=0; j<Col; j++)
		{
			gotoxy(RowArray[i][j],ColArray[i][j]);
			if(Candy[i][j]=='R')
				textcolor(RED);
			else if(Candy[i][j]=='Y')
				textcolor(YELLOW);
			else if(Candy[i][j]=='G')
				textcolor(GREEN);
			else if(Candy[i][j]=='B')				
				textcolor(BLUE);		
			cout<<Candy[i][j];
			gotoxy(RowArray[i][j],ColArray[i][j]);			
		}
	}
}

void Pointer(char Candy[][6], int RowArray[][6], int ColArray[][6], int Row, int Col, int Width, int &i,int &j, int &m, int &n) //TAKES USER INPUT
{
	int Input;
	int PointerX=2;
	int PointerY=1;
	int Inc_DecX=5;
	int Inc_DecY=2;

	int Selections=0;	

	gotoxy(PointerX,PointerY);	
	cout<<Candy[i][j];
	gotoxy(PointerX,PointerY);	

	while(Selections<1)
	{		
		Input=getch();	
		if(Input==RIGHT && j<Col-1)
		{	
			gotoxy(PointerX,PointerY);
			if(Candy[i][j]=='R')
				textcolor(RED);
			else if(Candy[i][j]=='Y')
				textcolor(YELLOW);
			else if(Candy[i][j]=='G')
				textcolor(GREEN);
			else if(Candy[i][j]=='B')				
				textcolor(BLUE);	
			cout<<Candy[i][j];
			j++;
			PointerX=PointerX+Inc_DecX;
			gotoxy(PointerX,PointerY);
			textcolor(WHITE);
			cout<<Candy[i][j];
			gotoxy(PointerX,PointerY);			
		}
		else if(Input==LEFT && j>0)
		{
			gotoxy(PointerX,PointerY);
			if(Candy[i][j]=='R')
				textcolor(RED);
			else if(Candy[i][j]=='Y')
				textcolor(YELLOW);
			else if(Candy[i][j]=='G')
				textcolor(GREEN);
			else if(Candy[i][j]=='B')				
				textcolor(BLUE);	
			cout<<Candy[i][j];
			--j;
			PointerX=PointerX-Inc_DecX;
			gotoxy(PointerX,PointerY);
			textcolor(WHITE);
			cout<<Candy[i][j];				
		}
		else if(Input==UP && i>0)	
		{
			gotoxy(PointerX,PointerY);
			if(Candy[i][j]=='R')
				textcolor(RED);
			else if(Candy[i][j]=='Y')
				textcolor(YELLOW);
			else if(Candy[i][j]=='G')
				textcolor(GREEN);
			else if(Candy[i][j]=='B')				
				textcolor(BLUE);	
			cout<<Candy[i][j];
			--i;
			PointerY=PointerY-Inc_DecY;
			gotoxy(PointerX,PointerY);
			textcolor(WHITE);
			cout<<Candy[i][j];					
		}
		else if(Input==DOWN && i<Row-1)
		{
			gotoxy(PointerX,PointerY);
			if(Candy[i][j]=='R')
				textcolor(RED);
			else if(Candy[i][j]=='Y')
				textcolor(YELLOW);
			else if(Candy[i][j]=='G')
				textcolor(GREEN);
			else if(Candy[i][j]=='B')				
				textcolor(BLUE);	
			cout<<Candy[i][j];
			++i;
			PointerY=PointerY+Inc_DecY;
			gotoxy(PointerX,PointerY);
			textcolor(WHITE);
			cout<<Candy[i][j];
		}
		else if(Input==ENTER)
		{	
			gotoxy(PointerX,PointerY);
			textcolor(BLINK);
			if(Selections==0)
			{
				m=i;
				n=j;
			}
			cout<<Candy[i][j];
			++Selections;
		}		
	}
	while(Selections<2)
	{
		Input=getch();
		if(Input==RIGHT && j<Col-1)
		{
			j++;
			++Selections;
		}
		else if(Input==LEFT && j>0)
		{
			--j;
			++Selections;
		}
		else if(Input==UP && i>0)	
		{
			--i;
			++Selections;
		}
		else if(Input==DOWN && i<Row-1)
		{
			++i;
			++Selections;
		}
	}
}

void Swap(char &Candy1, char &Candy2) //SWAP SELECTED CANDIES
{
	char Temp='\0';
	Temp=Candy2;
	Candy2=Candy1;
	Candy1=Temp;
}

void Check(char Candy[][6],int &Score) //CHECK FROM WHERE THE COMBINATION STARTS AND END
{
	char Target='\0';
    int Count = 1;

	int StartX=0;
	int StartY=0;
	int EndX=0;
	int EndY=0;

    for(int i = 0; i < 6; i++)
    {
         Target= Candy[i][0];
		 StartX=i;
		 StartY=0;
        for(int j = 1; j < 6; j++)
        {
            if(Candy[i][j] ==Target)
            {
                ++Count;
            }
            else
            {
                Target=Candy[i][j];
				StartX=i;
				StartY=j;
                Count = 1; 
            }
            if(Count == 3)  
            {
                EndX=i;
				EndY=j;
				RowPopper(Candy,StartX,StartY,EndX,EndY,Score);
            }
        }
    }
	for(int j = 0; j < 6; j++)
    {
         Target= Candy[0][j];
		 StartX=0;
		 StartY=j;
        for(int i = 1; i < 6; i++)
        {
            if(Candy[i][j]==Target)
            {
                ++Count;
            }
            else
            {
                Target= Candy[i][j];
				StartX=i;
				StartY=j;
                Count= 1; 
            }
            if(Count==3)  
            {
                EndX=i;
				EndY=j;
				ColPopper(Candy,StartX,StartY,EndX,EndY,Score);
            }
        }
    }
}
void RowPopper(char Candy[][6],int StartX, int StartY, int EndX, int EndY, int &Score)  //POPS COMBINATIONS IN ROWS
{
	char Candies[4]={'R','Y','G','B'};
	int SelectedCandy=0;

	for(int j=StartY;j<=EndY;j++)
	{
		if(StartX>0)
		{
			for(int i=StartX;i>0;i--)
			{
				Candy[i][j]=Candy[i-1][j];
			}
			SelectedCandy=rand() % 4;
			Candy[0][j]=Candies[SelectedCandy];
			Score=Score+10;
		}
		else
		{
			SelectedCandy=rand() % 4;
			Candy[0][j]=Candies[SelectedCandy];
			Score=Score+10;
		}
	}
}
void ColPopper(char Candy[][6],int StartX, int StartY, int EndX, int EndY, int &Score)  //POP CANDIES IN COLUMNS
{
	char Candies[4]={'R','Y','G','B'};
	int SelectedCandy=0;	

	for(int j=StartY;j<=EndY;j++)
	{
		if(StartX>0)
		{
		
			for(int i=StartX-1;i>=0;i--)
			{
				Candy[EndX][j]=Candy[i][j];
				EndX--;
			}
			for(EndX;EndX>=0;EndX--)
			{
				SelectedCandy=rand() % 4;
				Candy[EndX][j]=Candies[SelectedCandy];
			}
			Score=Score+10;
		}
		else
		{
			for(int i=0;i<=EndX;i++)
			{
				SelectedCandy=rand() % 4;
				Candy[i][j]=Candies[SelectedCandy];
			}
			Score=Score+10;
		}
	}
}

void HighScore(int Score)  //SAVES HIGHSCORE
{
	int HighScore;
	ifstream fin;
	fin.open("Score.txt");
	if(fin)
	{
		fin>>HighScore;
	}
	else
	{
		cout<<"File Could Not Be Opened";
	}
	fin.close();

	if(HighScore<Score)
	{
		ofstream fout;
		fout.open("Score.txt");
		if(fout)
		{
			fout<<Score;
			cout<<"Congrats! You Have Made The Highest Score:- "<<Score<<endl;
		}
		else
		{
			cout<<"File Could Not Be Opened";
		}
	}	
	else
	{
		cout<<"Highest Score Uptil Now Is:- "<<HighScore;
	}

}