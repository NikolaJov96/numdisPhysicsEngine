#ifndef TIMING_H
#define TIMING_H

namespace ndGE {

    /**
     * Class that calculates and limits FPS
     */
    class FpsLimiter {
    public:
        FpsLimiter(float maxFPS = DEFAULT_MAX_FPS);
        float getDelatTime() { return _frameTime; } //!< Returns length of previous frame
        void setMaxFPS(float maxFPS);               //!< Update desired FPS
        void begin();                               //!< Method that indicates beginning of the iteration
        float end();                                //!< Indicates end of the iteration, returns the current FPS
    private:
        void calculateFPS();                        //!< Calculates the current FPS

        float _fps;                                 //!< Last calculated FPS value
        float _maxFPS;                              //!< Desired FPS value
        float _frameTime;                           //!< Time length of the frame
        unsigned int _startTicks;                   //!< Number of SDL ticks at the start of the iteration

        static constexpr float DEFAULT_MAX_FPS = 60.0f; //!< Default desired FPS value
        static const int NUM_SAMPLES = 10;  //!< The number of frames to average when calculating current FPS
    };

}

#endif // TIMING_H
