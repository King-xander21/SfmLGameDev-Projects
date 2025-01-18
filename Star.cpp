#include "Stars.h"

using namespace std; 
using namespace sf;

void Stars::Init(float rad, Color color)
{
	circle.setRadius(rad);
	circle.setFillColor(color);
}

void Stars::setPosition(float startx, float starty)
{
	Position.x = startx;
	Position.y = starty;
	circle.setPosition(Position);
}

void Stars::setSpeed(float speedx)
{
	speed = speedx;
}

void Stars::moveLeft()
{
	movingLeft = true;
}

void Stars::DrawSprite(RenderWindow& window)
{
	window.draw(circle);
}

int genRandom()
{
	int value;
	value = rand() % 800;
	return value;
}

float Stars::getx_Pos()
{
	return Position.x;
}

void Stars::Update(Time dt)
{
	if (Stars::getx_Pos() > -250)
	{
		Position.x -= speed * dt.asSeconds();
		circle.setPosition(Position);
	}
	else
	{
		int randPos = genRandom();
		Stars::setPosition(1180, randPos - 100);
	}
}