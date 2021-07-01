#include "PortalPipe.h"

PortalPipe::PortalPipe(string name, int type, float camY)
{
	if (name.compare("in") == 0)
		this->name = PortalName::in;
	else {
		this->name = PortalName::out;
		PortalPipeOutManager::GetInstance()->portOut[type] = this;
	}

	this->type = type;
	this->camY = camY;
}

void PortalPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void PortalPipe::Render()
{
	//RenderBoundingBox();
}

void PortalPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PORT_WIDTH;
	b = y + PORT_HEIGHT;
}

PortalPipeOutManager* PortalPipeOutManager::__instance = NULL;

PortalPipeOutManager* PortalPipeOutManager::GetInstance()
{
	if (__instance == NULL) __instance = new PortalPipeOutManager();
	return __instance;
}
