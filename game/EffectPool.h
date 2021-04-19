#pragma once
#include "Effect.h"

class EffectPool
{
	static EffectPool* __instance;
	static const int POOL_SIZE = 2;
	Effect effect[POOL_SIZE];
	Effect* firstAvailable_;
public:
	static EffectPool* GetInstance();
	void InitPool(vector<LPGAMEOBJECT>& objects);
	Effect* Create();
	void GetBackToPool();
};

