#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Rocket {
public:
	Rocket(float startx, float starty, Texture& texture);
	Vector2f getPosition();
	void DrawSprite(RenderWindow& window);
	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();
	float gety_pos();
	float getx_pos();
	void Update(Time dt);
	bool getRocketStatusUp();
	bool getRocketStatusDown();
	FloatRect getGlobalBounding();
	float getBoundingWidth();

private:
	float speed = 300.0f;
	bool movingUp = false;
	bool movingDown = false;
	Vector2f Position;
	Sprite rocket;
};