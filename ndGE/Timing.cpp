#include "Timing.h"

#include <SDL2/SDL.h>

ndGE::FpsLimiter::FpsLimiter(float maxFPS) : _maxFPS(maxFPS), _frameTime(0) {}

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
    // Stores all the frame times for each frame to average
    static float frameTimes[NUM_SAMPLES];
    // The current frame we are on
    static int currentFrame = 0;
    // The ticks of the previous frame
    static Uint32 prevTicks = SDL_GetTicks();

    // Ticks for the current frame
    Uint32 currentTicks = SDL_GetTicks();

    // Calculate the number of ticks (ms) for this frame
    _frameTime = (float)(currentTicks - prevTicks);
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    // Current ticks is now previous ticks
    prevTicks = currentTicks;

    // The number of frames to average
    int cnt;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        cnt = currentFrame;
    } else {
        cnt = NUM_SAMPLES;
    }

    // Average all the frame times
    float frameTimeAverage = 0;
    for (int i = 0; i < cnt; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= cnt;

    // Calculate FPS
    if (frameTimeAverage > 0) {
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.0f;
    }
}
