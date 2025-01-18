#include <iostream>
#include <SFML/Graphics.hpp>
#include "Rocket.h"
#include "Rock.h"
#include "Stars.h"
#include <random>
#include <utility>
#include <chrono>

using namespace std;
using namespace sf;
int randomx()
{
	int value;
	value = rand() % 1080;
	return value;
}

float randRotation(float start, float end)
{
	std::random_device rd; // Obtain a random seed from the hardware 
	std::mt19937 gen(rd()); // Seed the generator 
	std::uniform_real_distribution<float> dis(start, end);// Define the distribution range 
	float randomNumber = dis(gen);
	return randomNumber;
}

struct Sizevalues {
	float x;
	float y;
};

Sizevalues randSize(float startx, float endx, float starty, float endy)
{
	Sizevalues randNum;

	std::random_device randx; // Obtain a random seed from the hardware 
	std::mt19937 genx(randx()); // Seed the generator 
	std::uniform_real_distribution<float> disx(startx, endx);// Define the distribution range 
	randNum.x = disx(genx);

	std::random_device rd; // Obtain a random seed from the hardware 
	std::mt19937 gen(rd()); // Seed the generator 
	std::uniform_real_distribution<float> dis(starty, endy);// Define the distribution range 
	randNum.y = dis(gen); 
	return randNum;
}

bool checkCollision(Rocket& player, Rock& rock)
{
	FloatRect rect1, rect2;
	rect1 = player.getGlobalBounding();
	rect2 = rock.getGlobalBounding();
	return rect1.intersects(rect2);
}

bool missileMovingRight = false;
bool visible = false;
bool CircleCreated = false;
float missileSpeed = 1000.0f;

void moveRight()
{
	missileMovingRight = true;
}

