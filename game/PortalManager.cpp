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