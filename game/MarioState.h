#pragma once
#include "Utils.h"
class MarioStandingState;
class MarioWalkingState;
class MarioJumpingState;
class MarioDuckingState;
class MarioStoppingState;
class MarioRunningState;
class MarioPreFlyState;
class MarioFlyingState;
class MarioDroppingState;
class MarioDropFlyState;
class MarioKickState;
class MarioLevelUpState;
class MarioTailHitState;
class MarioShootFireBallState;
class MarioFrontState;

class MarioState
{
	friend class CMario;
public:
	static MarioStandingState standing;
	static MarioWalkingState walking;
	static MarioJumpingState jumping;
	static MarioDuckingState ducking;
	static MarioStoppingState stopping;
	static MarioRunningState running;
	static MarioPreFlyState preFly;
	static MarioFlyingState flying;
	static MarioDroppingState dropping;
	static MarioDropFlyState dropFly;
	static MarioKickState kick;
	static MarioLevelUpState levelUp;
	static MarioTailHitState tailHit;
	static MarioShootFireBallState shootFireball;
	static MarioFrontState front;

	virtual void HandleInput(CMario& mario, Input input) = 0;
	virtual void Update(CMario& mario, DWORD dt);
	virtual void GetBoundingBox(CMario& mario, float& left, float& top, float& right, float& bottom);
	virtual void Enter(CMario& mario) = 0;
};

