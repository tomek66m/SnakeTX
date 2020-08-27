#pragma once
#define _WIDTH 1280
#define _HEIGHT 720
#define _THEFONT "Minecraft.ttf"
#include <vector>
#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Snake.h"
#include "Obstacles.h"
#include "MemorySaver.h"

using namespace sf;
using namespace std;

class Game
{
public:
	void Start();
private:
	const int _Height=1280, _Width=720;
	enum gameState{ Uninitialized, SplashScreen, MenuState, Playing, Score, Exiting };
	bool IsExiting();
	void GameLoop();
	void ShowMenu();
	int ChosingMode();
	void StartPlayingSingle();

	gameState _gameState;
	RenderWindow _mainWindow;
};