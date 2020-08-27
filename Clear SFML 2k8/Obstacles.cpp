#include "stdafx.h"
#include "Obstacles.h"

//apple

Apple::Apple()
{
	_texture.loadFromFile("apple.png");
	_texture.setSmooth(true);
	_texture.setRepeated(true);
	_sprite.setTexture(_texture);
	//_sprite.setScale(Vector2f(2, 2)); // przy tym kolizje nie beda dzialac poprawnie
	_lastPosition.x = 0;
	_lastPosition.y = 0;
	FindPlace();

}

void Apple::FindPlace()
{
	int x, y;
	mt19937 gen(rd());
	uniform_int_distribution<> distX(6, 38);
	x = distX(gen);
	uniform_int_distribution<> distY(4, 28);
	y = distY(gen);

	if (_lastPosition.x != x && _lastPosition.y != y)
	{
		_sprite.setPosition(Vector2f(x*20, y*20));
		_thisApple.left = _sprite.getPosition().x;
		_thisApple.top = _sprite.getPosition().y;
		_thisApple.width = _sprite.getGlobalBounds().width;
		_thisApple.height = _sprite.getGlobalBounds().height;
		
	}
	else FindPlace();
}

//points

Pointsx::Pointsx()
{
	if (!_fontX.loadFromFile("Minecraft.ttf")) std::cout << "MAMY KLOPOT XD";
	_textX.setFont(_fontX);
	_textX.setString("Wynik: ");
	_textX.setCharacterSize(20);
	_textX.setFillColor(Color::Red);
	_textX.setStyle(Text::Bold);
	_textX.setPosition(Vector2f(0, 0));
	_textX.setStyle(Text::Regular);
}

MiniWindow::MiniWindow(string _texturePath, Vector2f _pos, Vector2f _scale)
{
	_texture.loadFromFile(_texturePath);
	_sprite.setTexture(_texture);
	_sprite.setPosition(_pos);
	//_sprite.setScale(_scale);
}