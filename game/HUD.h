#pragma once
#include "Utils.h"
#define HUD_HEIGHT 125
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

class HUD
{
	static HUD* __instance;
	float x, y;
	int spriteId;
public:
	static HUD* GetInstance();
	RECT* GetRectHUD();
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void SetSpriteId(int spriteId) { this->spriteId = spriteId; }
	void Render();
};