int main()
{
	// VideoMode Object 
	VideoMode vm(1080, 800);

	RenderWindow window(vm, "Space", Style::Default); 
	
	// Texture for the player character
	Texture playerTexture;
	playerTexture.loadFromFile("plane.png");

	// Texture for the obstacles
	Texture rockTexture;
	rockTexture.loadFromFile("rock.png");

	// Player Class Object
	Rocket Player(400.0f, 200.0f, playerTexture);
	vector <CircleShape> missiles;
	vector <Vector2f> missilePos;
	
	// Obstacle Rock Object
	Rock Asteroid[20];
	float rotations[20];
	Sizevalues sizes[20];

	FloatRect playerBounds, rockBounds[20];
	playerBounds = Player.getGlobalBounding();
	for (int i = 0; i < 20; i++)
	{
		rockBounds[i] = Asteroid[i].getGlobalBounding();
	}

	// Creating a Rectangle Shape for player hp
	RectangleShape Hp(Vector2f(200.0f, 10.0f));
	Hp.setPosition(400.0f, 50.0f);
	Hp.setFillColor(Color::Red);
	float deductionVal = 0.001f;

	// Get the current time as the start time
	auto startTime = chrono::steady_clock::now();

	Font scoreTextFont, scoreValueFont;
	if (!scoreTextFont.loadFromFile("JerseyRegular.ttf"))
	{
		cout << "unable to read font file"<< endl;
		return  -1;
	}

	if (!scoreValueFont.loadFromFile("JerseyRegular.ttf"))
	{
		cout << "unable to read font file" << endl;
		return -1;
	}

	Text scoreText, scoreValue;
	int Scr = 0;
	scoreText.setFont(scoreTextFont);
	scoreText.setString("Score: ");
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10, 10);

	scoreValue.setFont(scoreValueFont);
	// Converting integer to string 
	String strScr = to_string(Scr);
	scoreValue.setString(strScr);
	scoreValue.setCharacterSize(24);
	scoreValue.setFillColor(Color::White);
	scoreValue.setPosition(90, 10);
	
	for (int i = 0; i < 20; i++)
	{
		sizes[i] = randSize(70.0f, 200.0f, 70.0f, 150.0f);
	}

	for (int i = 0; i < 20; i++)
	{
		rotations[i] = randRotation(-0.09f, 0.09f);
	}

	float x_pos = 600, y_pos = 5;

	for (int i = 0; i < 20; i++)
	{

		Asteroid[i].setTexture(rockTexture);
		Asteroid[i].setSize(sizes[i].x, sizes[i].y);
	}
	
	// Initialization
	Asteroid[0].setPosition(x_pos, y_pos);
	Asteroid[1].setPosition(x_pos + 100, y_pos + 100);
	Asteroid[2].setPosition(x_pos + 300, y_pos);
	Asteroid[3].setPosition(x_pos + 400, y_pos);
	Asteroid[4].setPosition(x_pos + 500, y_pos);
	Asteroid[5].setPosition(x_pos + 650, y_pos + 130);
	Asteroid[6].setPosition(x_pos + 600, y_pos);
	Asteroid[7].setPosition(x_pos + 750, y_pos);
	Asteroid[8].setPosition(x_pos, y_pos);
	Asteroid[9].setPosition(x_pos + 100, y_pos + 100);
	Asteroid[10].setPosition(x_pos + 800, y_pos);
	Asteroid[11].setPosition(x_pos + 900, y_pos);
	Asteroid[12].setPosition(x_pos + 1000, y_pos);
	Asteroid[13].setPosition(x_pos + 1050, y_pos + 130);
	Asteroid[14].setPosition(x_pos + 1070, y_pos);
	Asteroid[15].setPosition(x_pos + 1750, y_pos);
	Asteroid[16].setPosition(x_pos + 1400, y_pos);
	Asteroid[17].setPosition(x_pos + 1500, y_pos);
	Asteroid[18].setPosition(x_pos + 1650, y_pos + 130);
	Asteroid[19].setPosition(x_pos + 1400, y_pos);
	

	for (int i = 0; i < 20; i++)
	{
		Asteroid[i].setSpeed(700);
	}

	// Star Object
	Stars star[50];
	Stars star2[50];
	float starty = 100.0f;

	// Star Initialization
	for (int i = 0; i < 50; i++)
	{
		star[i].Init(2, Color::White);
		star[i].setSpeed(500.0f);
	}
	for (int i = 0; i < 50; i++)
	{
		star2[i].Init(4, Color::White);
		star2[i].setSpeed(500.0f);
	}


	for (int i = 0; i < 50; i++)
	{
		star[i].setPosition(randomx() * 40, starty * 40);
	}
	for (int i = 0; i < 50; i++)
	{
		star2[i].setPosition(randomx() * 40, starty * 40);
	}

	Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Getting the current time in the loop
		auto currentTime = chrono::steady_clock::now();

		// Calculating the elapsed time in seconds
		auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime);

		// Checking if 1 second has passed
		if (elapsedTime.count() >= 1)
		{
			Scr++;
			strScr = to_string(Scr);
			scoreValue.setString(strScr);
			startTime = currentTime;
		}
		
		//Player.handleInput();

		if (Keyboard::isKeyPressed(Keyboard::W) && Player.gety_pos() > 0)
		{
			Player.moveUp();
		}
		else
		{
			Player.stopUp();
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && Player.gety_pos() < 650)
		{
			Player.moveDown();
		}
		else 
		{
			Player.stopDown();
		}


		for (int i = 0; i < 20; i++)
		{
			if (checkCollision(Player, Asteroid[i]))
			{
				Vector2f size = Hp.getSize(); 
				if (size.x > 0)
				{
					Hp.setSize(Vector2f(size.x - deductionVal, size.y));
					Hp.setPosition(400.0f, 50.0f); 
				}
			}
		}

		for (int i = 0; i < 20; i++)
		{
			Asteroid[i].moveLeft();
			Asteroid[i].rotateRock(rotations[i]);
		}

		Time dt = clock.restart();



		// Condition for missiles
		if (Keyboard::isKeyPressed(Keyboard::J) && !CircleCreated)
		{
			moveRight();
			visible = true;
			CircleShape circle(5.0f);
			circle.setFillColor(Color::Red);
			Vector2f pos(Player.getx_pos(), Player.gety_pos());
			circle.setPosition(pos);
			CircleCreated = true;
		
			missiles.push_back(circle);
			missilePos.push_back(pos);
		} 
		else if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::J)
			{
				CircleCreated = false;
			}
		}

		// Updating missile position
		for (size_t i = 0; i < missiles.size(); ++i)
		{
			if (missilePos[i].x < 1080)
			{
				missilePos[i].x += missileSpeed * dt.asSeconds();
				missiles[i].setPosition(missilePos[i]);
			}
			else
			{
				missiles.erase(missiles.begin() + i);
				missilePos.erase(missilePos.begin() + i);
				--i;
			}
		}

		for (size_t i = 0; i < missiles.size(); ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				if (missiles[i].getGlobalBounds().intersects(Asteroid[j].getGlobalBounding()))
				{
					missiles[i].setPosition(-1000.0f, -1000.0f);
					/*visible = false;*/
					Asteroid[j].setPosition(-1000.0f, -1000.0f);
				}
			}
		}


		// Update Player Character per frame
		Player.Update(dt);

		std::for_each(std::begin(star), std::end(star), [dt](Stars& s) 
		{
				s.moveLeft(); 
				s.Update(dt); 
		});
		std::for_each(std::begin(star2), std::end(star2), [dt](Stars& s) { s.moveLeft(); s.Update(dt); });

		// Update Rock Obstacle Character per frame
		for (int i = 0; i < 20; i++)
		{
			Asteroid[i].Update(dt);
		}

		window.clear();

		window.draw(scoreText);
		window.draw(scoreValue);

		std::for_each(std::begin(star), std::end(star), [&window](Stars& s) { s.DrawSprite(window); });
		std::for_each(std::begin(star2), std::end(star2), [&window](Stars& s) { s.DrawSprite(window); });

		Player.DrawSprite(window);
		for (int i = 0; i < 20; i++)
		{
			Asteroid[i].DrawSprite(window);
		}

		if (visible)
		{
			for (const auto& circle : missiles)
			{
				window.draw(circle);
			}
		}
		window.draw(Hp);
		window.display();
	}

	return 0;
}