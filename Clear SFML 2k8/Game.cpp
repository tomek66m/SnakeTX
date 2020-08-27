#include "stdafx.h"
#include "Game.h"
using namespace std;

bool AreColliding(Sprite _target1, Sprite _target2)
{
	//globalboudns - uwzglednia skalowanie, localboudns - nie
	IntRect _one(_target1.getPosition().x, _target1.getPosition().y, _target1.getGlobalBounds().width, _target1.getGlobalBounds().height),
		_two(_target2.getPosition().x, _target2.getPosition().y, _target2.getGlobalBounds().width, _target2.getGlobalBounds().height);

	if (_one.intersects(_two))  return true;
	else return false;
}

void Game::Start()
{

	_gameState = gameState::Uninitialized;
	if (_gameState != gameState::Uninitialized)
		return;
	_mainWindow.create(VideoMode(_Height, _Width, 32), "SnakeTX");
	_gameState = gameState::SplashScreen;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();

}

bool Game::IsExiting()
{
	if (_gameState == gameState::Exiting)
		return true;
	else return false;
}

void Game::GameLoop()
{
	switch (_gameState)
	{
		case gameState::SplashScreen:
		{
			Texture splashTexture;
			if (!splashTexture.loadFromFile("logoSnake.png"))
			{
				return;
			}
			Sprite splashSprite(splashTexture);
			_mainWindow.draw(splashSprite);
			_mainWindow.display();
			Event currentEvent;
			while (true)
			{
				while (_mainWindow.pollEvent(currentEvent))
				{
					_mainWindow.draw(splashSprite);
					_mainWindow.display();
					if (currentEvent.type == Event::KeyPressed && currentEvent.key.code==Keyboard::Space)
					{
						_gameState = gameState::MenuState;
					}
					if (currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Escape)
					{
						_gameState = gameState::Exiting;
					}
				}
				break;
			}
			break;
		}

		case gameState::MenuState:
		{
			ShowMenu();
			break;
		}

		case gameState::Playing:
		{
			//rozdzielenie 
			
			//int chosenOne = ChosingMode();
			//if(chosenOne==0) StartPlayingSingle();
			//if(chosenOne==1) //multi

			StartPlayingSingle();
			break;
		}
		case gameState::Score:
		{
			//return;
			break;
		}

		case gameState::Exiting:
		{
			return;
			break;
		}

	}
}
//tu problem
void Game::ShowMenu()
{
	Menu _mainMenu;
	Menu::MenuResult result = _mainMenu.Show(_mainWindow);
	switch (result)
	{
		case Menu::Play:
		{
			_gameState = Game::Playing;
			break;
		}
		case Menu::Score:
		{
			//_gameState = Game::Score;
			_gameState = Game::Exiting;
			break;
		}
		case Menu::Exit:
		{
			_gameState = Game::Exiting;
			break;
		}
		case Menu::Nothing:
		{
			break;
		}
	}
}

int Game::ChosingMode()
{
	Event _currentEvent;
	Text _buttons[2];
	Font _font;
	_font.loadFromFile(_THEFONT);
	_buttons[0].setFont(_font);
	_buttons[0].setCharacterSize(30);
	_buttons[0].setPosition(Vector2f(640, 300));
	_buttons[0].setString("SINGLE Player");

	_buttons[1].setFont(_font);
	_buttons[1].setCharacterSize(30);
	_buttons[1].setPosition(Vector2f(640, 500));
	_buttons[0].setString("MULTI Player");

	int chosen = 0;
	bool yes = false;
	
	while (true)
	{
		while (_mainWindow.pollEvent(_currentEvent))
		{
			if (_currentEvent.type == Event::KeyPressed && _currentEvent.key.code == Keyboard::Up)
			{
				chosen = 0;
				_buttons[0].setFillColor(Color::Green);
				_buttons[1].setFillColor(Color::White);
			}
			if (_currentEvent.type == Event::KeyPressed && _currentEvent.key.code == Keyboard::Up)
			{
				chosen = 1;
				_buttons[1].setFillColor(Color::Green);
				_buttons[0].setFillColor(Color::White);
			}
			if (_currentEvent.type == Event::KeyPressed && _currentEvent.key.code == Keyboard::Enter) yes = true;
		}

		_mainWindow.clear();
		_mainWindow.display();
		if (yes == true) break;
	}
	return chosen;
}

