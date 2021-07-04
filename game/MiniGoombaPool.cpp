#include "MiniGoombaPool.h"

MiniGoombaPool* MiniGoombaPool::__instance = NULL;

MiniGoombaPool* MiniGoombaPool::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new MiniGoombaPool();
    }
    return __instance;
}

void MiniGoombaPool::InitPool(vector<LPGAMEOBJECT>& objects)
{
    miniGoomba[0] = new MiniGoomba();
    firstAvailable_ = miniGoomba[0];

    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        miniGoomba[i + 1] = new MiniGoomba();

        miniGoomba[i]->SetNext(miniGoomba[i + 1]);
        miniGoomba[i]->SetGrid(grid);
        objects.push_back(miniGoomba[i]);
    }
    miniGoomba[POOL_SIZE - 1]->SetNext(NULL);
    miniGoomba[POOL_SIZE - 1]->SetGrid(grid);
    objects.push_back(miniGoomba[POOL_SIZE - 1]);
}

MiniGoomba* MiniGoombaPool::Create() {
    if (firstAvailable_ != NULL)
    {
        MiniGoomba* newMiniGoomba = firstAvailable_;
        firstAvailable_ = newMiniGoomba->GetNext();
        return newMiniGoomba;
    }
    else return NULL;
}


void MiniGoombaPool::GetBackToPool()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        //DebugOut(L"GetBackToPool %d %d\n",i, miniGoomba[i]->inUse);
        if (miniGoomba[i]->GetBackToPool())
        {
            miniGoomba[i]->SetNext(firstAvailable_);
            firstAvailable_ = miniGoomba[i];
        }
    }
}

int MiniGoombaPool::CheckNumberInPool()
{
    int n = 0;
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (miniGoomba[i]->inUse == false)
        {
            n++;
        }
    }
    return n;
}