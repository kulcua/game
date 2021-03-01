#include "FireBallPool.h"

FireBallPool::FireBallPool(vector<LPGAMEOBJECT> &objects)
{
    // The first one is available.
    firstAvailable_ = &fireBall_[0];

    // Each particle points to the next.
    for (int i = 0; i < POOL_SIZE - 1; i++)
    {
        fireBall_[i].SetNext(&fireBall_[i + 1]);
        objects.push_back(&fireBall_[i]);
    }

    // The last one terminates the list.
    fireBall_[POOL_SIZE - 1].SetNext(NULL);
    objects.push_back(&fireBall_[POOL_SIZE - 1]);
}

void FireBallPool::Create(CMario* mario, CPlant* plant)
{
    // Make sure the pool isn't full.
    if (firstAvailable_ != NULL)
    {
        //DebugOut(L"init fireball pool\n");
        // Remove it from the available list.
        CFireBall* newParticle = firstAvailable_;
        firstAvailable_ = newParticle->GetNext();
        newParticle->Init(mario, plant);       
    } 
}

void FireBallPool::Animate()
{
    for (int i = 0; i < POOL_SIZE; i++)
    {
        //if (fireBall_[i]->Animate())  
        if (fireBall_[i].InUse() == false) // return fireball if it die
        {
            //DebugOut(L"fireBall_[i] %d\n", i);
            // Add this particle to the front of the list.
           /* fireBall_[i].SetNext(firstAvailable_);
            firstAvailable_ = &fireBall_[i];*/
        }
    }
}