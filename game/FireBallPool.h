#pragma once
#include "FireBall.h"
#include "Plant.h"
#include "Mario.h"
#include "GameObject.h"

class FireBallPool
{
	static const int POOL_SIZE = 2;
	CFireBall fireBall_[POOL_SIZE];
	CFireBall* firstAvailable_;
public:
	FireBallPool(vector<LPGAMEOBJECT> &objects);
	CFireBall* Create();
	void GetBackToPool();
};
