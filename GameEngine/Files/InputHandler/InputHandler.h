#pragma once
#include <SDL.h>
#include <functional>
#include <iostream>
#include "../Struct/float2.h"

class InputHandler
{
public:

    using MoveInputCallBack = std::function<void(float2*)>;
    
    MoveInputCallBack MoveInput;
    
    float2* Input;
    float2* MousePosition;
    
    bool mouseClicked = false;

    bool LeftKey = false;
    bool RightKey = false;
    bool UpKey = false;
    bool DownKey = false;
    
    InputHandler()
    {
        Input = new float2();
        MousePosition = new float2();
        mouseClicked = false;
    }
    
    void HandleKeyDownInputs(SDL_Keycode key_code,Boat* player)
    {
        switch (key_code)
        {
        case SDLK_w:
            UpKey = true;
            player->SetRotation(270);
            break;
        case SDLK_s:
            DownKey = true;
            player->SetRotation(90);
            break;
        case SDLK_a:
            LeftKey= true;
            player->SetRotation(180);
            break;
        case SDLK_d:
            RightKey = true;
            player->SetRotation(0);
            break;
        }
    }

    void HandleKeyUpInputs(SDL_Keycode key_code)
    {
        switch (key_code)
        {
        case SDLK_w:
            UpKey = false;
            break;
        case SDLK_s:
            DownKey = false;
            break;
        case SDLK_a:
            LeftKey = false;
            break;
        case SDLK_d:
            RightKey = false;
            break;
        }
    }

    void HandleInputEvents()
    {
        Input->X = Input->Y = 0;
        
        if(UpKey) 
            Input->Y += -1;
        if(DownKey)
            Input->Y += 1;
        if(LeftKey)
            Input->X += -1;
        if(RightKey)
            Input->X += 1;
            
        
        
        if(MoveInput)
            MoveInput(Input);
    }
};
