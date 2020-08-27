#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>
using namespace std;
using namespace sf;

class Apple : public Drawable
{
private:
	Vector2f _lastPosition;
	IntRect _thisApple;
	Sprite _sprite;
	Texture _texture;

	//losowosc
	random_device rd;
	//
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		target.draw(_sprite, states);
	}
public:
	Apple();
	void FindPlace();
	Sprite getSprite()
	{
		return _sprite;
	}

};

class Pointsx : public Drawable
{
private:
	int _Count = 0;
	
	Text _textX;
	Font _fontX;
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		target.draw(_textX, states);
	}
public:
	Pointsx();
	void addPoints()
	{
		_Count += 5;
	}
	void updatePoints()
	{
		string _test = "Wynik: " + to_string(_Count);
		_textX.setString(_test);

	}
	string getPoints()
	{
		return to_string(_Count);
	}
	int getPointsInt()
	{
		return _Count;
	}
};

class MiniWindow : public Drawable
{
private:
	Sprite _sprite;
	Texture _texture;
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		target.draw(_sprite, states);
	}
public:
	MiniWindow(string _texturePath, Vector2f _pos, Vector2f _scale);
	
};

class MovingText : public Drawable
{
private:
	vector<Text> _textVector;
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		for (auto x : _textVector)
		{
			target.draw(x, states);
		}
	}
};

class ButtonClass : public Drawable
{
private:

};