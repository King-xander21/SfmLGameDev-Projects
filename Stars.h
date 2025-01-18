#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Stars
{
public:
	void Init(float rad, Color color);
	void setPosition(float startx, float starty);
	void setSpeed(float speedx);
	void moveLeft();
	void DrawSprite(RenderWindow& window);
	void Update(Time dt);
	float getx_Pos();

private:
	Vector2f Position;
	CircleShape circle;
	bool movingLeft = false;
	float speed = 0;
};