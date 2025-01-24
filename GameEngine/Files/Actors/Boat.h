#pragma once
#include "../BaseClasses/Actor.h"
#include "../Interfaces/IVelocity.h"

class InputHandler;

class Boat final : public Actor, IVelocity
{
public:
    Boat(SDL_Rect* rect, const char filePath[], int collisionRadius, float speed, float2 direction);

    void RenderPass(SDL_Renderer* renderer);
    void SetRotation(float rotation);
    void Move(float2* input);
    void Update(float DeltaTime);
    std::shared_ptr<SDL_Texture> GetTexture() override;


private:
    float YLoopCheck(float2 position, float2 size);
    float XLoopCheck(float2 position, float2 size);
    float fireCooldown = 0.0f;
    float fireRate = 0.3f;
    float boatRotation = 0.0f;
};