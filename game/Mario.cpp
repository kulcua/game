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

#define BORDER_X 15

void CMario::ResetPower()
{
	power = 0; 
	isPower = false; 
	power_time_start = 0;
	power_time_end = GetTickCount64(); // bug
}

void CMario::HandleInput(Input input)
{
	state_->HandleInput(*this, input);

	state_->Enter(*this);
}

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;

	state_ = MarioState::standing.GetInstance();

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*DebugOut(L"ispower %d\n", GetPower());*/
	//DebugOut(L"vy: %f\n", vy);
	// update mario state
	state_->Update(*this, dt);

	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (x <= BORDER_X) //when mario collise with border x
		x = BORDER_X;

	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	
	// set ACCELERATION for mario
	// maybe it should be in Walking State?
	// but how about ACCELERATION when jumping or flying?
	if (vx == 0 && isGrounded && isSit == false) 
		//&&state != MARIO_STATE_DIE)
	{
		state_ = MarioState::standing.GetInstance();
	}
	else {
		if (vx > 0)
		{
			a = -MARIO_ACCELERATION;
			vx += a * dt;
			if (vx < 0)
				vx = 0;
		}
		else
		{
			a = MARIO_ACCELERATION;
			vx += a * dt;
			if (vx > 0)
				vx = 0;
		}
	}
	
	//CollisionAABB(coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (power < MARIO_MAX_POWER && power_time_start > 0)
	{
		DebugOut(L"power_time_start %d\n", GetPower());
		power = (GetTickCount64() - power_time_start) / MARIO_POWERUP_PER_SECOND;
	}
	if (power_time_end > 0 && isPower == false)
	{
		DebugOut(L"power_time_end %d\n", GetPower());
		power = MARIO_MAX_POWER - ((GetTickCount64() - power_time_end) / MARIO_POWERUP_PER_SECOND);
	}
	if (power == 0)
	{
		DebugOut(L"power == 0 %d\n", GetPower());
		power_time_end = 0;
	}

	/*if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME && untouchable)
	{
		untouchable_start = 0;
		untouchable = 0;
		SetLevel(level - 1);
	}

	if (GetTickCount() - level_up_start > MARIO_LEVEL_UP_TIME && level_up)
	{
		level_up_start = 0;
		level_up = false;
	}

	if (!isGrounded && !isJump && !isFly)
	{
		isDrop = true;
	}
	else
	{
		isDrop = false;
		isDropFly = false;
	}*/

	// No collision occured, proceed normally
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
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
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
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
								StartUntouchable();
							else
								SetState(MARIO_STATE_DIE);	
						}
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
				if (e->ny)
				{
					isGrounded = true;
				}
				else
				{
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
					SetLevel(level + 1);
					if (item->GetState() == ITEM_STATE_RED_MUSHROOM)
					{
						y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
					}
					else if (item->GetState() == ITEM_STATE_LEAF)
					{
						y -= MARIO_RACCOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT;
					}
					StartLevelUp();
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
				}
				else
				{
					koopas->vx = KOOPAS_BALL_SPEED;// *this->nx;
					StartKick();
				}
			}
		}
	}

	// clean up collision events
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
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;

	ani = GetAnimation();
	
	int alpha = 255;
	animation_set->at(ani)->Render(x, y, nx, alpha);

	RenderBoundingBox();
	//DebugOut(L"state: %d ani: %d\n", state, ani); 
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	//switch (state)
	//{
	//case MARIO_STATE_WALKING_RIGHT:
	//	if (isRun)
	//	{
	//		StartRun();
	//		vx = MARIO_RUN_SPEED;
	//	}
	//	else
	//	{
	//		vx = MARIO_WALKING_SPEED;
	//		isPreFly = false;
	//	}
	//	nx = 1;
	//	break;
	//case MARIO_STATE_WALKING_LEFT:
	//	if (isRun)
	//	{
	//		StartRun();
	//		vx = -MARIO_RUN_SPEED;
	//	}	
	//	else
	//	{
	//		isPreFly = false;
	//		vx = -MARIO_WALKING_SPEED;
	//	}
	//	nx = -1;
	//	break;
	//case MARIO_STATE_JUMP:
	//	if (isDrop) //drop
	//	{
	//		if (level == MARIO_LEVEL_RACCOON)
	//		{
	//			isDropFly = true;
	//			isDrop = false;
	//			vy = -MARIO_DROP_FLY_SPEED_Y;
	//		}
	//	}
	//	else if (isFly) //fly
	//	{
	//		if (level == MARIO_LEVEL_RACCOON)
	//			vy = -MARIO_FLY_SPEED_Y;
	//		else if (isGrounded)
	//			vy = -MARIO_JUMP_SPEED_Y;
	//		isJump = false;
	//	}
	//	else if (isGrounded) //jump
	//	{
	//		vy = -MARIO_JUMP_SPEED_Y;
	//		isJump = true;
	//	}
	//	isGrounded = false;
	//	break;
	//case MARIO_STATE_IDLE:	
	//	vx = 0;
	//	break;
	//case MARIO_STATE_DIE:
	//	vy = -MARIO_DIE_DEFLECT_SPEED;
	//	break;
	//}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	//state_->GetBoundingBox(*this, left, top, right, bottom);
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
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

//Reset Mario status to the beginning state of a scene
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

