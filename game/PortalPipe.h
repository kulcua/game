#pragma once
#include "GameObject.h"

enum class PortalName {
	in,
	out
};

class PortalPipe : public CGameObject
{
	PortalName name;
	int type;
public:
	PortalPipe(string name, int type, float width, float height);

	PortalName GetName() { return name; }
	int GetType() { return type; }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

class PortalPipeOutManager {
	static PortalPipeOutManager* __instance;
public:
	// type - port
	unordered_map<int, PortalPipe*> portOut;
	static PortalPipeOutManager* GetInstance();
	PortalPipe* GetPortalPipeOut(int type) { return portOut[type]; }
	void ClearPortalPipe() { portOut.clear(); }
};

