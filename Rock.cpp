#include "Rock.h"

using namespace std;
using namespace sf;

void Rock::setTexture(Texture& texture)
{
	rock.setTexture(texture);
}

void Rock::setPosition(float startx, float starty)
{
	Position.x = startx;
	Position.y = starty;
}

void Rock::DrawSprite(RenderWindow& window)
{
	window.draw(rock);
}

void Rock::setSpeed(float speedx)
{
	speed = speedx;
}

void Rock::setSize(float sizex, float sizey)
{
	Vector2f targetSize(sizex, sizey);
	rock.setScale(targetSize.x / rock.getLocalBounds().width, targetSize.y / rock.getLocalBounds().height);
}

void Rock::moveLeft()
{
	movingLeft = true;
}

int genRand()
{
	int value;
	value = rand() % 800;
	return value;
}

void Rock::Update(Time dt)
{
	if (Rock::getx_Pos() > -250)
	{
		Position.x -= speed * dt.asSeconds();
		rock.setPosition(Position);
	}
	else
	{
		int randPos = genRand();
		Rock::setPosition(1180, randPos - 100);
	}
}

bool Rock::findRockPos_x()
{
	return rock.getPosition().x;
}

bool Rock::findRockPos_y()
{
	return rock.getPosition().y;
}

bool Rock::getRockStatus()
{
	return movingLeft;
}

void Rock::setRockStatus()
{
	movingLeft = true;
}

float Rock::getx_Pos()
{
	return Position.x;
}

float Rock::gety_Pos()
{
	return Position.y;
}


void Rock::rotateRock(float angle)
{
	rock.setOrigin(rock.getLocalBounds().width / 2, rock.getLocalBounds().height / 2);
	rock.rotate(angle);
}

FloatRect Rock::getGlobalBounding()
{
	return rock.getGlobalBounds();
}