#pragma once
#include "Utils.h"
#include "Portal.h"
#include <unordered_map>

class PortalManager
{
	static PortalManager* __instance;
public:
	// portType - spriteId
	unordered_map<string, int> portSprite;

	// portType - sceneId
	unordered_map<string, int> portScene;

	int currentPort = 0;

	vector<CPortal*> portals;

	static PortalManager* GetInstance();

	CPortal* GetPortById(int id);
};

