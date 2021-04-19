#include "EffectPool.h"

EffectPool* EffectPool::__instance = NULL;

EffectPool* EffectPool::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new EffectPool();
    }
    return __instance;
}

void EffectPool::InitPool(vector<LPGAMEOBJECT>& objects)
{
    firstAvailable_ = &effect[0];

    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        effect[i].SetNext(&effect[i + 1]);
        objects.push_back(&effect[i]);
    }
    effect[POOL_SIZE - 1].SetNext(NULL);
    objects.push_back(&effect[POOL_SIZE - 1]);
}

Effect* EffectPool::Create() {
    if (firstAvailable_ != NULL)
    {
        Effect* newEffect = firstAvailable_;
        firstAvailable_ = newEffect->GetNext();
        return newEffect;
    }
    else return NULL;
}

void EffectPool::GetBackToPool()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (effect[i].GetBackToPool())
        {
            effect[i].SetNext(firstAvailable_);
            firstAvailable_ = &effect[i];
        }
    }
}