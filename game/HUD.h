#pragma once
#include "Utils.h"
#include "Text.h"

#define HUD_HEIGHT 155
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 750

#define HUD_ALIGN_LEFT 110
#define HUD_ALIGN_CENTER 160
#define HUD_ALIGN_MONEY	398
#define HUD_ALIGN_TIME 376
#define HUD_ALIGN_TOP 21
#define HUD_ALIGN_BOTTOM 46

class HUD
{
	static HUD* __instance;
	float x, y;
	int spriteId;
	float xWorld, xM;
	float xPower, xPoint;
	float xMoney, xTime;
public:
	Text* world;
	Text* life;
	Text* point;
	TextPowerSign* power;
	Text* money;
	Text* time;

	static HUD* GetInstance();
	HUD();
	void SetPosition(float x, float y);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void SetSpriteId(int spriteId) { this->spriteId = spriteId; }
	void Render();
	void RenderBoundingBox();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

