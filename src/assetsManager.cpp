#include "assetManager.h"

Texture2D AssetManager::penguinIdle;
Texture2D AssetManager::penguinRun;
Texture2D AssetManager::penguinDeath;

Texture2D AssetManager::snowmanIdle;
Texture2D AssetManager::snowmanRun;
Texture2D AssetManager::snowmanDeath;

Texture2D AssetManager::snowBalls;
Texture2D AssetManager::snowBallsPile;

Texture2D AssetManager::barePlatforms;
Texture2D AssetManager::snowyPlatformCorners;
Texture2D AssetManager::snowyPlatforms;
Texture2D AssetManager::snowyPlatformsAngled;

void AssetManager::loadAssets()
{
    penguinIdle = LoadTexture("assets/Penguin/PenguinIdleAnim.png");
    penguinRun = LoadTexture("assets/Penguin/PenguinRunAnim.png");
    penguinDeath = LoadTexture("assets/Penguin/PenguinDeathAnim.png");

    snowmanIdle = LoadTexture("assets/Snowman/SnowManIdle.png");
    snowmanRun = LoadTexture("assets/Snowman/SnowManRun.png");
    snowmanDeath = LoadTexture("assets/Snowman/SnowManDeathAnimation.png");

    snowBalls = LoadTexture("assets/Snowballs/SnowBalls.png");
    snowBallsPile = LoadTexture("assets/Snowballs/SnowBallsPile.png");

    barePlatforms = LoadTexture("assets/Platforms/BarePlatforms.png");
    snowyPlatformCorners = LoadTexture("assets/Platforms/SnowyPlatformCorners.png");
    snowyPlatforms = LoadTexture("assets/Platforms/SnowyPlatforms.png");
    snowyPlatformsAngled = LoadTexture("assets/Platforms/SnowyPlatformsAngled.png");
}

void AssetManager::unloadAssets()
{
    UnloadTexture(penguinIdle);
    UnloadTexture(penguinRun);
    UnloadTexture(penguinDeath);

    UnloadTexture(snowmanIdle);
    UnloadTexture(snowmanRun);
    UnloadTexture(snowmanDeath);

    UnloadTexture(snowBalls);
    UnloadTexture(snowBallsPile);
    
    UnloadTexture(barePlatforms);
    UnloadTexture(snowyPlatformCorners);
    UnloadTexture(snowyPlatforms);
    UnloadTexture(snowyPlatformsAngled);
}