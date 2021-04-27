#pragma once
#include "Effect.h"

class EffectPool
{
	static EffectPool* __instance;
	static const int POOL_SIZE = 10;
	Effect effect[POOL_SIZE];
	Effect* firstAvailable_;
public:
	static EffectPool* GetInstance();
	void InitPool(vector<LPGAMEOBJECT>& objects);
	Effect* Create();
	void CreateDebris(float x, float y);
	void GetBackToPool();
};

