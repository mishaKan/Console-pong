#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <Windows.h>
#define nl frame.append("\n");
using namespace std;
class Ball
{
public:
	int posX = 35;
	int posY = 10;
	int velocity[2] = {1,-1};
	void updateball()
	{
		posX += velocity[0];
		posY += velocity[1];
		this_thread::sleep_for(chrono::milliseconds(50));
	}
};
class Board
{
public:
	int posX = 20;
	int posY = 18;
	void updateboard()
	{
		if (GetAsyncKeyState(VK_LEFT) != 0)
		{
			posX -= 2;
		}
		else if (GetAsyncKeyState(VK_RIGHT) != 0)
		{
			posX += 2;
		}
	}
};

int main()
{
	Board board;
	Ball ball;
	const int height = 20;
	const int lenght = 40;
	int grid[lenght][height];
	string frame = "";
	while (true)
	{
		thread boardthread(&Board::updateboard, &board);
		thread ballthread(&Ball::updateball,&ball);
		ballthread.join();
		boardthread.join();
		
		if (board.posX - 2 <= 0)
		{
			board.posX = lenght - 4;
		}
		else if (board.posX + 2 >= lenght - 1)
		{
			board.posX = 3;
		}
		if (ball.posY >= height)
		{
			ball.posY = 4;
		}
		for (int y = 0;y < height;y++)
		{
			for (int x = 0;x < lenght;x++)
			{
				if (x == ball.posX && y == ball.posY)
				{
					frame.append("@");
					if (ball.posY + ball.velocity[1] <= 0)
					{
						ball.velocity[1] *= -1;
					}
					if (ball.posX + ball.velocity[0] <= 0 || ball.posX + ball.velocity[0] >= lenght - 1)
					{
						ball.velocity[0] *= -1;
					}
					if (ball.posY + 1 == board.posY && (ball.posX == board.posX - 2 || ball.posX == board.posX - 1 || ball.posX == board.posX || ball.posX == board.posX + 1 || ball.posX == board.posX + 2))
					{
						ball.velocity[1] *= -1;
					}
				}
				else if ((x == board.posX - 2 || x == board.posX - 1 || x == board.posX || x == board.posX + 1 || x == board.posX + 2) && y == board.posY)
				{
					frame.append("-");
				}
				else if (x == 0 || x == lenght - 1)
				{
					frame.append("#");
				}
				else if (y == 0)
				{
					frame.append("#");
				}
				else if (y == height - 1)
				{
					frame.append("X");
				}
				else
				{
					frame.append(" ");
				}
			}
			nl;
		}
		cout << frame;
		frame = "";
	}
	return 0;
}