#pragma once

#include "../Struct/float2.h"
#include "../Actors/BeachBall.h"

class BeachballFactory
{
private:
    const char* filePath;
    
public:
    BeachballFactory();
    ~BeachballFactory() = default;
    
    BeachBall* CreateBeachball(float2 position, int size, float2 direction, float speed) const;
};
