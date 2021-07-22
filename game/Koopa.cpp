#include "Koopa.h"
#include "Brick.h"
#include "Ground.h"
#include "BigBox.h"
#include "Goomba.h"
#include "Mario.h"
#include "Game.h"
#include "KoopaBound.h"
#include "BrickBlock.h"
#include "EffectPool.h"
#include "MusicalNote.h"
#include "Item.h"
#include "Camera.h"
#include "BoomerangBrother.h"
#include "BrotherBound.h"
#include "Coin.h"
#include "CameraBound.h"

CKoopa::CKoopa()
{
	SetState(KOOPA_STATE_WALKING);
	level = KOOPA_LEVEL_NO_WING;
	mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
}

void CKoopa::HandleByMario()
{
	isHandled = true;
}

void CKoopa::KickByMario()
{
	isHandled = false;	 
	isKicked = true;
	nx = mario->nx;
	vx = nx * KOOPA_BALL_SPEED;
	x += dx;
}

void CKoopa::SetPositionHandled()
{
	if (mario->GetLevel() == MARIO_LEVEL_SMALL)
	{
		if (mario->nx < 0)
			SetPosition(mario->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario->y - MARIO_SMALL_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario->x + MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT, mario->y - MARIO_SMALL_HANDLED_SHELL_HEIGHT);
	}
	else if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_FIRE)
	{
		if (mario->nx < 0)
			SetPosition(mario->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario->x + MARIO_SMALL_BIG_HANDLE_SHELL_WIDTH_RIGHT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
	}
	else if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
	{
		if (mario->nx < 0)
			SetPosition(mario->x - MARIO_SMALL_BIG_RACCOON_HANDLE_SHELL_WIDTH_LEFT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
		else
			SetPosition(mario->x + MARIO_RACCOON_HANDLE_SHELL_WIDTH_RIGHT, mario->y + MARIO_BIG_RACCOON_HANDLED_SHELL_HEIGHT);
	}
}

void CKoopa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + KOOPA_BBOX_WIDTH;
	if (state == KOOPA_STATE_WALKING)
		b = y + KOOPA_BBOX_HEIGHT;
	else
		b = y + KOOPA_BBOX_HEIGHT_DIE;
}

