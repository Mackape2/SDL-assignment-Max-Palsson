#pragma once
#include <SDL_events.h>
#include <vector>

#include "BaseClasses/Actor.h"
#include "Util/TextureFlyWeight.h"
#include "Actors/Boat.h"
#include "Factories/BeachballFactory.h"
#include "Spawners/BeachballSpawner.h"

class Core
{
public:
    Core(SDL_Renderer* renderer);
    ~Core();

    SDL_Event e;

public:
    static inline std::vector<std::unique_ptr<Actor>> Actors;

    static inline float2 MidPoint = float2(1024/2, 768/2);

    static SDL_Renderer* renderer;

    BeachballFactory beachballFactory;
    
    static TextureFlyWeight* TextureFlyWeight;

    InputHandler* input_handler;

    static Boat* player;
private:
    bool quit = false;
    bool restart = false;
    float LastFrameTime;

    SDL_Color whiteColor = {255, 255, 255, 255};

    BeachballSpawner* beachballSpawner;
public:
    void Start();
    void Inputs();
    void UpdateObjects();
    void Collision();
    void RenderPass(SDL_Renderer* renderer);
    void Cleanup();
    bool Quit()
    {
        return quit;
    }
};
