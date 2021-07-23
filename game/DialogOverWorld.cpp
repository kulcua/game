#include "DialogOverWorld.h"
#include "Game.h"

DialogOverWorld::DialogOverWorld()
{
	timeStart = 0;
	die = true;
	this->width = DIALOG_WIDTH;
	this->height = DIALOG_HEIGHT;
	world = new Text();
	life = new Text();
	world->SetLength(TEXT_NUM_WORLD);
	life->SetLength(TEXT_NUM_LIFE);
}

DialogOverWorld* DialogOverWorld::__instance = NULL;

DialogOverWorld* DialogOverWorld::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new DialogOverWorld();
	}
	return __instance;
}

void DialogOverWorld::Update() {
	if (die == false)
	{
		if (GetTickCount64() - timeStart > DIALOG_TIME_TO_CLOSE && timeStart > 0)
		{
			timeStart = 0;
			die = true;
		}
		world->SetContent(1);
		life->SetContent(CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLife());
	}
}

void DialogOverWorld::StartTime()
{
	SetAnimation(DIALOG_ANI_ID);
	die = false;
	timeStart = GetTickCount64();
	float cx, cy;
	CGame::GetInstance()->GetCam()->GetPosition(cx, cy);
	cx = cx + CAM_WIDTH / 2 - DIALOG_WIDTH / 2;
	cy = cy + CAM_HEIGHT / 2 - DIALOG_HEIGHT / 2;
	SetPosition(cx, cy);

	world->SetPosition(cx + DIALOG_WORLD_X, cy + DIALOG_WORLD_Y);
	life->SetPosition(cy + DIALOG_LIFE_X, cy + DIALOG_LIFE_Y);
}

void DialogOverWorld::CheckShowDialog()
{
	if (CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLife() == 0)
	{
		DialogOverWorld::GetInstance()->StartTime();
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetLife(MARIO_INIT_LIFE);
	}
}

void DialogOverWorld::Render()
{
	if (die == false) {
		int ani = DIALOG_ANI_WORLD;
		animation_set->at(ani)->Render(x, y, nx, ny);

		world->Render();
		life->Render();
	}
}

void DialogOverWorld::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}