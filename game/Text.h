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
#define TEXT_CARD_ANI_ID 53
#define TEXT_CARD_BBOX_WIDTH 72
#define TEXT_CARD_ANI_MUSHROOM_BLINK 0
#define TEXT_CARD_ANI_MUSHROOM 1
#define TEXT_CARD_ANI_STAR_BLINK 2
#define TEXT_CARD_ANI_STAR 3
#define TEXT_CARD_ANI_WHITEFLOWER_BLINK 4
#define TEXT_CARD_ANI_WHITEFLOWER 5

class Text : public CGameObject
{
protected:
	int content;
	int characterRender;
	int length;
public:
	void SetLength(int length) { this->length = length; }
	void SetContent(int content) { this->content = content; characterRender = content; }
	virtual void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

class TextPowerSign : public Text
{
	int power;
public:
	void SetPower(int power) { this->power = power; }
	virtual void Render();
};

class TextString : public Text
{
protected:
	string content;
public:
	void SetContent(string content);
	string GetContent() { return content; }
	virtual void Render();
	void RenderCard(string cardName);
};

class TextCard : public TextString
{
public:
	bool blink;
	TextCard();
	void Render();
};