#include "stdafx.h"
#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	if (!_font.loadFromFile("Minecraft.ttf")) std::cout << "couldnt load";

	_buttons[0].action = MenuResult::Play;
	_buttons[0]._text.setFont(_font);
	_buttons[0]._text.setPosition(Vector2f(350, 200));
	_buttons[0]._text.setCharacterSize(40);
	_buttons[0]._text.setString("PLAY");

	_buttons[1].action = MenuResult::Score;
	_buttons[1]._text.setFont(_font);
	_buttons[1]._text.setPosition(Vector2f(350, 300));
	_buttons[1]._text.setCharacterSize(40);
	_buttons[1]._text.setString("SCORE");

	_buttons[2].action = MenuResult::Exit;
	_buttons[2]._text.setFont(_font);
	_buttons[2]._text.setPosition(Vector2f(350, 400));
	_buttons[2]._text.setCharacterSize(40);
	_buttons[2]._text.setString("EXIT");

	chosenButton = 0;
}

Menu::MenuResult Menu::Show(RenderWindow& window)
{
	Event event;
	while (true)
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
			{
				if (chosenButton == 0) chosenButton = 2;
				else chosenButton--;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
			{
				if (chosenButton == 2) chosenButton = 0;
				else chosenButton++;
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
			{
				return _buttons[chosenButton].action;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (i == chosenButton) _buttons[i]._text.setFillColor(Color::Green);
			else _buttons[i]._text.setFillColor(Color::White);
		}
		window.clear();
		window.draw(_buttons[0]._text);
		window.draw(_buttons[1]._text);
		window.draw(_buttons[2]._text);
		window.display();
	}
}