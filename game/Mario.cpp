#include <algorithm>
#include <cstdlib>
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Portal.h"
#include "BigBox.h"
#include "Ground.h"
#include "Item.h"
#include "Koopa.h"
#include "Pipe.h"
#include "MarioState.h"
#include "MarioStandingState.h"
#include "MarioKickState.h"
#include "MarioLevelUpState.h"
#include "MarioDroppingState.h"
#include "FireBallPool.h"
#include "CameraBound.h"
#include "HUD.h"
#include "KoopaBound.h"
#include "EffectPool.h"
#include "PowerUpItem.h"

CMario* CMario::__instance = NULL;

CMario* CMario::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new CMario();
	}
	return __instance;
}

void CMario::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		if (rdx != 0 && rdx != dx)
			x += nx * abs(rdx);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->DowngradeLevel();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (isAttack)
					{
						Effect* effect = EffectPool::GetInstance()->Create();
						if (effect != NULL)
							effect->Init(EffectName::marioTailAttack, goomba->x, goomba->y);
						goomba->vy = -GOOMBA_DEFLECT_SPEED;
						goomba->SetState(GOOMBA_STATE_DIE);
					}
				}
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny)
				{
					isGrounded = true;
				}
			}
			else if (dynamic_cast<CPipe*>(e->obj))
			{
				if (e->ny < 0)
				{
					isGrounded = true;
				}
			}
			else if (dynamic_cast<CBigBox*>(e->obj))
			{
				if (e->ny < 0)
				{
					isGrounded = true;
				}
				else {
					x += dx;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny < 0)
				{
					isGrounded = true;
				}
				else if (brick->GetState() != BRICK_STATE_DISABLE)
				{
					if (e->ny > 0)
					{
						brick->SetState(BRICK_STATE_DISABLE);
					}
				}
			}
			else if (dynamic_cast<CKoopa*>(e->obj))
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
				if (koopa->GetState() != KOOPA_STATE_BALL) {
					if (e->ny < 0)
					{
						koopa->DowngradeLevel();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else if (e->nx != 0 && isAttack)
					{
						Effect* effect = EffectPool::GetInstance()->Create();
						if (effect != NULL)
							effect->Init(EffectName::marioTailAttack, koopa->x, koopa->y);
						koopa->vy = -KOOPA_DEFECT_SPEED;
						koopa->SetState(KOOPA_STATE_BALL);
					}
				}
				else
				{
					if (isPower && e->nx != 0) //handleShell
					{
						isHandleShell = true;
						koopa->HandleByMario(this);
						koopaShell = koopa;
					}
					else { // kick normally
						koopa->vx = this->nx * KOOPA_BALL_SPEED;
						MarioState::kick.GetInstance()->StartKick();
						state_ = MarioState::kick.GetInstance();
					}
				}
			}
			else if (dynamic_cast<CCameraBound*>(e->obj))
			{
				if (e->ny > 0)
				{
					state_ = MarioState::dropping.GetInstance();
					PowerReset();
				}
				else if (e->ny < 0)
					isGrounded = true;
			}
			else if (dynamic_cast<KoopaBound*>(e->obj))
			{
				x += dx;
				y += dy;
			}
			else if (dynamic_cast<PowerUpItem*>(e->obj))
			{
				e->obj->die = true;
				LevelUp();
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	CGameObject::Update(dt);

	state_->Update(*this, dt);

	vy += MARIO_GRAVITY * dt;

	PowerControl();

	HandleCollision(coObjects);
}

void CMario::PowerReset()
{
	isPower = false;
	powerStartTime = 0;
	PowerDown();
}

void CMario::KickShell()
{
	isHandleShell = false;
	koopaShell->KickByMario(this);
	state_ = MarioState::kick.GetInstance();
	MarioState::kick.GetInstance()->StartKick();
}

int CalculatePowerTimePassed(int time)
{
	return (GetTickCount64() - time) / MARIO_POWERUP_PER_SECOND;
}

void CMario::PowerControl()
{
	int timePassed;
	if (isPower && powerStartTime > 0)
	{
		timePassed = CalculatePowerTimePassed(powerStartTime);
		if (timePassed < MARIO_MAX_POWER)
		{
			if (power == 0)
				power = timePassed;
			else if (savePower == 0)
			{
				savePower = power;
			}

			if (timePassed <= MARIO_MAX_POWER - savePower) {
				power = savePower + timePassed;
			}
		}
	}
	else if (powerEndTime > 0)
	{
		timePassed = CalculatePowerTimePassed(powerEndTime);
		if (power == 0)
			powerEndTime = 0;
		else if (savePower == 0)
		{
			savePower = power;
		}

		if (savePower - timePassed >= 0) {
			power = savePower - timePassed;
		}
	}

	HUD::GetInstance()->power->SetPower(this->GetPower());
}

void CMario::LevelUp()
{
	SetLevel(level + 1);
	state_ = MarioState::levelUp.GetInstance();
	MarioState::levelUp.GetInstance()->StartLevelUp();
}

void CMario::HandleInput(Input input)
{
	state_->HandleInput(*this, input);

	state_->Enter(*this);
}

CMario::CMario() : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	state_ = MarioState::standing.GetInstance();
	start_x = x;
	start_y = y;
	nx = 1;
	pool = FireBallPool::GetInstance();
}

void CMario::Render()
{
	int animation = -1;
	if (state == MARIO_STATE_DIE)
		animation = MARIO_ANI_DIE;
	else 
		animation = GetAnimation();

	animation_set->at(animation)->Render(x, y, nx, 255);

	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	state_->GetBoundingBox(*this, left, top, right, bottom);
}

void CMario::Reset()
{
	state_ = MarioState::standing.GetInstance();
	isAttack = false;
	isPower = false;
	isHandleShell = false;
	isUntouchable = false;
	SetLevel(MARIO_LEVEL_SMALL);
	SetSpeed(0, 0);
}

