#include "ConsoleGameEngine.h"

#include <time.h>
#include <vector>

const int SC_WIDTH = 120, SC_HEIGHT = 30;
const int GAME_WIDTH = 60, GAME_HEIGHT = 30;

class Snake
{
private:
	class SnakeSegment
	{
	public:
		SnakeSegment()
		{
			child = NULL;
			vel = CGE::Vec2(0, 0);
			pos = CGE::Vec2(0, 0);
			segment = CGE::Character("X", pos);
		}
		void Update()
		{
			pos += vel;
			segment.pos = pos;
		}
		void Render(CGE::Console console)
		{
			console.Draw(segment);
		}
		CGE::Vec2 pos;
		CGE::Vec2 vel;
	private:
		SnakeSegment* child;
		CGE::Character segment;
	};
public:
	Snake()
	{
		segments.push_back(SnakeSegment());
		head = &segments[0];
	}
	void Update()
	{
		for(unsigned int i = 0; i < segments.size(); i++)
		{
			segments[i].Update();
		}
	}
	void Render(CGE::Console console)
	{
		for(unsigned int i = 0; i < segments.size(); i++)
		{
			segments[i].Render(console);
		}
	}
	SnakeSegment* head;
private:
	std::vector<SnakeSegment> segments;
};


class Apple
{
public:
	Apple()
	{
		pos = CGE::Vec2(rand() % GAME_WIDTH, rand() % GAME_HEIGHT);
		apple = CGE::Character("O", pos);
	}
	void Repos()
	{
		pos = CGE::Vec2(rand() % GAME_WIDTH, rand() % GAME_HEIGHT);
	}
	void Update()
	{
		apple.pos = pos;
	}
	void Render(CGE::Console console)
	{
		console.Draw(apple);
	}
	CGE::Vec2 pos;
private:
	CGE::Character apple;
};

int main()
{
	srand((unsigned int) time(0));
	CGE::Console console(SC_WIDTH, SC_HEIGHT, "Snake");

	std::vector<CGE::Character> side_borders;
	for(int i = 0; i < GAME_HEIGHT; i++)
	{
		side_borders.push_back(CGE::Character("#", 0, i));
		side_borders.push_back(CGE::Character("#", GAME_WIDTH - 1, i));
	}
	CGE::Character upper_border(std::string(GAME_WIDTH, '#'), 0, 0);
	CGE::Character lower_border(std::string(GAME_WIDTH, '#'), 0, GAME_HEIGHT - 1);
	Snake snake;
	Apple apple;
	snake.head->pos = CGE::Vec2(GAME_WIDTH / 2, GAME_HEIGHT / 2);
	bool run = true;
	while(run)
	{
		Sleep(100);
		if(console.GetKeyState(VK_UP))
			snake.head->vel = CGE::Vec2(0, -1);
		if(console.GetKeyState(VK_DOWN))
			snake.head->vel = CGE::Vec2(0, 1);
		if(console.GetKeyState(VK_LEFT))
			snake.head->vel = CGE::Vec2(-1, 0);
		if(console.GetKeyState(VK_RIGHT))
			snake.head->vel = CGE::Vec2(1, 0);
		if(snake.head->pos.y < 1 || snake.head->pos.y > GAME_HEIGHT - 2 ||
		   snake.head->pos.x < 1 || snake.head->pos.x > GAME_WIDTH - 2)
			run = false;
		if(snake.head->pos.x == apple.pos.x && snake.head->pos.y == apple.pos.y)
		{
			apple.Repos();
		}
		snake.Update();
		apple.Update();
		console.Clear();
		for(unsigned int i = 0; i < side_borders.size(); i++)
		{
			console.Draw(side_borders[i]);
		}
		console.Draw(upper_border);
		console.Draw(lower_border);
		snake.Render(console);
		apple.Render(console);
		console.Display();
	}
}