#include "FireBall.h"
#include "Utils.h"
#include "Animations.h"
#include "BigBox.h"
#include "Camera.h"
#include "EffectPool.h"
#include "Game.h"
#include "KoopaBound.h"
#include "BrotherBound.h"
#include "Coin.h"

CFireBall::CFireBall()
{
	SetAnimationFireBall();
	die = true;
}

void CFireBall::InitForPlant(VenusFireTrap* venus) {
  	this->state_.live.mario =
		CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	this->state_.live.venus = venus;
	die = false;
	inUse = true;
	SetPosition(venus->x, venus->y);
	this->state_.live.type = FIREBALL_FOR_VENUS;

	float x_mario, y_mario, x_plant, y_plant;

	state_.live.mario->GetPosition(x_mario, y_mario);

	state_.live.venus->GetPosition(x_plant, y_plant);

	if (state_.live.venus->createFireball)
	{
		nx = state_.live.venus->nx;

		if (state_.live.venus->isUp)
			vy = -FIREBALL_SPEED;
		else
			vy = FIREBALL_SPEED;

		if (abs(x_mario - x_plant) < FIREBALL_CHECK_POS_SHOOT_X)
			vx = FIREBALL_SPEED * nx;
		else
			vx = FIREBALL_SPEED * nx * 2;

		state_.live.venus->createFireball = false;
	}
}

void CFireBall::InitForMario()
{
	this->state_.live.mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	die = false;
	inUse = true;
	SetPosition(state_.live.mario->x, state_.live.mario->y);
	this->state_.live.type = FIREBALL_FOR_MARIO;

	if (state_.live.mario->nx > 0)
		nx = 1;
	else
		nx = -1;

	vx = nx * FIREBALL_VELOCITY_X;
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
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);

		for (size_t i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBigBox*>(e->obj))
			{
				if (e->nx)
				{
					vx = this->nx * FIREBALL_VELOCITY_X;
					x += dx;
				}
				else if (e->ny)
					vy = -FIREBALL_DEFLECT_Y;
			}
			else if (dynamic_cast<Enermy*>(e->obj))
			{
				e->obj->die = true;
				die = true;
				Effect* effect = EffectPool::GetInstance()->Create();
				if (effect != NULL)
					effect->Init(EffectName::fireballDestroy, x, y);
			}
			else if (dynamic_cast<KoopaBound*>(e->obj)
				|| dynamic_cast<BrotherBound*>(e->obj)
				|| dynamic_cast<Coin*>(e->obj))
			{
				if (e->nx)
				{
					vx = this->nx * FIREBALL_VELOCITY_X;
					x += dx;
				}
				if (e->ny)
				{
					y += dy;
				}
			}
			else
			{
				if (e->ny < 0)
				{
					vy = -FIREBALL_DEFLECT_Y;
				}
				else {
					die = true;
					Effect* effect = EffectPool::GetInstance()->Create();
					if (effect != NULL)
						effect->Init(EffectName::fireballDestroy, x, y);
				}
			}
		}
	}
}

void CFireBall::UpdateForPlant(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += dx;
	y += dy;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	coObjects->push_back(this);
	CGameObject::Update(dt, coObjects);
	if (this->state_.live.type == FIREBALL_FOR_VENUS)
		UpdateForPlant(dt, coObjects);
	else UpdateForMario(dt, coObjects);

	CCamera* cam = CGame::GetInstance()->GetCam();
	if (AABB(cam) == false)
	{
		die = true;
	}
}

void CFireBall::Render()
{
	animation_set->at(0)->Render(x, y, nx, ny);
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_WIDTH;
	b = y + FIREBALL_HEIGHT;
}