#include "MarioTail.h"
#include "Animations.h"
#include "Utils.h"
#include "MarioTailHitState.h"
#include "BrickBlock.h"
#include "EffectPool.h"
#include "Brick.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Plant.h"

#define MARIO_TAIL_WDITH 100
#define MARIO_TAIL_HEIGHT 40
#define MARIO_TAIL_X 10
#define MARIO_TAIL_Y 40

MarioTail* MarioTail::__instance = NULL;

MarioTail* MarioTail::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new MarioTail();
	}
	return __instance;
}

void MarioTail::Render()
{
	//RenderBoundingBox();
}

void MarioTail::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	if (MarioTailHitState::GetInstance()->tailHitting)
	{
		for (int i = 0; i < coObjects->size(); i++)
		{
			if (AABB(coObjects->at(i)))
			{
				if (dynamic_cast<BrickBlock*>(coObjects->at(i)))
				{
					BrickBlock* block = dynamic_cast<BrickBlock*>(coObjects->at(i));
					if (block->isCoin == false)
					{
						EffectPool::GetInstance()->CreateDebris(block->x, block->y);
						block->die = true;
					}
				}
				else if (dynamic_cast<CBrick*>(coObjects->at(i)))
				{
					if (coObjects->at(i)->GetState() != BRICK_STATE_DISABLE)
						coObjects->at(i)->SetState(BRICK_STATE_DISABLE);
				}
				else if (dynamic_cast<CGoomba*>(coObjects->at(i)))
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(coObjects->at(i));
					Effect* effect = EffectPool::GetInstance()->Create();
					if (effect != NULL)
						effect->Init(EffectName::marioTailAttack, goomba->x, goomba->y);
					goomba->vy = -GOOMBA_DEFLECT_SPEED;
					goomba->ny = -goomba->ny;
					goomba->SetState(GOOMBA_STATE_DIE);
				}
				else if (dynamic_cast<CKoopa*>(coObjects->at(i)))
				{
					CKoopa* koopa = dynamic_cast<CKoopa*>(coObjects->at(i));
					Effect* effect = EffectPool::GetInstance()->Create();
					if (effect != NULL)
						effect->Init(EffectName::marioTailAttack, koopa->x, koopa->y);

					koopa->vy = -KOOPA_DEFECT_SPEED;
					koopa->ny = -koopa->ny;
					koopa->SetState(KOOPA_STATE_BALL);
				}
				else if (dynamic_cast<CPlant*>(coObjects->at(i)))
				{
					coObjects->at(i)->SetState(PLANT_STATE_DIE);
				}
			}
		}
		MarioTailHitState::GetInstance()->tailHitting = false;
	}
}

void MarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetPosition(CMario::GetInstance()->x - MARIO_TAIL_X, CMario::GetInstance()->y + MARIO_TAIL_Y);

	HandleCollision(coObjects);
}

void MarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_TAIL_WDITH;
	b = y + MARIO_TAIL_HEIGHT;
}