#include "ConsoleGameEngine.h"
#include <deque>
#include <time.h>
#include <string>

const unsigned int SCREEN_WIDTH = 120, SCREEN_HEIGHT = 30;

class Dodger
{
public:
	Dodger()
	{
		pos = CGE::Vec2(0, 0);
		dodger = CGE::Character("/*\\", pos);
	}
	Dodger(CGE::Vec2 pos)
		:
		Dodger()
	{
		this->pos = pos;
		dodger.pos = pos;
	}
	void Update()
	{
		dodger.pos = pos;
	}
	void Render(CGE::Console console)
	{
		console.Draw(dodger);
	}
	CGE::Vec2 pos;
private:
	CGE::Character dodger;
};

class Meteor
{
public:
	Meteor()
	{
		pos = CGE::Vec2(0, 0);
		meteor = CGE::Character("\\O/", pos);
	}
	Meteor(CGE::Vec2 pos)
		:
		Meteor()
	{
		this->pos = pos;
		meteor.pos = pos;
	}
	void Update()
	{
		meteor.pos = pos;
	}
	void Render(CGE::Console console)
	{
		console.Draw(meteor);
	}
	CGE::Vec2 pos;
private:
	CGE::Character meteor;

};

int main()
{
	CGE::Console console(SCREEN_WIDTH, SCREEN_HEIGHT, L"Dodge");
	//INIT
	CGE::Character gameover_text("GAMEOVER!");
	gameover_text.pos = CGE::Vec2(SCREEN_WIDTH / 2 - gameover_text.character.length() / 2, SCREEN_HEIGHT / 2);
	CGE::Character score_text;
	score_text.pos = CGE::Vec2(0, 0);
	Dodger dodger(CGE::Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 5));
	std::deque<Meteor> meteors;
	bool gameover = false;
	unsigned int score = 0;

	// GAME LOOP
	bool run = true;
	while(run)
	{
		Sleep(100); // timer
		// Game Variable Updates
		bool should_spawn = rand() % 100 > 50 ? true : false;
		if(should_spawn)
		{
			meteors.push_front(Meteor(CGE::Vec2(rand() % SCREEN_WIDTH, 0)));
		}
		if(console.GetKeyState(VK_LEFT) && !(dodger.pos.x <= 0))
		{
			dodger.pos.x -= 2;
		}
		if(console.GetKeyState(VK_RIGHT) && !(dodger.pos.x >= SCREEN_WIDTH - 3))
		{
			dodger.pos.x += 2;
		}
		for(unsigned int i = 0; i < meteors.size(); i++)
		{
			meteors[i].pos.y++;
			if(meteors[i].pos.x + 3 > dodger.pos.x && meteors[i].pos.x < dodger.pos.x + 3 &&
			   meteors[i].pos.y + 1 > dodger.pos.y && meteors[i].pos.y < dodger.pos.y + 2)
			{
				Sleep(500);
				gameover = true;
				run = false;
			}
			if(meteors[i].pos.y >= SCREEN_HEIGHT)
			{
				meteors.pop_back();
			}
		}
		score++;
		score_text.character = "Score: " + std::to_string(score);
		if(gameover)
			score_text.pos = CGE::Vec2(SCREEN_WIDTH / 2 - score_text.character.length() / 2, SCREEN_HEIGHT / 2 + 1);
		dodger.Update();
		for(unsigned int i = 0; i < meteors.size(); i++)
		{
			meteors[i].Update();
		}
		// RENDER
		console.Clear();
		// Start Draw
		if(!gameover)
		{
			dodger.Render(console);
			// draw meteors
			for(unsigned int i = 0; i < meteors.size(); i++)
			{
				meteors[i].Render(console);
			}
			// draw score
			console.Draw(score_text);
		}
		else
		{
			console.Draw(gameover_text);
			console.Draw(score_text);
		}
		// End Draw
		console.Display(); // Display Screen
		if(gameover)
			Sleep(3000);
	}
}