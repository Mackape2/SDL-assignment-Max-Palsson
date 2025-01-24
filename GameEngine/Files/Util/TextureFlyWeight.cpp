#include "TextureFlyWeight.h"

#include <SDL_image.h>

#include "../Core.h"

TextureFlyWeight::TextureFlyWeight(const char* beachballFilePath, const char* playerFilePath)
{
    Instance = this;
    BeachballTexture = std::shared_ptr<SDL_Texture>(CreateTexture(beachballFilePath), sdl_deleter());
    PlayerTexture = std::shared_ptr<SDL_Texture>(CreateTexture(playerFilePath), sdl_deleter());
}

SDL_Texture* TextureFlyWeight::CreateTexture(const char* filePath)
{
    SDL_Surface* surface = IMG_Load(filePath);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Core::renderer, surface);

    SDL_FreeSurface(surface);

    return texture;
}
