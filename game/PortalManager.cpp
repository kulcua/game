#include "PortalManager.h"

PortalManager* PortalManager::__instance = NULL;

PortalManager* PortalManager::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new PortalManager();
	}
	return __instance;
}

CPortal* PortalManager::GetPortById(int id)
{
	for (size_t i = 0; i < portals.size(); i++)
	{
		if (portals[i]->GetSceneId() == id)
			return portals[i];
	}
	return nullptr;
}

void PortalManager::ClearPortal()
{
	portals.clear();
}
