#include "BeachballFactory.h"
#include "..\Actors\BeachBall.h"

BeachballFactory::BeachballFactory()
{
    filePath = "./img/beachball.png";
}

BeachBall* BeachballFactory::CreateBeachball(float2 position, int size, float2 direction, float speed) const
{
    const int collisionRadius = size/2 - static_cast<int>(0.2f * static_cast<float>(size));
    auto* rect = new SDL_Rect{static_cast<int>(position.X), static_cast<int>(position.Y), size,size };
    return new BeachBall(rect, filePath, collisionRadius, speed, direction);
}