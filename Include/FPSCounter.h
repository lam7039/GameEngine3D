#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "std.h"
#include "Timer.h"

namespace se {

	class FPSCounter {
	public:
		FPSCounter();
		void Update();
		int GetFPS();
		float GetDelta();
		float GetTimeMilliseconds();
	private:
		long long m_frames;
		long long m_lastTime;
		long long m_oldTime;
		long long m_newTime;
		float m_deltaTime;
		int m_fps;
		Timer time;
	};

}

#endif
