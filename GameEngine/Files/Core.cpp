#include "Core.h"

#include <iostream>
#include <SDL_timer.h>

#include "Actors/BeachBall.h"
#include "Util/TextureFlyWeight.h"
#include "Actors/Boat.h"
#include "Collision/CollisionHandler.h"
#include "InputHandler/InputHandler.h"


SDL_Renderer* Core::renderer;

TextureFlyWeight* Core::TextureFlyWeight;

Boat* Core::player;

Core::Core(SDL_Renderer* renderer): e(), LastFrameTime(0)
{
    Core::renderer = renderer;
    quit = false;

    input_handler = new InputHandler();
    
    beachballSpawner = new BeachballSpawner(.1f, .5f, 800, MidPoint*2);
    
    TextureFlyWeight = new class TextureFlyWeight("./img/beachball.png", "./img/boat.png");
}

Core::~Core()
{
    SDL_Delay(1000);
    delete beachballSpawner;
    delete TextureFlyWeight;
    for (int i = Actors.size() - 1; i >= 0; --i)
    {
        Actors[i].reset();
    }
    Actors.clear();
}


void Core::Start()
{
    SDL_Rect* Rect = new SDL_Rect();

    Rect->x = 100;
    Rect->y = 100;
    Rect->w = 100;
    Rect->h = 100;

    player = new Boat(Rect, "./img/boat.png", 50, 1.5f, float2(0,0));
    input_handler->MoveInput = std::bind(&Boat::Move, player, std::placeholders::_1);

}

void Core::Inputs()
{
    while (SDL_PollEvent(&e))
    {
        // check, if it's an event we want to react to:
        switch (e.type) {
        case SDL_QUIT:
            {
                quit = true;
                break;
            }
        case SDL_KEYDOWN:
            {
                input_handler->HandleKeyDownInputs(e.key.keysym.sym,player);
                break;
            }
        case SDL_KEYUP:
            {
                input_handler->HandleKeyUpInputs(e.key.keysym.sym);
                break;
            }
            
        }
    }
    input_handler->HandleInputEvents();
}


void Core::UpdateObjects()
{
    
    const Uint32 CurrentTime = SDL_GetTicks();

    const float DeltaTime = (static_cast<float>(CurrentTime) - LastFrameTime) / 1000.0f;
    
    LastFrameTime = static_cast<float>(CurrentTime);
    
    for (int i = 0; i < Actors.size(); i++)
    {
        if (!Actors[i]->Enabled) continue;
        Actors[i]->Update(DeltaTime);
    }

    beachballSpawner->Update(DeltaTime);
}

void Core::Collision()
{
    if (!player) return;
    for (int i = 0; i < Actors.size(); ++i)
    {
        BeachBall* beachBall = dynamic_cast<BeachBall*>(Actors[i].get());

        if (!beachBall) continue;
        if (!beachBall->Enabled) continue;

        if (CollisionHandler::Collided(player->GetPosition(), player->CollisionRadius, beachBall->GetPosition(), beachBall->CollisionRadius))
        {
            float2 direction1 = player->GetPosition();
            float2 direction2 = beachBall->GetPosition();

            float2 normalizedA = direction1.Normalize();
            float2 normalizedB = direction2.Normalize();

            
            float new_direction = float2::AngleBetweenNormalized(normalizedA, normalizedB);
            if (player->GetPosition().X > beachBall->GetPosition().X)
                new_direction = -new_direction;
            
            beachBall->direction =  beachBall->GetPosition() * new_direction;
            continue;
        }
    }
}

void Core::RenderPass(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    SDL_RenderClear(renderer);
    
    
    for (int i = 0; i < Actors.size(); i++)
    {
        if (!Actors[i]->Enabled) continue;
        Actors[i]->RenderPass(renderer);
    }
    
    SDL_RenderPresent(renderer);
}

void Core::Cleanup()
{
    for (int i = 0; i < Actors.size(); i++)
    {
        if (Actors[i]->ShouldBeDestroyed)
        {
            Actors.erase(Actors.begin() + i);
        }
    }
}
