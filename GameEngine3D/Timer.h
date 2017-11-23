#ifndef TIMER_H
#define TIMER_H

#include "std.h"

SE_BEGIN_NAMESPACE

class Timer {
public:
	Timer();

	void Start();
	void Pause();
	void Resume();
	void Stop();

	long long Microseconds();
	long long Milliseconds();
	long long Seconds();

private:
	bool m_hasStarted;
	bool m_isPaused;
	long long m_startTime;
	long long m_pausedTime;
	long long m_frequency;

	long long GetPerformanceFrequency();
	long long GetPerformanceCounter();
};

SE_END_NAMESPACE

#endif
