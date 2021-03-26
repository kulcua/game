#include "FireBallPool.h"

FireBallPool::FireBallPool(vector<LPGAMEOBJECT> &objects)
{
    firstAvailable_ = &fireBall_[0];

    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        fireBall_[i].SetNext(&fireBall_[i + 1]);
        objects.push_back(&fireBall_[i]);
    }
    fireBall_[POOL_SIZE - 1].SetNext(NULL);
    objects.push_back(&fireBall_[POOL_SIZE - 1]);
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
    for (int i = 0; i < POOL_SIZE; i++)
    {  
        if (fireBall_[i].GetBackToPool()) // return fireball
        {         
            fireBall_[i].SetNext(firstAvailable_);
            firstAvailable_ = &fireBall_[i];
        }
    }
}