#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Menu
{
public:
	Menu();
	Font _font;
	enum MenuResult{Play, Score, Exit, Nothing};

	struct Button
	{
		Text _text;
		MenuResult action;
	};

	MenuResult Show(RenderWindow& window);

private:
	int chosenButton;
	Button _buttons[3];
	
};