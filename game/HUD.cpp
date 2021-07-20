#include "HUD.h"
#include "Sprites.h"
#include "FontManager.h"
#include "Textures.h"
#include "Game.h"
#include "Camera.h"
#define WORLD_MAP_SCENE 2

HUD::HUD(vector<LPGAMEOBJECT> &objects)
{
	world = new Text();
	life = new Text();
	point = new Text();
	power = new TextPowerSign();
	money = new Text();
	time = new Text();

	world->SetLength(TEXT_NUM_WORLD);
	life->SetLength(TEXT_NUM_LIFE);
	point->SetLength(TEXT_NUM_POINT);
	power->SetLength(TEXT_NUM_POWER);
	money->SetLength(TEXT_NUM_MONEY);
	time->SetLength(TEXT_NUM_TIME);

	objects.push_back(world);
	objects.push_back(life);
	objects.push_back(point);
	objects.push_back(power);
	objects.push_back(money);
	objects.push_back(time);
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

ULONGLONG HUD::CountDownTimer()
{
	ULONGLONG calculateTimeLeft = HUD_TIMER - (GetTickCount64() - timeStart) / 1000;
	if (CGame::GetInstance()->GetCurrentScene()->isFinished)
	{
		if (timeLeft == HUD_TIMER)
		{
			timeLeft = calculateTimeLeft;
		}
		else {
			timeLeft = timeLeft--;
			mario->SetPoint(10);
		}
	}
	else {
		return calculateTimeLeft;
	}
	return timeLeft;
}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	float cx, cy;
	CGame::GetInstance()->GetCam()->GetPosition(cx, cy);
	SetPosition(cx, cy);

	int timer = 0;
	if (CGame::GetInstance()->GetCurrentScene()->GetSceneId() != WORLD_MAP_SCENE)
		timer = CountDownTimer();

	world->SetContent(1);
	life->SetContent(mario->GetLife());
	power->SetPower(mario->GetPower());
	point->SetContent(mario->GetPoint());
	money->SetContent(mario->GetMoney());
	time->SetContent(timer);

	if(timer == 0 && CGame::GetInstance()->GetCurrentScene()->GetSceneId() != WORLD_MAP_SCENE)
	{
		CGame::GetInstance()->SwitchScene(WORLD_MAP_SCENE);
	}
}

void HUD::SetPosition(float cx, float cy)
{
	x = cx;
	y = cy + SCREEN_HEIGHT - 155;

	x = floor(x);
	y = floor(y);

	xWorld = xM = x + HUD_ALIGN_LEFT;
	xPower = xPoint = x + HUD_ALIGN_CENTER;
	xMoney = x + HUD_ALIGN_MONEY;
	xTime = x + HUD_ALIGN_TIME;
	xCard = x + HUD_ALIGN_CARD;
	float yTop = y + HUD_ALIGN_TOP;
	float yBottom = y + HUD_ALIGN_BOTTOM;

	world->SetPosition(xWorld, yTop);
	life->SetPosition(xM, yBottom);
	power->SetPosition(xPower, yTop);
	point->SetPosition(xPoint, yBottom);
	money->SetPosition(xMoney, yTop);
	time->SetPosition(xTime, yBottom);
	for (int i = 0; i < card.size(); i++)
	{
		card[i]->SetPosition(xCard + i * TEXT_CARD_BBOX_WIDTH, yTop);
	}
}

void HUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HUD_WIDTH;
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

	CGame::GetInstance()->Draw(x, y, nx, ny, bbox, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void HUD::Render()
{
	if (spriteId != 0)
	{
		RenderBoundingBox();

		CSprites::GetInstance()->Get(spriteId)->Draw(x, y, -1, -1);
	}	

	world->Render();
	life->Render();
	power->Render();
	point->Render();
	money->Render();
	time->Render();
	for (int i = 0; i < card.size(); i++)
	{
		card[i]->Render();
	}
}