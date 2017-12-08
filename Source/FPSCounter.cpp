#include "FPSCounter.h"

namespace se {

	FPSCounter::FPSCounter() {
		m_frames = 0;
		m_lastTime = 0;
		m_oldTime = 0;
		m_newTime = 0;
		m_fps = 0;
		time.Start();
	}

	void FPSCounter::Update() {
		m_deltaTime = (float)(m_newTime - m_oldTime) / 1000000.0f;
		m_oldTime = m_newTime;
		m_newTime = time.Microseconds();

		if (m_newTime - m_lastTime >= 1000000) {
			m_lastTime = m_newTime;
			m_fps = m_frames;
			m_frames = 0;
		}
		m_frames++;
	}

	int FPSCounter::GetFPS() {
		return m_fps;
	}

	float FPSCounter::GetDelta() {
		return m_deltaTime;
	}

	float FPSCounter::GetTimeMilliseconds() {
		return time.Milliseconds();
	}

}
