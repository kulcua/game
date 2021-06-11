#pragma once
#include "Utils.h"
#include "GameObject.h"
#define TEXT_WIDTH 25
#define TEXT_NUM_WORLD	1
#define TEXT_NUM_LIFE	1
#define TEXT_NUM_POWER	7
#define TEXT_NUM_POINT	7
#define TEXT_NUM_MONEY	2
#define TEXT_NUM_TIME	3

class Text : public CGameObject
{
protected:
	int content;
	int characterRender;
	int numberOfText;
public:
	Text(int numberOfText) { this->numberOfText = numberOfText; }
	void SetContent(int content) { this->content = content; characterRender = content; }
	virtual void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

class TextPowerSign : public Text
{
	int power;
public:
	TextPowerSign(int num) : Text(numberOfText) { this->numberOfText = num; }
	void SetPower(int power) { this->power = power; }
	virtual void Render();
};

