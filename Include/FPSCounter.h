#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "Timer.h"

namespace se {

	///
	/// You can use this class to get the fps and delta
	///
	class FPSCounter {
	public:
		FPSCounter();
		void Update();
		///
		/// Get the delta
		///
		float GetDelta() const;
		///
		/// Get the frames per second
		///
		int GetFPS() const;
	private:
		long long m_frames;
		long long m_lastTime;
		long long m_oldTime;
		long long m_newTime;
		float m_deltaTime;
		int m_fps;
		Timer m_time;
	};

}

#endif
