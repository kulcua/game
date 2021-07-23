#include "FireBallPool.h"

FireBallPool* FireBallPool::__instance = NULL;

FireBallPool* FireBallPool::GetInstance()
{
    if (__instance == NULL)
    {
        __instance = new FireBallPool();
    }
    return __instance;
}

void FireBallPool::InitPool(vector<LPGAMEOBJECT>& objects)
{
    fireBall_[0] = new CFireBall();
    firstAvailable_ = fireBall_[0];

    for (size_t i = 0; i < POOL_SIZE - 1; i++)
    {
        fireBall_[i + 1] = new CFireBall();

        fireBall_[i]->SetNext(fireBall_[i + 1]);
        objects.push_back(fireBall_[i]);
    }
    fireBall_[POOL_SIZE - 1]->SetNext(NULL);
    objects.push_back(fireBall_[POOL_SIZE - 1]);
}

CFireBall* FireBallPool::Create() {
    if (firstAvailable_ != NULL)
    {
        // get fireball
        CFireBall* newFireball = firstAvailable_;
        firstAvailable_ = newFireball->GetNext();
        return newFireball;
    }
    else return NULL;
}

void FireBallPool::GetBackToPool()
{
    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        if (fireBall_[i]->GetBackToPool())
        {        
            fireBall_[i]->SetNext(firstAvailable_);
            firstAvailable_ = fireBall_[i];
        }
    }
}

void FireBallPool::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        if (fireBall_[i]->inUse)
        {
            fireBall_[i]->Update(dt, coObjects);
        }
    }
}

void FireBallPool::Render()
{
    for (size_t i = 0; i < POOL_SIZE; i++)
    {
        if (fireBall_[i]->inUse)
        {
            fireBall_[i]->Render();
        }
    }
}