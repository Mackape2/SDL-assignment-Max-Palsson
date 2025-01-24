#include "BeachBall.h"
#include <random>

#include "../Core.h"

BeachBall::BeachBall(SDL_Rect* rect, const char filePath[], int collisionRadius, float speed, float2 direction): Actor(rect, collisionRadius) ,IVelocity(speed, direction)
{
    Enabled = false;
}

void BeachBall::Update(float deltaTime)
{
    AddPositionOffset(direction * speed * deltaTime);

    Rotation += RotationSpeed * deltaTime;

    LifeTime += deltaTime;
    if (LifeTime >= MaxLifeTime)
    {
        Destroy();
    }
}

std::shared_ptr<SDL_Texture> BeachBall::GetTexture()
{
    return TextureFlyWeight::Instance->BeachballTexture;
}

void BeachBall::Destroy()
{
    Enabled = false;
    SetPosition(float2(0,0));
    LifeTime = 0;
}

void BeachBall::RenderPass(SDL_Renderer* renderer)
{
    if (renderer == nullptr) return;

    SDL_Point center = { Rect->w / 2, Rect->h / 2};
    
    SDL_RenderCopyEx(renderer, GetTexture().get(), nullptr, Rect, Rotation, &center, SDL_FLIP_NONE);
}