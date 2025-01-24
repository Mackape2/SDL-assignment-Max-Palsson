#pragma once
#include "../Factories/BeachballFactory.h"
#include "../Struct/float2.h"
#include "../Util/Random.h"

class BeachballSpawner
{
public:
    BeachballSpawner(float minSpawnTime, float maxSpawnTime, float radius, float2 screenSize);
private:
    float radius;
    float maxSpawnTime;
    float minSpawnTIme;

    float time;

    float cooldown;

    float2 screenSize;

    float2 midPoint;

    float totalElapsedTime;
    
    Random random;

    BeachballFactory beachballFactory;

protected:

    void SpawnNew();
public:
    void Update(float DeltaTime);
};
