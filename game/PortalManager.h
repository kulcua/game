#pragma once
#include "Utils.h"
#include <unordered_map>

class PortalManager
{
	static PortalManager* __instance;
public:
	// portType - spriteId
	unordered_map<string, int> portSprite;

	// portType - sceneId
	unordered_map<string, int> portScene;

	static PortalManager* GetInstance();
};

