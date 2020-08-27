#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;

class Snake : public Drawable
{
public:
	Snake();
	void Update();
	void ChangeMoveState(int x);
	void ChangeVelocity(float x);
	void AddTail();
	Sprite _CurrentHeadPos()
	{
		return _head;
	}
	void getPosition()
	{
		std::cout << "X: " << _head.getPosition().x << "Y:" << _head.getPosition().y << std::endl;
	}
	Sprite getHeadSprite()
	{
		return _head;
	}

	vector<Sprite> getTailVector()
	{
		return snakeBody;
	}

	void setVelocity(float _velocity)
	{
		velocity = _velocity;
	}
private:
	int _howLongHeIs = 3;
	float SizeOfParts = 20;
	Sprite _head;
	Texture _textureHead, _textureBody;
	vector <Sprite> snakeBody;
	float velocity = 1;
	void destroyPart();
	bool isDefeated();
	enum MoveDirection{ Up, Down, Left, Right, Nothing};
	MoveDirection _moveDirection;
	void MoveHead();// poruszanie reszty ciala weza
	virtual void draw(RenderTarget &target, RenderStates states) const
	{
		target.draw(_head, states);
		for (auto x : snakeBody)
		{
			target.draw(x);
		}
	}
};