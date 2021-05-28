#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"

class Intro
{
	static Intro* __instance;
	int introTime;
	int introTimeStart;
	CMario* mario;
	CMario* luigi = new CMario();

	bool luigi_jump_mario = false;

public:
	static Intro* GetInstance();
	void SetScenario(vector<LPGAMEOBJECT> &objects);
	void Step1();
	void Update();
};

