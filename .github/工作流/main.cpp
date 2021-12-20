#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;
//copy from a guys who called AceTan

int const ROW = 4;
int const COL = 4;
int game[ROW][COL] = { 0 };

int const UP = 1;
int const DOWN = 2;
int const LEFT = 3;
int const RIGHT = 4;

int const GAME_OVER = 1;
int const GAME_WIN = 2;
int const GAME_CONTINUE = 3;

enum GameNum
{
	Game_2 = 2,
	Game_4 = 4,
	Game_8 = 8,
	Game_16 = 16,
	Game_32 = 32,
	Game_64 = 64,
	Game_128 = 128,
	Game_256 = 256,
	Game_512 = 512,
	Game_1024 = 1024,
	Game_2048 = 2048,

};

void Print()
{
	system("cls");
	std::cout << "**********2048**********" << endl;



	for (int i = 0; i < ROW; ++i)
	{
		std::cout << "_____________________" << endl;
		for (int j = 0; j < COL; ++j)
		{
			if (game[i][j] == 0)
			{
				std::cout << "|    \t";
			}
			else
			{
				std::cout << "|    " << game[i][j] << "\t";
			}
		}
		std::cout << "|" << endl;
	}
	std::cout << "_____________________" << endl;
}

bool CreateNumber()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = ROW * COL;

	int whitch = rand() % 3;
	do
	{
		x = rand() % ROW;
		y = rand() % COL;

	} while (game[x][y] != 0 && times <= maxTimes);

	if (times >= maxTimes)
	{
		return false;
	}
	else
	{
		GameNum num;
		if (whitch == 0)
		{
			num = Game_4;
		}
		else if (whitch)
		{
			num = Game_2;
		}
		game[x][y] = num;
	}

	return true;
}

void Process(int direction)
{

	switch (direction)
	{
	case UP:
		for (int row = 1; row < ROW; ++row)
		{
			for (int crow = row; crow >= 1; --crow)
			{
				for (int col = 0; col < COL; ++col)
				{
					if (game[crow - 1][col] == 0)
					{
						game[crow - 1][col] = game[crow][col];
						game[crow][col] = 0;
					}
					else
					{
						if (game[crow - 1][col] == game[crow][col])
						{
							game[crow - 1][col] *= 2;
							game[crow][col] = 0;
						}
					}

				}
			}
		}
		break;




	case DOWN:
		for (int row = ROW - 2; row >= 0; --row)
		{
			for (int crow = row; crow < ROW - 1; ++crow)
			{
				for (int col = 0; col < COL; ++col)
				{
					if (game[crow + 1][col] == 0)
					{

						game[crow + 1][col] = game[crow][col];
						game[crow][col] = 0;
					}
					else
					{
						if (game[crow + 1][col] == game[crow][col])
						{
							game[crow + 1][col] *= 2;
							game[crow][col] = 0;
						}
					}
				}
			}
		}
		break;
	case LEFT:
		for (int col = 1; col < COL; ++col)
		{
			for (int ccol = col; ccol >= 1; --ccol)
			{
				for (int row = 0; row < ROW; ++row)
				{
					if (game[row][ccol - 1] == 0)
					{
						game[row][ccol - 1] = game[row][ccol];
						game[row][ccol] = 0;
					}
					else
					{
						if (game[row][ccol - 1] == game[row][ccol])
						{
							game[row][ccol - 1] *= 2;
							game[row][ccol] = 0;
						}
					}
				}
			}
		}
		break;
	case RIGHT:

		for (int col = COL - 2; col >= 0; --col)
		{
			for (int ccol = col; ccol <= ROW; ++ccol)
			{
				for (int row = 0; row < ROW; ++row)
				{
					if (game[row][ccol + 1] == 0)
					{
						game[row][ccol + 1] = game[row][ccol];
						game[row][ccol] = 0;
					}
					else
					{
						if (game[row][ccol + 1] == game[row][ccol])
						{
							game[row][ccol + 1] *= 2;
							game[row][ccol] = 0;
						}
					}
				}
			}
		}
		break;

	}
}


int Input()
{
	int upArrow = 0;
	int downArrow = 0;
	int leftArrow = 0;
	int rightArrow = 0;
	int direction = 0;

	while (true)
	{
		upArrow = GetAsyncKeyState(VK_UP);
		downArrow = GetAsyncKeyState(VK_DOWN);
		leftArrow = GetAsyncKeyState(VK_LEFT);
		rightArrow = GetAsyncKeyState(VK_RIGHT);

		if (upArrow)
		{
			direction = UP;
			break;
		}
		else if (downArrow)
		{
			direction = DOWN;
			break;
		}
		else if (leftArrow)
		{
			direction = LEFT;
			break;
		}
		else if (rightArrow)
		{
			direction = RIGHT;
			break;
		}
		Sleep(100);
	}
	return direction;
	
}

int Judge()
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			if (game[i][j] == 2048)
			{
				
				break;
			}
		}
	}

	for (int j = 0; j < COL; ++j)
	{
		for(int i = 0; i < ROW - 1; ++i)
		{
			if (!game[i][j] || (game[i][j] == game[i][j+1]))
			{
				
				break;
			}
		}
	}
	return GAME_OVER;
	
}

int main()
{
	srand((unsigned int)time(0));
	CreateNumber();
	CreateNumber();
	Print();
	int Direction = 0;
	int gameState = -1;
	while (true)
	{
		Direction = Input();

		gameState = Judge();
		if (Direction && gameState == GAME_CONTINUE)
		{
			Process(Direction);
			CreateNumber();
			Print();
			Sleep(100);

		}
		else if (gameState == GAME_OVER)
		{
			Print();
			cout << "YOU lose!" << endl;
			break;
		}
	}
}

