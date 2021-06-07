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
    effect[0] = new Effect();
    firstAvailable_ = effect[0];

    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        effect[i + 1] = new Effect();

        effect[i]->SetNext(effect[i + 1]);
        objects.push_back(effect[i]);
    }
    effect[POOL_SIZE - 1]->SetNext(NULL);
    objects.push_back(effect[POOL_SIZE - 1]);
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

void EffectPool::CreateDebris(float x, float y)
{
    Effect* e1 = EffectPool::GetInstance()->Create();
    Effect* e2 = EffectPool::GetInstance()->Create();
    Effect* e3 = EffectPool::GetInstance()->Create();
    Effect* e4 = EffectPool::GetInstance()->Create();

    if (e1 != NULL && e2 != NULL && e3 != NULL && e4 != NULL)
    {
        e1->InitDebris(1, x, y);
        e2->InitDebris(2, x, y);
        e3->InitDebris(3, x, y);
        e4->InitDebris(4, x, y);
    }
}

void EffectPool::GetBackToPool()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        if (effect[i]->GetBackToPool())
        {
            effect[i]->SetNext(firstAvailable_);
            firstAvailable_ = effect[i];
        }
    }
}