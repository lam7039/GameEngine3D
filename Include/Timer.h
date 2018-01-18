#ifndef TIMER_H
#define TIMER_H

#include "std.h"

namespace se {

	///
	/// You can use this class to get the time elapsed from the specified start
	///
	class Timer {
	public:
		Timer();

		///
		/// Start the timer
		///
		void Start();
		///
		/// Pause the timer
		///
		void Pause();
		///
		/// Resume the timer
		///
		void Resume();
		///
		/// Stop the timer
		///
		void Stop();

		///
		/// Get the microseconds passed
		///
		long long Microseconds();
		///
		/// Get the milliseconds passed
		///
		long long Milliseconds();
		///
		/// Get the seconds passed
		///
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

}

#endif
