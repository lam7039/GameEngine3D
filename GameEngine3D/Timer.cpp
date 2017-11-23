#include <Windows.h>
#include "Timer.h"

SE_BEGIN_NAMESPACE

Timer::Timer() {
	m_pausedTime = 0;
	m_startTime = 0;
	m_frequency = 0;
	m_hasStarted = false;
	m_isPaused = false;
}

void Timer::Start() {
	if (!m_hasStarted) {
		m_startTime = GetPerformanceCounter();
		m_frequency = GetPerformanceFrequency();
		m_hasStarted = true;
	}
}

void Timer::Stop() {
	if (m_hasStarted) {
		m_hasStarted = false;
		m_isPaused = false;
		m_pausedTime = 0;
		m_startTime = 0;
		m_frequency = 0;
	}
}

void Timer::Pause() {
	if (m_hasStarted && !m_isPaused) {
		m_isPaused = true;
		long long now;
		now = GetPerformanceCounter();
		m_pausedTime = (now - m_startTime) * 1000000 / m_frequency;
	}
}

void Timer::Resume() {
	m_isPaused = false;
	m_pausedTime = 0;
}

long long Timer::Microseconds() {
	if (!m_hasStarted) {
		return 0;
	}
	if (m_isPaused) {
		return m_pausedTime;
	}
	long long now = GetPerformanceCounter();
	return (now - m_startTime) * 1000000 / m_frequency;
}

long long Timer::Milliseconds() {
	return Microseconds() / 1000;
}

long long Timer::Seconds() {
	return Microseconds() / 1000 / 1000;
}

long long Timer::GetPerformanceFrequency() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency.QuadPart;
}

long long Timer::GetPerformanceCounter() {
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return counter.QuadPart;
}

SE_END_NAMESPACE