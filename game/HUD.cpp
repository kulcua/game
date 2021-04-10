#include "HUD.h"
#include "Sprites.h"
#include "FontManager.h"

HUD* HUD::__instance = NULL;

HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}

HUD::HUD()
{
	world = new Text(TEXT_NUM_WORLD);
	life = new Text(TEXT_NUM_LIFE);
	point = new Text(TEXT_NUM_POINT);
	power = new TextPowerSign(TEXT_NUM_POWER);
	money = new Text(TEXT_NUM_MONEY);
	time = new Text(TEXT_NUM_TIME);
}

void HUD::SetPosition(float x, float y)
{
	world->SetContent(1);
	life->SetContent(4);
	//power->SetPower(2);
	point->SetContent(3979);
	money->SetContent(15);
	time->SetContent(300);

	x = floor(x);
	y = floor(y);
	this->x = x;
	this->y = y;

	xWorld = xM = x + HUD_ALIGN_LEFT;
	xPower = xPoint = x + HUD_ALIGN_CENTER;
	xMoney = x + HUD_ALIGN_MONEY;
	xTime = x + HUD_ALIGN_TIME;
	float yTop = y + HUD_ALIGN_TOP;
	float yBottom = y + HUD_ALIGN_BOTTOM;

	world->SetPosition(xWorld, yTop);
	life->SetPosition(xM, yBottom);
	power->SetPosition(xPower, yTop);
	point->SetPosition(xPoint, yBottom);
	money->SetPosition(xMoney, yTop);
	time->SetPosition(xTime, yBottom);
}

RECT* HUD::GetRectHUD()
{
	RECT rect;

	rect.left = x;
	rect.top = y;
	rect.right = x + SCREEN_WIDTH;
	rect.bottom = y + HUD_HEIGHT;

	//DebugOut(L"%d %d %d %d\n", rect.left, rect.right, rect.top, rect.bottom);

	return &rect;
}

void HUD::Render()
{
	CSprites::GetInstance()->Get(spriteId)->Draw(x, y, NULL);
	
	world->Render();
	life->Render();
	point->Render();
	money->Render();
	time->Render();
	power->Render();
}