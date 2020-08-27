#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Snake.h"
using namespace std;
using namespace sf;

class Player
{
private:
	string _Nick;
	IpAddress _client;
	int points = 0;
	Snake _snake;

public:

};

class MultiPlayer
{
private:
	enum MultiState { SearchingPlayers };
	void Room();
	void Loop();

public:
	MultiPlayer();
};