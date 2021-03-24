#include <algorithm>
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Portal.h"
#include "BigBox.h"
#include "Ground.h"
#include "Item.h"
#include "Koopas.h"
#include "Pipe.h"
#include "MarioState.h"
#include "MarioStandingState.h"
#include "MarioDuckingState.h"
#include "MarioKickState.h"
#include "MarioLevelUpState.h"
#include "MarioFlyingState.h"
#include "FireBallPool.h"
#include "CameraBound.h"

void CMario::PowerReset()
{
	isPower = false; 
	powerStartTime = 0;
	savePower = 0;
	PowerDown();
}

void CMario::KickShell()
{
	if (isHandleShell)
	{
		isHandleShell = false;
		koopaShell->KickByMario(this);
		state_ = MarioState::kick.GetInstance();
		MarioState::kick.GetInstance()->StartKick();
	}
}

void CMario::PowerControl()
{
	if (isPower)
	{
		int temp;
		if (((GetTickCount64() - powerStartTime) / MARIO_POWERUP_PER_SECOND) < MARIO_MAX_POWER)
		{
			temp = (GetTickCount64() - powerStartTime) / MARIO_POWERUP_PER_SECOND; //1
			if (power > 0 && savePower == 0)
			{
				savePower = power;
			}
			if (temp <= MARIO_MAX_POWER - savePower) //temp_power = 2
			{
				power = savePower + temp;
			}
			if (power == 0)
				power = temp;
			//DebugOut(L"temp %d - temp-power %d - power %d\n", temp, temp_power, power);
		}
	}
	if (powerEndTime > 0 && isPower == false)
	{
		if (power == 0)
		{
			powerEndTime = 0;
		}
		else
			power = MARIO_MAX_POWER - ((GetTickCount64() - powerEndTime) / MARIO_POWERUP_PER_SECOND);
	}
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

CMario::CMario(float x, float y, FireBallPool* pool) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;

	state_ = MarioState::standing.GetInstance();

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
	this->pool_ = pool;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	CGameObject::Update(dt);

	/*DebugOut(L"vy %f\n", vy);*/

	state_->Update(*this, dt);

	vy += MARIO_GRAVITY * dt;

	if (vy > MARIO_VY_DROP)
		isGrounded = false;

	PowerControl();

	//CollisionAABB(coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != MARIO_STATE_DIE)
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
		if (rdx != 0 && rdx!=dx)
			x += nx*abs(rdx); 

		// block every object first!
		//fix 0.4f to 0.2f
		x += min_tx * dx + nx * 0.2f;
		y += min_ty * dy + ny * 0.2f;

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
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (isAttack || level == MARIO_LEVEL_RACCOON)
						goomba->SetState(GOOMBA_STATE_DIE);
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
				else if (e->ny > 0 && isHighJump)
				{
					vy = -MARIO_JUMP_SPEED_Y / 2; // jump little to avoid object on mario head
					y += dy;
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
				if (brick->GetState() != BRICK_STATE_DISABLE)
				{
					if (e->ny > 0)
					{
						brick->SetState(BRICK_STATE_DISABLE);
					}
				}
			}
			else if (dynamic_cast<CItem*>(e->obj))
			{
				CItem* item = dynamic_cast<CItem*>(e->obj);
				if (level < MARIO_LEVEL_MAX)
				{
					LevelUp();
					if (item->GetState() == ITEM_STATE_RED_MUSHROOM)
					{
						y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
					}
					else if (item->GetState() == ITEM_STATE_LEAF)
					{
						y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT;
					}
				}
				item->die = true;
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (koopas->GetState() != KOOPAS_STATE_BALL) {
					if (e->ny < 0)
					{
						koopas->SetState(KOOPAS_STATE_BALL);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					else if (e->nx != 0 && isAttack && level == MARIO_LEVEL_RACCOON) // tail hit
						koopas->SetState(KOOPAS_STATE_BALL);							
				}
				else
				{
					if (isPower && e->nx != 0) //handleShell
					{
						isHandleShell = true;
						koopas->HandleByMario(this);
						koopaShell = koopas;
					}
					else { // kick normally
						koopas->vx = this->nx * KOOPAS_BALL_SPEED;
						MarioState::kick.GetInstance()->StartKick();
						state_ = MarioState::kick.GetInstance();
					}
				}
			}
			else if (dynamic_cast<CCameraBound*>(e->obj))
			{
				CCameraBound* camBound = dynamic_cast<CCameraBound*>(e->obj);
				if (e->ny > 0)
				{
					if (camBound->GetType() == 1)
					{
						if (dynamic_cast<MarioFlyingState*>(state_))
						{
							y += dy;
						}
					}
				}
				else if (e->ny < 0)
				{
					if (camBound->GetType() == 1)
					{
						y += dy;
					}
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

//void CMario::CollisionAABB(vector<LPGAMEOBJECT>* coObjects)
//{	
//	for (int i = 0; i < coObjects->size(); i++) //need filter to box
//	{
//		if (dynamic_cast<CItem*>(coObjects->at(i)))
//		{
//			CItem* item = dynamic_cast<CItem*>(coObjects->at(i));
//			if (item->GetState() == ITEM_STATE_RED_MUSHROOM)
//			{
//				SetLevel(level + 1);
//				y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
//				item->die = true;
//			}
//			else if (item->GetState() == ITEM_STATE_LEAF)
//			{
//				SetLevel(level + 1);
//				y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT;
//				item->die = true;
//			}
//		}
//	}
//}

void CMario::Render()
{
	int animation = -1;
	if (state == MARIO_STATE_DIE)
		animation = MARIO_ANI_DIE;
	else 
		animation = GetAnimation();

	int alpha = 255;

	animation_set->at(animation)->Render(x, y, nx, alpha);

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
	//state_->GetBoundingBox(*this, left, top, right, bottom);
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIRE)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		right = x + MARIO_RACCOON_BBOX_WIDTH;
		bottom = y + MARIO_RACCOON_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	
	if (isSit)
	{
		bottom = y + MARIO_SIT_BBOX_HEIGHT;
	}
}

void CMario::Reset()
{
	state_ = MarioState::standing.GetInstance();
	isAttack = false;
	isPower = false;
	isHandleShell = false;
	SetLevel(MARIO_LEVEL_SMALL);
	SetSpeed(0, 0);
}

