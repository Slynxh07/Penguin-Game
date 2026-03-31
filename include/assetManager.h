#pragma once

#include "raylib.h"

class AssetManager {
public:
    static Texture2D penguinIdle;
    static Texture2D penguinRun;
    static Texture2D penguinDeath;

    static Texture2D snowmanIdle;
    static Texture2D snowmanRun;
    static Texture2D snowmanDeath;

    static Texture2D snowBalls;
    static Texture2D snowBallsPile;

    static Texture2D barePlatforms;
    static Texture2D snowyPlatformCorners;
    static Texture2D snowyPlatforms;
    static Texture2D snowyPlatformsAngled;

    static void loadAssets();
    static void unloadAssets();
};