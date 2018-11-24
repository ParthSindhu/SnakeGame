// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>
#include <conio.h>

using namespace std;

enum edir
{
	stop,
	Left,
	Right,
	up,
	down
};

class snake
{
private:
	int length;
	int curx, cury;
	int originalx, originaly;
	vector<int> x, y;
	edir direction;
public:
	snake(int posx,int posy) 
	{
		originalx = posx;
		originaly = posy;
		curx = originalx;
		cury = originaly;
		length = 10;
		for (int i=0;i<length;i++)
		{
			y.push_back(originaly);
			x.push_back(originalx + i + 1);
		}
	}

	int getx()
	{
		return curx;
	}

	int gety()
	{
		return cury;
	}

	vector<int> getallx()
	{
		return x;
	}

	vector<int> getally()
	{
		return y;
	}


	int getlength()
	{
		return length;
	}

	void collision(int posx,int posy)
	{
		curx = posx;
		cury = posy;
		length++;
		x.push_back(curx);
		y.push_back(cury);
	}

	inline void changedirection(edir d)
	{
		direction = d;
	}

	void move()
	{
		switch (direction)
		{
		case stop:
			break;
		case up:
			cury--;
			y.push_back(cury);
			x.push_back(curx);
			x.erase(x.begin());
			// system("pause");
			//for (int p = 0; p < y.size(); p++)
				//cout << "(" << x[p] << "," << y[p] << ") ";
			//system("pause");
			y.erase(y.begin());
			break;
		case down:
			cury++;
			y.push_back(cury);
			x.push_back(curx);
			y.erase(y.begin());
			x.erase(x.begin());
			
			break;
		case Left:
			curx--;
			x.push_back(curx);
			y.push_back(cury);
			x.erase(x.begin());
			y.erase(y.begin());
			
			break;
		case Right:
			curx++;
			x.push_back(curx);
			y.push_back(cury);
			x.erase(x.begin());
			y.erase(y.begin());
			
			break;
		}
	}

	void printcordinates()
	{
		for (int p = 0; p < x.size(); p++)
			cout << "(" << x[p] << "," << y[p] << ") ";
		
	}

	edir getdir()
	{
		return direction;
	}
};

class food
{
private:
	int x;
	int y;
public:
	food(int posx, int posy)
	{
		x = posx;
		y = posy;
	}

	int getx()
	{
		return x;
	}

	int gety()
	{
		return y;
	}
};

class gamemanager
{
private:
	int width, height;
	snake * csnake;
	food * newfood;
	char upc, downc, rightc, leftc;
	bool quit;
	int score;
public:
	gamemanager(int w , int h)
	{
		width = w; height = h;
		csnake = new snake(0, height / 2);
		newfood = new food(width / 2, height / 2);
		quit = false;
		upc = 'w';
		downc = 's';
		rightc = 'd';
		leftc = 'a';
		score = 0;
	}

	~gamemanager() 
	{
		delete newfood, csnake;
	}

	void draw()
	{
		system("cls");
		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;
		
		int foodx = newfood->getx();
		int foody = newfood->gety();
		vector<int> snakeallx = csnake->getallx();
		vector<int> snakeally = csnake->getally();

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j <= width; j++)
			{
				bool g = true;
				if (j == 0)
					cout << "\xB2";

				//cout << foodx << foody ;
				//cout << j << i; 


				if (j == foodx && i == foody)
				{
					cout << "o";
				}
				for (int p = 0; p < snakeallx.size(); p++)
				{
					if (i == snakeally[p] && j == snakeallx[p])
					{
						cout << "\xB2";
						g = false;
					}
				}
				if (j == width)
					cout << "\xB2";
				if (g)
					cout << " ";
			}
			cout << endl;
		}

		for (int i = 0; i < width + 2; i++)
			cout << "\xB2";
		cout << endl;

		cout << "Score :" << score << endl;
		cout << "Snake Cordinates:";
		csnake->printcordinates();

	}

	void input()
	{
		csnake->move();

		int snakex = csnake->getx();
		int snakey = csnake->gety();

		if (_kbhit())
		{
			char current = _getch();
			if (current == upc)
				if (snakey > 0)
				{
					csnake->changedirection(up);
					csnake->move();
				}
			if (current == downc)
				if (snakey < height)
				{
					csnake->changedirection(down);
					csnake->move();
				}
			if (current == leftc)
				if (snakex > 0)
				{
					csnake->changedirection(Left);
					csnake->move();
				}
			if (current == rightc)
				if (snakex < width)
				{
					csnake->changedirection(Right);
					csnake->move();
				}
			if (current == 'q')
				quit = true;
		}

	}

	void logic()
	{
		int snakex = csnake->getx();
		int snakey = csnake->gety();
		int foodx = newfood->getx();
		int foody = newfood->gety();	
		int length = csnake->getlength();

		if (snakex == foodx && snakey == foody)
		{
			if (csnake->getdir() == up )
			{
				csnake->collision(foodx, --foody);
			}
			if (csnake->getdir() == down)
			{
				csnake->collision(foodx, ++foody);
			}
			if (csnake->getdir() == Right)
			{
				csnake->collision(++foodx, foody);
			}
			if (csnake->getdir() == Left)
			{
				csnake->collision(--foodx, foody);
			}
			makefood();
			score++;
			system("pause");
		}


		if (snakey == height+1)
		{
			reset();
			score--;
			system("pause");
		}

		if (snakey == -1)
		{
			reset();
			score--;
		}
		if (snakex == width+1)
		{
			reset();
			score--;
		}
		if (snakex == -1)
		{
			reset();
			score--;
		} 
	}

	void reset() 
	{
		csnake = new snake(0, height / 2);
	}

	void run()
	{
		while (!quit)
		{
			draw();
			input();
			logic();
		}
	}

	void makefood()
	{
	
		vector<int> snakeallx = csnake->getallx();
		vector<int> snakeally = csnake->getally();
		vector <int> row1;
		vector <int> row2;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for(int p=0;p < snakeallx.size() ;p++)
				if (i != snakeally[p] && j != snakeallx[p])
				{
					row1.push_back(i);
					row2.push_back(j);
				}
			}
		}
		
		int z = rand() % row1.size();

		cout << endl << "Food Coordinate:" << "(" << row2[z] << "," << row1[z] << ")" << endl;

		newfood = new food(row2[z], row1[z]);
	}


};

int main()
{
	system("Title snake game");
	system("mode 650");
	gamemanager newgame(50, 25);
	newgame.run();
    return 0;
}

