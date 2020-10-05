#include <algorithm>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "BigBox.h"
#include "Ground.h"
#include "Item.h"
#include "Koopas.h"
#include "Pipe.h"

#define BORDER_X 15

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	if (x <= BORDER_X) //when mario collise with border x
		x = BORDER_X;

	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	
	//set gia toc cho mario
	if (vx == 0)
	{
		SetState(MARIO_STATE_IDLE);
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
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents); //sweptAABBEx in here so must use another function for AABB

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

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
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
							{
								SetState(MARIO_STATE_DIE);	
							}		
						}
					}
				}
			} // if Goomba

			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny)
					isGrounded = true;
			}

			else if (dynamic_cast<CPipe*>(e->obj))
			{
				if (e->ny < 0)
					isGrounded = true;
			}

			/*else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}*/

			else if (dynamic_cast<CBigBox*>(e->obj))
			{				
				if (e->ny)
					isGrounded = true;
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
						DebugOut(L"brick\n");
					}
				}
			}
			else if (dynamic_cast<CItem*>(e->obj))
			{
				CItem* item = dynamic_cast<CItem*>(e->obj);
				if (item->GetState() == ITEM_STATE_RED_MUSHROOM)
				{
					SetLevel(MARIO_LEVEL_BIG);
					y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
					item->die = true;
				}
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
					koopas->vx = KOOPAS_BALL_SPEED;
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

//void CMario::CollisionAABB(vector<LPGAMEOBJECT>* coObjects)
//{	
//	int box = 0; //check xem co box nao bi overlapping ko
//	int ground = 0;
//
//	for (int i = 0; i < coObjects->size(); i++) //need filter to box
//	{
//		if (dynamic_cast<CItem*>(coObjects->at(i)))
//		{
//			CItem* item = dynamic_cast<CItem*>(coObjects->at(i));
//			if (AABB(coObjects->at(i)))
//			{
//				item->SetState(ITEM_STATE_ENABLE);
//				y += dy;
//			}	
//		}
//	}
//}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
			ani = MARIO_ANI_SMALL_IDLE;
		else
			ani = MARIO_ANI_SMALL_WALKING;
		if(!isGrounded) ani = MARIO_ANI_SMALL_JUMP;
		if (state == MARIO_STATE_STOP) ani = MARIO_ANI_SMALL_STOP;
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
			ani = MARIO_ANI_BIG_IDLE;
		else
			ani = MARIO_ANI_BIG_WALKING;
		if (!isGrounded) ani = MARIO_ANI_BIG_JUMP;
		if (state == MARIO_STATE_STOP) ani = MARIO_ANI_BIG_STOP;
	}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, nx, alpha);
	//RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isGrounded)
		{
			vy = -MARIO_JUMP_SPEED_Y;
			isGrounded = false;
		}
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		break;
	case MARIO_STATE_IDLE:	
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
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

