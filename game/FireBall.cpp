#include "FireBall.h"
#include "Utils.h"
#include "Animations.h"

CFireBall::CFireBall()
{
	SetAnimationFireBall();	
	die = true;
}

void CFireBall::Init(CMario* mario, CPlant* plant) {
	this->state_.live.mario = mario;
	this->state_.live.plant = plant;
	die = false;
	SetPosition(plant->x, plant->y);
	DebugOut(L"init fireball\n");
}

void CFireBall::SetAnimationFireBall()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIREBALL_ANI_ID);
	SetAnimationSet(ani_set);
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"update CFireBall die\n");
	if (!die)
	{
		//DebugOut(L"update CFireBall\n");
		CGameObject::Update(dt, coObjects);

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

		x += dx;
		y += dy;

		if (abs(y_mario - y) > FIREBALL_CHECK_Y || abs(x_plant - x_mario) > FIREBALL_CHECK_X)
		{
			//die = true;
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