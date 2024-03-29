#pragma once
#include "GameObject.h"
#define PORTAL_WIDTH 48
#define PORTAL_HEIGHT 48

class CPortal :public CGameObject
{
	int scene_id; // target scene to switch to 
	string type;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }
	void SetType(string type);
};

