#include "BrickBlock.h"
#include "Utils.h"
#include "Mario.h"
#include "Game.h"

BrickBlock::BrickBlock()
{
	SetAnimation(BRICKBLOCK_ANI_ID);
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void BrickBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	
	if (mario->switchItem)
	{
		isCoin = true;
	}
}

void BrickBlock::Render()
{
	int ani;
	if (isCoin)
		ani = BRICK_ANI_COIN;
	else ani = BRICK_ANI_BRICKBLOCK;
	animation_set->at(ani)->Render(x, y, nx, ny);
}

void BrickBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}