void Game::StartPlayingSingle()
{
	Event currentEvent;
	Snake _snake;
	//Time _time;
	Clock _clock;
	float _gettedTime;
	Apple _apple;

	//background
	Sprite _background;
	Texture _tbackground;
	_tbackground.loadFromFile("firstBackground.png");
	_background.setTexture(_tbackground);
	_background.setPosition(Vector2f(0, 0));
	_background.setScale(Vector2f(1.6, 1.2));

	//punkty
	Pointsx _points;
	const char* _pointsInChar="1"; // potrzebne do zapisu danych do rejestru

	//wskaznik na wektor do przechowywania ogonu weza
	vector <Sprite> _snakeTailVector;

	//zapis wyniku do pamiec
	MemorySaver _MemorySaver;

	//tekst wyswietlony po pobiciu rekordu
	MiniWindow _recordWindow("MessageBox.png", Vector2f(300, 200), Vector2f(1, 1));

	Text _scoreText;
	Font _font;
	_font.loadFromFile("Minecraft.ttf");
	_scoreText.setString("Wynik: ");
	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(30);
	_scoreText.setFillColor(Color::Black);
	_scoreText.setPosition(Vector2f(350, 220));

	//timer odpalany przed powrotem do menu
	Clock _endClock;
	float _endTime;

	//zmienna do odliczania do wyjscia do menu

	bool LoseTimer = false;
	bool LoseCounter = false;

	float currentVelocity = 0.100;



	
	while (true && LoseCounter==false) //tu czas
	{
		//check sth
		//
		if (_gettedTime = _clock.getElapsedTime().asSeconds() >= currentVelocity)
		{
			while (_mainWindow.pollEvent(currentEvent))
			{
				if (currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Up)
				{
					_snake.ChangeMoveState(0);
					break;
				}
				if (currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Down)
				{
					_snake.ChangeMoveState(1);
					break;
				}
				if (currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Left)
				{
					_snake.ChangeMoveState(2);
					break;
				}
				if (currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Right)
				{
					_snake.ChangeMoveState(3);
					break;
				}
				if (currentEvent.type == Event::KeyPressed && currentEvent.key.code == Keyboard::Escape)
				{
					_gameState = gameState::Exiting;
					break;
				}
			}


			_mainWindow.clear(); //zawsze clear ekranu
			if (LoseTimer==false)
			{
				//update ruchu snakea
				_snake.Update();
				//apple collision
				if (AreColliding(_snake.getHeadSprite(), _apple.getSprite()))
				{
					_points.addPoints();
					_apple.FindPlace();
					_snake.AddTail();
					//zwiekszenei szybkosci
					if(currentVelocity > 0.05) currentVelocity -= 0.005;
					cout << currentVelocity << endl;
				}
				_points.updatePoints();
				//tail collision
				_snakeTailVector = _snake.getTailVector();

				for (auto x : _snakeTailVector)
				{
					if (AreColliding(_snake.getHeadSprite(), x) == true)
					{
						const CHAR* xxx = _MemorySaver.ReadData("HighestScore");
						std::stringstream buffer;
						int theHighest;
						buffer << xxx;
						buffer >> theHighest;
						if (_points.getPointsInt() > theHighest)
						{
							_MemorySaver.SaveData(_points.getPoints().c_str(), "HighestScore");
							_scoreText.setString("WYNIK: " + _points.getPoints() + " \nPOBITO !!");
						}
						_scoreText.setString("WYNIK: \n" + _points.getPoints());
						_gameState = gameState::MenuState;

						_endClock.restart();
						LoseTimer = true;
						_endClock.restart();
					}
				}
				_mainWindow.draw(_background);
				_mainWindow.draw(_snake);
				_mainWindow.draw(_apple);
				_mainWindow.draw(_points);
				_mainWindow.display();
				_clock.restart();
				_endClock.restart(); //ciagly restart zegarka
			}
			if(LoseTimer==true)
			{
				_mainWindow.draw(_background);
				_mainWindow.draw(_snake);
				_mainWindow.draw(_apple);
				_mainWindow.draw(_points);
				_mainWindow.draw(_recordWindow);
				_mainWindow.draw(_scoreText);
				_mainWindow.display();
				if (_endClock.getElapsedTime().asSeconds() >= 1.5) LoseCounter = true;
			}

			if (_gameState == gameState::Exiting) break;
		}
	}
}