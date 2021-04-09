#pragma once
#include "Utils.h"
#include "Text.h"
#define HUD_HEIGHT 125
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define HUD_ALIGN_LEFT 110
#define HUD_ALIGN_CENTER 160
#define HUD_ALIGN_MONEY	398
#define HUD_ALIGN_TIME 376
#define HUD_ALIGN_TOP 22
#define HUD_ALIGN_BOTTOM 46

class HUD
{
	static HUD* __instance;
	float x, y;
	int spriteId;
	float xWorld, xM;
	float xPower, xPoint;
	float xMoney, xTime;

	Text* world = new Text(1);
	Text* life = new Text(1);
	Text* point = new Text(7);
	Text* power = new Text(7);
	Text* money = new Text(2);
	Text* time = new Text(3);
public:
	static HUD* GetInstance();
	HUD();
	RECT* GetRectHUD();
	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void SetSpriteId(int spriteId) { this->spriteId = spriteId; }
	void Render();
};

