// Clear SFML 2k8.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//
#include "stdafx.h"
#include "Game.h"
#include <Windows.h>
#include "SFML/Network.hpp"
using namespace sf;
using namespace std;


int main()
{
	//

	//const int dataSize = 100;
	//char data[dataSize] = "Danedad023ed-3wqd\n";
	//TcpSocket socket;
	//IpAddress ip = IpAddress::getLocalAddress();
	//unsigned int port = 36000;
	//if (socket.connect(ip, port) != Socket::Done)
	//{
	//	cout << "nie udalo sie polaczyc\n";
	//	Sleep(1000);
	//}
	////
	//while (true)
	//{
	//	Sleep(1000);
	//	if (socket.send(data, dataSize) != Socket::Done)
	//	{
	//		cout << "Nie udalo sie wyslac danych\n";
	//	}
	//	else
	//	{
	//		cout << "wysylam\n";
	//	}
	//}

	Game _game;
	_game.Start();
	return 0;
}