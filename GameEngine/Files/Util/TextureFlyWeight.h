#pragma once
#include <memory>
#include <SDL_render.h>

struct sdl_deleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

class TextureFlyWeight
{
public:
    TextureFlyWeight(const char* beachballFilePath,  const char* playerFilePath);

    static inline TextureFlyWeight* Instance;

    std::shared_ptr<SDL_Texture> BeachballTexture;
    std::shared_ptr<SDL_Texture> PlayerTexture;

    SDL_Texture* CreateTexture(const char* filePath);
};