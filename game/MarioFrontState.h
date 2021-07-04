#pragma once
#include "MarioState.h"
#include "PortalPipe.h"

#define MARIO_FRONT_SPEED_DOWN 0.02f
#define MARIO_FRONT_SPEED_UP -0.02f

class MarioFrontState : public MarioState
{
	static MarioFrontState* __instance;
	PortalPipe* portIn, * portOut;
	bool getOut;
public:
	float eny;
	bool onPortalPipe;
	static MarioFrontState* GetInstance();
	void GetPortal(CMario& mario, PortalPipe *port, float eny);
	virtual void HandleInput(CMario& mario, Input input);
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario);
};

