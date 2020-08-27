#include "stdafx.h"
#include "Snake.h"
#include "Game.h"

Snake::Snake()
{
	//glwoa weza
	_textureHead.loadFromFile("snakeHead.png");
	_textureBody.loadFromFile("snakeTail.png");
	_head.setTexture(_textureHead);
	_head.setPosition(Vector2f(_WIDTH/2, _HEIGHT/2));

	//cialo weza - 3 elementy
	for (int i = 0; i < _howLongHeIs; i++)
	{
		snakeBody.push_back(Sprite(_textureBody));
	}

	//ustawienie pozycji
	for (float i = 0; i < 3; i+=1)
	{
		snakeBody[i].setPosition(Vector2f(400 - (i+1) * 20, 300));
	}

	_moveDirection = MoveDirection::Right;

}

void Snake::destroyPart()
{
	if (!snakeBody.empty())
	{
		snakeBody.pop_back();
		_howLongHeIs--;
	}
	else return;
}

bool Snake::isDefeated()
{
	if (snakeBody.empty())
	{
		return true;
	}
	//if ... uderzy w cialo

	else return true;
}

void Snake::Update()
{
	cout << _head.getPosition().x << " " << _head.getPosition().y << endl;
	//kolizja z ekranem
	if (_head.getPosition().x >= _WIDTH)
	{
		cout << "1" << endl;
		_head.setPosition(Vector2f(0, _head.getPosition().y));
	}
	else if (_head.getPosition().y >= _HEIGHT)
	{
		cout << "2" << endl;
		_head.setPosition(Vector2f(_head.getPosition().x, 0));
	}
	else if (_head.getPosition().x < 0)
	{
		cout << "3" << endl;
		_head.setPosition(Vector2f(_WIDTH, _head.getPosition().y));
	}
	else if (_head.getPosition().y < 0)
	{
		cout << "4" << endl;
		_head.setPosition(Vector2f(_head.getPosition().x, _HEIGHT));
	}
	//
	switch (_moveDirection)
	{
		case MoveDirection::Up:
		{
			MoveHead();
			_head.move(Vector2f(0,-SizeOfParts));
			break;
		}
		case MoveDirection::Down:
		{
			MoveHead();
			_head.move(Vector2f(0, SizeOfParts));
			break;
		}
		case MoveDirection::Left:
		{
			MoveHead();
			_head.move(Vector2f(-SizeOfParts, 0));
			break;
		}
		case MoveDirection::Right:
		{
			MoveHead();
			_head.move(Vector2f(SizeOfParts, 0));
			break;
		}
		case MoveDirection::Nothing:
		{
			break;
		}
	}

}

void Snake::ChangeMoveState(int x)
{
	switch (x)
	{
	case 0:
	{
		if(_moveDirection!= MoveDirection::Down) _moveDirection = MoveDirection::Up;
		break;
	}
	case 1:
	{
		if (_moveDirection != MoveDirection::Up) _moveDirection = MoveDirection::Down;
		break;
	}
	case 2:
	{
		if (_moveDirection != MoveDirection::Right) _moveDirection = MoveDirection::Left;
		break;
	}
	case 3:
	{
		if (_moveDirection != MoveDirection::Left) _moveDirection = MoveDirection::Right;
		break;
	}
	default:
	{
		break;
	}

	}
}

void Snake::ChangeVelocity(float x)
{
	this->velocity = x;
}

void Snake::MoveHead()
{
	snakeBody[snakeBody.size() - 1].setPosition(Vector2f(_head.getPosition().x, _head.getPosition().y));
	for (int i = 0; i < snakeBody.size() - 1; i++) snakeBody[i].setPosition(snakeBody[i + 1].getPosition().x, snakeBody[i + 1].getPosition().y);
}

void Snake::AddTail()
{
	snakeBody.push_back(Sprite(_textureBody));
	_howLongHeIs++;
}