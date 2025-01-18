#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Rock
{
public:
	void rotateRock(float angle);
	void setTexture(Texture& texture);
	void setPosition(float startx, float starty);
	void setSize(float sizex, float sizey);
	void setSpeed(float speedx);
	void moveLeft();
	void DrawSprite(RenderWindow& window);
	void Update(Time dt);
	bool findRockPos_x();
	bool findRockPos_y();
	bool getRockStatus();
	void setRockStatus();
	float getx_Pos();
	float gety_Pos();
	FloatRect getGlobalBounding();

private:
	Vector2f Position;
	Sprite rock;
	bool movingLeft = false;
	float speed = 0;
	float rotationSpeed = 0;
};