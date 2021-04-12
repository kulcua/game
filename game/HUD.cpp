#include "HUD.h"
#include "Sprites.h"
#include "FontManager.h"
#include "Textures.h"
#include "Game.h"

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

void HUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + SCREEN_WIDTH;
	b = y + HUD_HEIGHT;
}

void HUD::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y, NULL, bbox, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void HUD::Render()
{
	RenderBoundingBox();

	CSprites::GetInstance()->Get(spriteId)->Draw(x, y, NULL);
	
	world->Render();
	life->Render();
	point->Render();
	money->Render();
	time->Render();
	power->Render();
}