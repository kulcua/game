#include "FireBall.h"
#include "Utils.h"
#include "Animations.h"
#include "BigBox.h"
#include "Camera.h"
#include "Goomba.h"
#include "Koopas.h"

CFireBall::CFireBall()
{
	SetAnimationFireBall();
	die = true;
}

void CFireBall::InitForPlant(CPlant* plant) {
  	this->state_.live.mario = CMario::GetInstance();
	this->state_.live.plant = plant;
	die = false;
	inUse = true;
	SetPosition(plant->x, plant->y);
	isForPlant = true;
}

void CFireBall::InitForMario()
{
	this->state_.live.mario = CMario::GetInstance();
	die = false;
	inUse = true;
	SetPosition(state_.live.mario->x, state_.live.mario->y);
	isForPlant = false;

	if (state_.live.mario->nx > 0)
		vx = FIREBALL_VELOCITY_X;
	else
		vx = -FIREBALL_VELOCITY_X;
}

void CFireBall::SetAnimationFireBall()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIREBALL_ANI_ID);
	SetAnimationSet(ani_set);
}

bool CFireBall::GetBackToPool()
{
	if (!inUse) return false;
	else if (die)
	{
		inUse = false;
		return true;
	}
	return false;
}

void CFireBall::UpdateForMario(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += FIREBALL_GRAVITY * dt;

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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBigBox*>(e->obj))
			{
				if (e->nx)
					x += dx;
				else if (e->ny)
					vy = -FIREBALL_DEFLECT_Y;
			}
			else if (dynamic_cast<CGoomba*>(e->obj)
				|| dynamic_cast<CKoopas*>(e->obj))
			{
				e->obj->die = true;
				die = true;
				StartDestroy();
			}
			else
			{
				if (e->ny < 0)
				{
					vy = -FIREBALL_DEFLECT_Y;
				}
				else {
					die = true;
					StartDestroy();
				}
			}
		}
	}
}

void CFireBall::UpdateForPlant(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += dx;
	y += dy;

	float x_mario, y_mario, x_plant, y_plant;

	state_.live.mario->GetPosition(x_mario, y_mario);
	state_.live.plant->GetPosition(x_plant, y_plant);

	if (state_.live.plant->createFireball)
	{
		nx = state_.live.plant->nx;
		state_.live.plant->createFireball = false;
	}
	
	if (state_.live.plant->isUp)
		vy = -FIREBALL_SPEED;
	else
		vy = FIREBALL_SPEED;

	if (abs(x_mario - x_plant) < FIREBALL_CHECK_POS_SHOOT_X)
		vx = FIREBALL_SPEED * nx;
	else
		vx = FIREBALL_SPEED * nx * 2;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (isDestroyed && GetTickCount64() - destroyTimeStart > FIREBALL_DESTROYED_TIME)
	{
		destroyTimeStart = 0;
		isDestroyed = false;
	}

	if (die == false)
	{
		CGameObject::Update(dt, coObjects);

		if (isForPlant)
		{
			UpdateForPlant(dt, coObjects);
		}
		else
		{
			UpdateForMario(dt, coObjects);
		}

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CCamera*>(coObjects->at(i)))
			{
				if (AABB(coObjects->at(i)) == false)
				{
					die = true;
				}
			}
		}
	}
}

void CFireBall::Render()
{
	if (inUse)
	{
		animation_set->at(FIREBALL_ANI_BALL)->Render(x, y, NULL);
	}
	else if (isDestroyed)
	{
		animation_set->at(FIREBALL_ANI_DESTROYED)->Render(x, y, NULL);
	}
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_WIDTH;
	b = y + FIREBALL_HEIGHT;
}