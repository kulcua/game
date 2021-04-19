#pragma once
#include "FireBall.h"

class FireBallPool
{
	static FireBallPool* __instance;
	static const int POOL_SIZE = 2;
	CFireBall fireBall_[POOL_SIZE];
	CFireBall* firstAvailable_;
public:
	static FireBallPool* GetInstance();
	void InitPool(vector<LPGAMEOBJECT>& objects);
	CFireBall* Create();
	void GetBackToPool();
};
