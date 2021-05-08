#include "PortalPipe.h"

PortalPipe::PortalPipe(string name, int type, float width, float height)
{
	if (name.compare("in") == 0)
		this->name = PortalName::in;
	else {
		this->name = PortalName::out;
		PortalPipeOutManager::GetInstance()->portOut[type] = this;
	}

	this->type = type;
	this->width = width;
	this->height = height;
}

void PortalPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void PortalPipe::Render()
{

}

void PortalPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

PortalPipeOutManager* PortalPipeOutManager::__instance = NULL;

PortalPipeOutManager* PortalPipeOutManager::GetInstance()
{
	if (__instance == NULL) __instance = new PortalPipeOutManager();
	return __instance;
}
