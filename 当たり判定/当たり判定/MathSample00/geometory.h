#pragma once

//’·•ûŒ`
struct Rect
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
};

//‰~Œ`
struct Circle
{
	int posX;
	int posY;
	int rang;
};

Rect rcA = { 0,0,100,100 };
Rect rcB = { 200,300,50,50 };

Circle cirA={300,300,50};
Circle cirB = {100,100,30};

//Vector2

unsigned int color = 0xffffff;
char keystate[256];
int speed = 4;

void Move(void);
bool IsHitAABB(const Rect& rcA, const Rect& rcB);
bool IsHitCircle(const Circle& cirA, const Circle& cirB);