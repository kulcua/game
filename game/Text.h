#pragma once
#include "Utils.h"
#define TEXT_WIDTH 25
#define TEXT_NUM_WORLD	1
#define TEXT_NUM_LIFE	1
#define TEXT_NUM_POWER	7
#define TEXT_NUM_POINT	7
#define TEXT_NUM_MONEY	2
#define TEXT_NUM_TIME	3

class Text
{
protected:
	float x, y;
	int content;
	int characterRender;
	int numberOfText;
public:
	Text(int numberOfText) { this->numberOfText = numberOfText; }
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	void SetContent(int content) { this->content = content; characterRender = content; }
	virtual void Render();
};

class TextPowerSign : public Text
{
	int power;
public:
	TextPowerSign(int num) : Text(numberOfText) { this->numberOfText = num; }
	void SetPower(int power) { this->power = power; }
	virtual void Render();
};

