#include "stdafx.h"
#include "MemorySaver.h"


MemorySaver::MemorySaver()
{
	_Score = RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\_TomSnake", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &_key, &ISCreated);
	if (ISCreated == REG_CREATED_NEW_KEY)
	{
		cout << "Stworzono nowy klucz";
		if (RegSetValueEx(_key, "HighestScore", 0, REG_SZ, (LPBYTE)_CountToWrite, 0) != ERROR_SUCCESS)
		{
			cout << "Zapisuje wynik pierwszy raz";
		}
	}
	if (RegCloseKey(_key) != ERROR_SUCCESS)
	{
		cout << "Nie udalo sie zamknac klucza";
	}
}

const CHAR* MemorySaver::ReadData(const CHAR* valueFromKey)
{
	CHAR _readData[100];
	DWORD _dataType = REG_SZ;
	DWORD sizeOfChar;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, Path, 0, KEY_READ, &_key)!=ERROR_SUCCESS)
	{
		cout << "Nie odczytano klcuza" << endl;
	}
	if (RegQueryValueEx(_key, valueFromKey, 0, &_dataType, (LPBYTE)_readData, &sizeOfChar) != ERROR_SUCCESS)
	{
		cout << " NIE ODCZYTANO";
	}
	RegCloseKey(_key);
	cout << _readData << endl;

	CHAR* _clearData;
	int count = 0;
	for (int i = 0; i < 100; i++)
	{
		if (_readData[i] >= 47 || _readData[i] <= 57)
		{
			count++;
		}
	}
	_clearData = new char[count];
	for (int i = 0; i < count; i++)
	{
		if (_readData[i] >= 47 || _readData[i] <= 57)
		{
			_clearData[i] = _readData[i];
		}
	}
	return _clearData;
}

void MemorySaver::SaveData(const CHAR* dataToSave, const CHAR* whereToSave)
{
	if (RegOpenKeyEx(HKEY_CURRENT_USER, Path, 0, KEY_WRITE, &_key) != ERROR_SUCCESS)
	{
		cout << "Nie odczytano klcuza" << endl;
	}
	DWORD _dataType = REG_SZ;
	if (RegSetValueEx(_key, whereToSave, 0 , _dataType, (LPBYTE) dataToSave, sizeof(dataToSave))   != ERROR_SUCCESS)
	{
		cout << " NIE ZAPISANO";
	}
	
	RegCloseKey(_key);

}

const CHAR* MemorySaver::StringToConstChar(string Source)
{

	return Source.c_str();
}