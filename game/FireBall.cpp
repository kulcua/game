#include "FireBall.h"
#include "Utils.h"
#include "Animations.h"
#include "Ground.h"

CFireBall::CFireBall()
{
	//SetAnimation(FIREBALL_ANI_ID);
	SetAnimationFireBall();
	die = true;
}

void CFireBall::Init(CMario* mario, CPlant* plant) {
  	this->state_.live.mario = mario;
	this->state_.live.plant = plant;
	die = false;
	SetPosition(plant->x, plant->y);
	isForPlant = true;
}

void CFireBall::Init(CMario* mario)
{
	this->state_.live.mario = mario;
	die = false;
	SetPosition(mario->x, mario->y);
	isForPlant = false;
}

void CFireBall::SetAnimationFireBall()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIREBALL_ANI_ID);
	SetAnimationSet(ani_set);
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!die)
	{
		CGameObject::Update(dt, coObjects);

		if (isForPlant)
		{
			x += dx;
			y += dy;

			float x_mario, y_mario, x_plant, y_plant;

			state_.live.mario->GetPosition(x_mario, y_mario);
			state_.live.plant->GetPosition(x_plant, y_plant);

			nx = state_.live.plant->nx;

			if (state_.live.plant->isUp)
				vy = -FIREBALL_SPEED;
			else
				vy = FIREBALL_SPEED;

			if (abs(x_mario - x_plant) < FIREBALL_CHECK_POS_SHOOT_X)
				vx = FIREBALL_SPEED * nx;
			else
				vx = FIREBALL_SPEED * nx * 2;

			if (abs(y_mario - y) > FIREBALL_CHECK_Y || abs(x_plant - x_mario) > FIREBALL_CHECK_X)
			{
				//die = true;
			}
		}
		else
		{
			vy += FIREBALL_GRAVITY * dt;

			if (this->state_.live.mario->nx > 0)
			{
				vx = FIREBALL_VELOCITY_X;
			}
			else
			{
				vx = -FIREBALL_VELOCITY_X;
			}

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

				if (rdx != 0 && rdx != dx)
					x += nx * abs(rdx);

				x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];

					if (dynamic_cast<CGround*>(e->obj))
					{
						CGround* ground = dynamic_cast<CGround*>(e->obj); 
						if (e->ny < 0)
						{
							vy = -FIREBALL_DEFLECT_Y;
						}
					}
				}
			}
		}
	}
}

void CFireBall::Render()
{
	if (!die)
	{
		animation_set->at(0)->Render(x, y, NULL);
		//RenderBoundingBox();
	}
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + FIREBALL_WIDTH;
	b = y + FIREBALL_HEIGHT;
}