#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Camera.h"

class Intro
{
	static Intro* __instance;
	int introTime;
	int introTimeStart;
	CMario* mario;
	CMario* luigi;
	CCamera* cam;
	vector<CGameObject*> objects;
	bool luigi_jump_mario = false;

public:
	static Intro* GetInstance();
	Intro();
	void SetScenario(vector<LPGAMEOBJECT> &objects);
	void Step1();
	void Update(DWORD dt);
	void Render();
};

