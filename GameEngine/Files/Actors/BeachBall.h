#pragma once

#include "../BaseClasses/Actor.h"
#include "../Interfaces/IVelocity.h"

class BeachBall final : public Actor, public IVelocity
{
public:
    BeachBall(SDL_Rect* rect, const char fielPath[], int collisionRadius, float speed, float2 direction);
    //~BeachBall()() override = default;

    void Update(float deltaTime);

    void RenderPass(SDL_Renderer* renderer);

    std::shared_ptr<SDL_Texture> GetTexture() override;

    void Destroy();

    float RotationSpeed = 0.0f;
    float Rotation = 0.0f;
    
private:
    const float MaxLifeTime = 10.f;
    float LifeTime = 0;
};
