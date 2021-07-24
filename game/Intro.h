#pragma once
#define WORLD_MAP_SCENE 2
#define INTRO_PLAYER_GAME 20012
#define INTRO_CURTAIN 20002
#define INTRO_TREE_LEFT 20008
#define INTRO_TREE_RIGHT 20009
#define INTRO_CLOUD_BIG 20010
#define INTRO_CLOUD_SMALL 20011
#include "Mario.h"
#include "PlayScene.h"
#include "Camera.h"
#include "Three.h"
#include "Koopa.h"
#include "Arrow.h"

class Intro
{
	static Intro* __instance;
	int introTime;
	ULONGLONG introTimeStart;
	Curtain* curtain;
	CMario* mario;
	CMario* luigi;
	CCamera* cam;
	Three* three;
	Arrow* arrow;
	vector<CGameObject*> objects;
	bool luigi_jump_mario = false;
	bool luigi_high_jump = false;
	bool turnOnBG = false;
public:
	static Intro* GetInstance();
	void SetScenario(vector<LPGAMEOBJECT> &objects);
	void PhaseIntro();
	void Update(DWORD dt);
	void Render();
	void ArrowUp();
	void ArrowDown();
	void SwitchOverWorld();
};

