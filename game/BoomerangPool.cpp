#include "BoomerangPool.h"

BoomerangPool* BoomerangPool::__instance = NULL;

BoomerangPool* BoomerangPool::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new BoomerangPool();
    }
    return __instance;
}

void BoomerangPool::InitPool(vector<LPGAMEOBJECT>& objects)
{
    boomerang[0] = new Boomerang();
    firstAvailable_ = boomerang[0];

    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        boomerang[i + 1] = new Boomerang();

        boomerang[i]->SetNext(boomerang[i + 1]);
        objects.push_back(boomerang[i]);
    }
    boomerang[POOL_SIZE - 1]->SetNext(NULL);
    objects.push_back(boomerang[POOL_SIZE - 1]);
}

Boomerang* BoomerangPool::Create() {
    if (firstAvailable_ != NULL)
    {
        Boomerang* newBoomerang = firstAvailable_;
        firstAvailable_ = newBoomerang->GetNext();
        return newBoomerang;
    }
    else return NULL;
}


void BoomerangPool::GetBackToPool()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        //DebugOut(L"GetBackToPool %d %d\n",i, boomerang[i]->inUse);
        if (boomerang[i]->GetBackToPool())
        {
            boomerang[i]->SetNext(firstAvailable_);
            firstAvailable_ = boomerang[i];
        }
    }
}

bool BoomerangPool::CheckBoomerangInPool(int index)
{
    return boomerang[index]->inUse;
}

void BoomerangPool::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (boomerang[i]->inUse)
        {
            boomerang[i]->Update(dt, coObjects);
        }
    }
}

void BoomerangPool::Render()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (boomerang[i]->inUse)
        {
            boomerang[i]->Render();
        }
    }
}