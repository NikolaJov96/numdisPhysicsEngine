#include <SDL2/SDL.h>

#include "Timing.h"

ndGE::FpsLimiter::FpsLimiter(float maxFPS) : _maxFPS(maxFPS) {}

void ndGE::FpsLimiter::setMaxFPS(float maxFPS) {
    _maxFPS = maxFPS;               // Update desired FPS value
}

void ndGE::FpsLimiter::begin()
{
    _startTicks = SDL_GetTicks();   // Store number of SDL tick at he beginning of the iteration
}

float ndGE::FpsLimiter::end()
{
    calculateFPS();
    float frameTicks = (float)(SDL_GetTicks() - _startTicks);
    if (1000.0f / _maxFPS > frameTicks)
        SDL_Delay((Uint32)(1000.0f / _maxFPS - frameTicks));    // Limit the FPS to the max FPS
    return _fps;
}

void ndGE::FpsLimiter::calculateFPS()
{
    //Stores all the frametimes for each frame that we will average
    static float frameTimes[NUM_SAMPLES];
    //The current frame we are on
    static int currentFrame = 0;
    //the ticks of the previous frame
    static Uint32 prevTicks = SDL_GetTicks();

    //Ticks for the current frame
    Uint32 currentTicks = SDL_GetTicks();

    //Calculate the number of ticks (ms) for this frame
    _frameTime = (float)(currentTicks - prevTicks);
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    //current ticks is now previous ticks
    prevTicks = currentTicks;

    //The number of frames to average
    int count;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }

    //Average all the frame times
    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    //Calculate FPS
    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.0f;
    }
}
