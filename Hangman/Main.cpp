#include <iostream>
#include <fstream>
#include <vector>

bool LoadWords(std::string path, std::vector<std::string> &list);

int main()
{
	std::vector<std::string> easy, medium, hard;
	if(!LoadWords("words/test.txt", easy))
	{
		std::cout << "LOADWORD::EASY::FAILED\n";
		return 1;
	}
	if(!LoadWords("words/test.txt", easy))
	{
		std::cout << "LOADWORD::MEDIUM::FAILED\n";
		return 1;
	}
	if(!LoadWords("words/test.txt", easy))
	{
		std::cout << "LOADWORD::HARD::FAILED\n";
		return 1;
	}
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
	else
	{
		return false;
	}
}