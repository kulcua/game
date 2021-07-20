#pragma once
#include "Utils.h"
#include "Text.h"
#include "GameObject.h"
#include "Mario.h"

#define HUD_HEIGHT 500
#define SCREEN_HEIGHT 750
#define HUD_WIDTH 800
#define HUD_ALIGN_LEFT 110
#define HUD_ALIGN_CENTER 160
#define HUD_ALIGN_MONEY	398
#define HUD_ALIGN_TIME 376
#define HUD_ALIGN_TOP 21
#define HUD_ALIGN_BOTTOM 46
#define HUD_ALIGN_CARD 491
#define HUD_TIMER 500

class HUD : public CGameObject
{
	int spriteId = 0;
	float xWorld, xM;
	float xPower, xPoint;
	float xMoney, xTime;
	float xCard;
	CMario* mario;
	ULONGLONG timeStart = GetTickCount64();
	ULONGLONG timeLeft = HUD_TIMER;
public:
	Text* world;
	Text* life;
	Text* point;
	TextPowerSign* power;
	Text* money;
	Text* time;
	vector<TextString*> card;
	HUD(vector<LPGAMEOBJECT> &objects);
	ULONGLONG CountDownTimer();
	void SetPosition(float x, float y);
	void SetSpriteId(int spriteId) { this->spriteId = spriteId; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void RenderBoundingBox();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

