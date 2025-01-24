#include "Boat.h"
#include "../Core.h"

Boat::Boat
(
    SDL_Rect* rect, const char filePath[], int collisionRadius,float speed, float2 direction) : Actor(rect, collisionRadius), IVelocity(speed, direction)
{
    
}

void Boat::Move(float2* input)
{
    const float2 position = GetPosition();
    const float2 normalizedInput = input->Normalize();
    SetPosition(position + normalizedInput * DeltaTime * 300);
}



void Boat::Update(float DeltaTime)
{
    Actor::Update(DeltaTime);
    fireCooldown += DeltaTime;
    float2 position = GetPosition();
    const float2 size = GetSize();

    float x = XLoopCheck(position, size);
    float y = YLoopCheck(position, size);
    
    SetPosition(float2(x,y));
}

void Boat::SetRotation(float rotation)
{
    boatRotation = rotation;
}


std::shared_ptr<SDL_Texture> Boat::GetTexture()
{
    return TextureFlyWeight::Instance->PlayerTexture;
}

void Boat::RenderPass(SDL_Renderer* renderer)
{
    if (renderer == nullptr) return;

    SDL_Point center = { Rect->w / 2, Rect->h / 2};

    SDL_RenderCopyEx(renderer, GetTexture().get(), nullptr, Rect, boatRotation, &center, SDL_FLIP_NONE);
    
}

float Boat::YLoopCheck(float2 position, float2 size)
{
    float2 ScreenSize = Core::MidPoint * 2.f;
    if (position.Y <= -size.Y + 50)
    {
        return ScreenSize.Y + size.Y - 51;
    }

    if (position.Y >= ScreenSize.Y + size.Y - 50)
    {
        return -size.Y + 51;
    }

    return position.Y;
}

float Boat::XLoopCheck(float2 position, float2 size)
{
    float2 ScreenSize = Core::MidPoint * 2.f;
    if (position.X <= -size.X + 50)
    {
        return ScreenSize.X + size.X - 51;
    }

    if (position.X >= ScreenSize.X + size.X - 50)
    {
        return -size.X + 51;
    }

    return position.X;
}