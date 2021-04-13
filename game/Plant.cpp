#include "Plant.h"
#include "Ground.h"
#include "Pipe.h"
#include "PlayScene.h"

CPlant::CPlant(float y) {
	startY = y;
	vy = -PLANT_SPEED;
	mario = CMario::GetInstance();
}

void CPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	y += dy;

	if (y > startY && vy > 0)
		vy = -vy;
}

