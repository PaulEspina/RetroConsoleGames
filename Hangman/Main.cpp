#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

#include "Tools.h"

bool GuessWord(std::string word);
bool LoadWords(std::string path, std::vector<std::string> &list);
std::string PickWord(std::vector<std::string> list);

int main()
{
	std::vector<std::string> easy, medium, hard;
	if(!LoadWords("words/easy.txt", easy))
	{
		std::cout << "LOADWORD::EASY::FAILED\n";
		return 1;
	}
	if(!LoadWords("words/medium.txt", medium))
	{
		std::cout << "LOADWORD::MEDIUM::FAILED\n";
		return 1;
	}
	if(!LoadWords("words/hard.txt", hard))
	{
		std::cout << "LOADWORD::HARD::FAILED\n";
		return 1;
	}
	std::string word = PickWord(easy);
	if(GuessWord(word))
	{
		system("cls");
		std::cout << "Win";
	}
	else
	{
		system("cls");
		std::cout << "Lose";
	}
}

bool GuessWord(std::string word)
{
	std::string guess;
	unsigned int word_length = word.length();
	for(unsigned int i = 0; i < word_length; i++)
	{
		guess.push_back('_');
		std::cout << guess[i];
	}
	int health = 5;
	while(health > 0)
	{
		bool found = false;
		char c;
		Goto(0, 1);
		std::cout << "Enter a letter: ";
		std::cin >> c;
		for(unsigned int i = 0; i < word_length; i++)
		{
			if(guess[i] == c)
			{
				std::cout << "Test";
				found = true;
				break;
			}
			if(word[i] == c)
			{
				guess[i] = c;
				found = true;
			}
		}
		if(!found)
		{
			health--;
		}
		Goto(0, 0);
		for(unsigned int i = 0; i < word_length; i++)
		{
			std::cout << guess[i];
		}
		if(guess == word)
		{
			return true;
		}
	}
	return false;
}

bool LoadWords(std::string path, std::vector<std::string> &list)
{
	std::ifstream file(path);
	if(file.is_open())
	{
		std::string data;
		while(file >> data)
		{
			list.push_back(data);
		}
		file.close();
		return true;
	}
	return false;
}

std::string PickWord(std::vector<std::string> list)
{
	srand(unsigned int(time(0)));
	int i = rand() % list.size();
	return list[i];
}