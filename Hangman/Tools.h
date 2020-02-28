#include <Windows.h>

HANDLE GetHandle()
{
	return GetStdHandle(STD_OUTPUT_HANDLE);
}

void Goto(short x, short y)
{
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetHandle(), pos);
}