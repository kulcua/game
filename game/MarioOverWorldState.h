#pragma once
#include "MarioState.h"
#define MARIO_WIDTH 48
#define MARIO_HEIGHT 48
#define MARIO_ANI_SMALL_OVERWORLD	0 
#define MARIO_ANI_BIG_OVERWORLD	1
#define MARIO_ANI_RACCOON_OVERWORLD	2
class MarioOverWorldState : public MarioState
{
	static MarioOverWorldState* __instance;
	int sceneId;
	bool isSwitchScene;
public:
	static MarioOverWorldState* GetInstance();
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
	void SetSceneId(int sceneId) { this->sceneId = sceneId; }
};