void CKoopa::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
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
		float nx, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<Enermy*>(e->obj))
			{
				if (e->nx && state != KOOPA_STATE_BALL) {
					WalkThrough();
				}
			}

			if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->nx != 0 && state == KOOPA_STATE_BALL)
				{
					if (brick->GetState() != BRICK_STATE_DISABLE)
						brick->SetState(BRICK_STATE_DISABLE);
					TurnBack(KOOPA_BALL_SPEED);
				}
			}
			else if (dynamic_cast<CBigBox*>(e->obj))
			{
				if (e->ny < 0)
				{
					isOnGround = true;
				}
				if (e->nx != 0) WalkThrough();
			}
			else if (dynamic_cast<CCamera*>(e->obj))
			{
				if (e->nx != 0) WalkThrough();
			}
			else if (dynamic_cast<Coin*>(e->obj))
			{
				if (e->nx != 0) x += dx;
				if (e->ny != 0)	y += dx;
			}
			else if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (state == KOOPA_STATE_BALL && goomba->GetState() != GOOMBA_STATE_DIE)
				{
					goomba->SetState(GOOMBA_STATE_DIE);
					goomba->BeingKicked();
				}
			}
			else if (dynamic_cast<CKoopa*>(e->obj))
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
				if (koopa->GetState() != KOOPA_STATE_DIE && state == KOOPA_STATE_BALL)
				{
					koopa->SetState(KOOPA_STATE_DIE);
					this->SetState(KOOPA_STATE_DIE);
				}
			}
			else if (dynamic_cast<BoomerangBrother*>(e->obj))
			{
				BoomerangBrother* bmrBrother = dynamic_cast<BoomerangBrother*>(e->obj);
				if (bmrBrother->GetState() != BOOMERANG_BROTHER_STATE_DIE && state == KOOPA_STATE_BALL)
				{
					bmrBrother->SetState(BOOMERANG_BROTHER_STATE_DIE);
					bmrBrother->BeingKicked();
					WalkThrough();
				}
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
					isOnGround = true;
				if (e->nx != 0) {
					if (state == KOOPA_STATE_BALL)
						TurnBack(KOOPA_BALL_SPEED);
					else TurnBack(KOOPA_WALKING_SPEED);
				}
			}
			else if (dynamic_cast<BrickBlock*>(e->obj))
			{
				BrickBlock* block = dynamic_cast<BrickBlock*>(e->obj);
				if (block->isCoin == false)
				{
					if (e->nx != 0)
					{
						if (state == KOOPA_STATE_BALL && block->die == false)
						{
							EffectPool::GetInstance()->CreateDebris(block->x, block->y);
							block->die = true;
							TurnBack(KOOPA_BALL_SPEED);
						}
						else TurnBack(KOOPA_WALKING_SPEED);
					}
				}
				else {
					if (e->nx) x += dx;
					if (e->ny) y += dy;
				}
			}
			else if (dynamic_cast<MusicalNote*>(e->obj))
			{
				MusicalNote* note = dynamic_cast<MusicalNote*>(e->obj);
				if (e->nx != 0 && state == KOOPA_STATE_BALL)
				{
					if (note->GetType() == MUSICAL_NOTE_TYPE_WHITE)
					{
						note->Deflect(1);
						TurnBack(KOOPA_BALL_SPEED);
					}
					else WalkThrough();
				}
			}
			else if (dynamic_cast<KoopaBound*>(e->obj)
				|| dynamic_cast<BrotherBound*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (state == KOOPA_STATE_BALL) {
						WalkThrough();
					}	
					else {
						TurnBack(KOOPA_WALKING_SPEED);
					}
				}
			}
			else if (dynamic_cast<CItem*>(e->obj))
			{
				WalkThrough();
			}
			else if (dynamic_cast<CCameraBound*>(e->obj))
			{
				x += dx;
				y += dy;
				die = true;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopa::TurnBack(float vx)
{
	this->nx = -this->nx;
	this->vx = this->nx * vx;
}

void CKoopa::WalkThrough()
{
	if (state == KOOPA_STATE_BALL)
		vx = this->nx * KOOPA_BALL_SPEED;
	else
		vx = this->nx * KOOPA_WALKING_SPEED;
	x += dx;
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (state == KOOPA_STATE_DIE)
	{
		if (GetTickCount64() - dieTimeStart > ENERMY_DIE_TIME)
			die = true;
		else {
			x += dx;
			y += dy;
		}
	}
	else if (state == KOOPA_STATE_BALL && vx != 0)
	{
		// ball is rolling
		ballStartTime = 0;
	}
	else if (GetTickCount64() - ballStartTime > KOOPA_BALL_RELIVE_TIME && ballStartTime > 0)
	{
		SetState(KOOPA_STATE_BALL_RELIVE);
	}
	else if (state == KOOPA_STATE_BALL_RELIVE)
	{
		if (GetTickCount64() - reliveStartTime > KOOPA_BALL_RELIVE_TIME)
		{
			SetState(KOOPA_STATE_WALKING);
			reliveStartTime = 0;
			y -= KOOPA_BBOX_HEIGHT_DIE;
			isKicked = false;
			level = KOOPA_LEVEL_NO_WING;
		}
		else
		{
			vx = -vx;
		}
	}
	
	HandleCollision(coObjects);

	if (isHandled)
		SetPositionHandled();
	else
	{
		vy += KOOPA_GRAVITY * dt;
	}

	grid_->Move(this, x, y);
}

void CKoopa::DowngradeLevel()
{
	level--;
	if (level == KOOPA_LEVEL_BALL)
		SetState(KOOPA_STATE_BALL);
	else if (level == KOOPA_LEVEL_NO_WING)
	{
		Effect* effect = EffectPool::GetInstance()->Create();
		if (effect != NULL)
			effect->InitPoint(EffectPoint::p100, x, y);
		SetState(KOOPA_STATE_WALKING);
	}	
}

void CKoopa::Render()
{
	int ani;
	if (state == KOOPA_STATE_BALL)
	{
		if (vx == 0)
			ani = KOOPA_ANI_BALL;
		else ani = KOOPA_ANI_BALL_ROLL;
	}
	else if (state == KOOPA_STATE_DIE)
		ani = KOOPA_ANI_BALL;
	else if (state == KOOPA_STATE_BALL_RELIVE)
		ani = KOOPA_ANI_BALL_RELIVE;
	else ani = KOOPA_ANI_WALKING;

	animation_set->at(ani)->Render(x, y, nx, ny);

	//RenderBoundingBox();
}

void CKoopa::SetState(int state) 
{
	CGameObject::SetState(state);
	switch (state)
	{
		case KOOPA_STATE_BALL:
		{
			Effect* effect = EffectPool::GetInstance()->Create();
			if (effect != NULL)
				effect->InitPoint(EffectPoint::p100, x, y);
			vx = 0;
			StartBallTime();
		}
		break;
		case KOOPA_STATE_WALKING:
		{
			ny = -1;
			vx = nx * KOOPA_WALKING_SPEED;
		}
		break; 
		case KOOPA_STATE_DIE:
		{
			Effect* effect = EffectPool::GetInstance()->Create();
			if (effect != NULL)
				effect->InitPoint(EffectPoint::p200, x, y);
			vx = 0;
			StartDieTime();
			BeingKicked();
		}
		break;
		case KOOPA_STATE_BALL_RELIVE:
		{
			StartReliveTime();
			ballStartTime = 0;
			vx = 0.2f;
		}
		break;
	}
}
