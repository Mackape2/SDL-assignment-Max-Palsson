#pragma once
#include <memory>
#include <SDL_rect.h>
#include <SDL_render.h>
#include "../Struct/float2.h"
#include "../Util/TextureFlyWeight.h"



class Actor
{
public:
    Actor(SDL_Rect* Rect, int CollisionRadius);
    virtual ~Actor() = default;
    
#pragma region Params
public:
    bool Enabled = true;
    int CollisionRadius;
    bool ShouldBeDestroyed;
protected:
    float DeltaTime = 0;

    virtual std::shared_ptr<SDL_Texture> GetTexture();

    const float2 GetSize() const;

    SDL_Rect* Rect;
    float2 Position;
    float2 Offset;

    TextureFlyWeight* textureFlyWeight;
#pragma endregion
    

#pragma region Functions
public: 
    float2 GetPosition() const;
    void SetPosition(float2 Position);
    void GetRotation(float Rotation);
    void SetSize(float2 size);
    void AddPositionOffset(float2 DeltaPosition);
    virtual void RenderPass(SDL_Renderer* renderer);
    virtual void Destroy();

    virtual void Update(float DeltaTime);
#pragma endregion
};
