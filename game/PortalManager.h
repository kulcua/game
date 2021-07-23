#pragma once
#include "Utils.h"
#include "Portal.h"
#include <unordered_map>

class PortalManager
{
	static PortalManager* __instance;
public:
	static PortalManager* GetInstance();
	// portType - spriteId
	unordered_map<string, int> portSprite;

	// portType - sceneId
	unordered_map<string, int> portScene;

	int currentPort = 0;
	vector<CPortal*> portals;
	CPortal* GetPortById(int id);
	void ClearPortal();
};

