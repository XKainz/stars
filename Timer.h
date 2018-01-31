#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL_timer.h>


class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();
		Uint32 getDifferenceTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;
		Uint32 mDifferenceTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif // TIMER_H
