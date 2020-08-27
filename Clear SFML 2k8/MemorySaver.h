#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

class MemorySaver
{
	HKEY _key;
	LONG _Score;
	DWORD ISCreated;
	CHAR Path[19] = "Software\\_SnakeTX";
	CHAR _CountToWrite[10]="0";
public:
	const CHAR* StringToConstChar(string Source);
	MemorySaver();
	const CHAR* ReadData(const CHAR* valueFromKey);
	void SaveData(const CHAR* dataToSave, const CHAR* whereToSave);
};
