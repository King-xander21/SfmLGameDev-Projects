#include "Rocket.h"

using namespace std;
using namespace sf;

Rocket::Rocket(float startx, float starty, Texture& texture)
{
	rocket.setTexture(texture);
	Position.x = startx;
	Position.y = starty;
	rocket.setPosition(Position);
	Vector2f targetSize(44.0f, 34.0f);
	rocket.setScale(targetSize.x / rocket.getLocalBounds().width, targetSize.y / rocket.getLocalBounds().height);
}

Vector2f Rocket::getPosition()
{
	return rocket.getPosition();
}

void Rocket::DrawSprite(RenderWindow& window)
{
	window.draw(rocket);
}

void Rocket::moveUp()
{
	movingUp = true;
}

void Rocket::moveDown()
{
	movingDown = true;
}

void Rocket::Update(Time dt)
{
	if (movingDown == true)
	{
		Position.y += speed * dt.asSeconds();
	}
	if (movingUp == true)
	{
		Position.y -= speed * dt.asSeconds();
	}
	rocket.setPosition(Position);
}

void Rocket::stopUp()
{
	movingUp = false;
}

void Rocket::stopDown()
{
	movingDown = false;
}

bool Rocket::getRocketStatusUp()
{
	return movingUp;
}

bool Rocket::getRocketStatusDown()
{
	return movingDown;
}

float Rocket::gety_pos()
{
	return rocket.getPosition().y;
}

float Rocket::getx_pos()
{
	return rocket.getPosition().x;
}

FloatRect Rocket::getGlobalBounding()
{
	return rocket.getGlobalBounds();
}

float Rocket::getBoundingWidth()
{
	return rocket.getLocalBounds().width;
}