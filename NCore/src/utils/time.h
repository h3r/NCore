#pragma once
#include "ncpch.h"

// ----------------------------------------------------------
// To compute time elapsed between ctor and elapsed()
class CTimer {
	uint64_t time_stamp;
public:
	CTimer() {
		Reset();
	}

	// Ticks!
	uint64_t GetTimeStamp() const {
		uint64_t now;
		::QueryPerformanceCounter((LARGE_INTEGER*)&now);
		return now;
	}

	float Elapsed() {
		uint64_t now = GetTimeStamp();
		uint64_t delta_ticks = now - time_stamp;

		LARGE_INTEGER freq;
		if (::QueryPerformanceFrequency(&freq)) {
			float delta_secs = (float)(delta_ticks) / (float)freq.QuadPart;
			return delta_secs;
		}
		nc_fatal("QueryPerformanceFrequency returned false!!!\n");
		return 0.f;
	}

	// Reset counter to current timestamp
	void Reset() {
		time_stamp = GetTimeStamp();
	}

	float ElapsedAndReset() {
		float delta = Elapsed();
		Reset();
		return delta;
	}

	// Operador de 'iguales' -> Tiene que coincidir todo
	bool operator==(CTimer h) const {
		return h.Elapsed() == h.Elapsed();
	}

	bool operator!=(CTimer h) const {
		return h.Elapsed() != h.Elapsed();
	}

	bool operator<(CTimer h) const {
		return h.Elapsed() < h.Elapsed();
	}

	bool operator>(CTimer h) const {
		return h.Elapsed() > h.Elapsed();
	}

	bool operator<=(CTimer h) const {
		return h.Elapsed() <= h.Elapsed();
	}

	bool operator>=(CTimer h) const {
		return h.Elapsed() >= h.Elapsed();
	}

};



// ----------------------------------------------------------
// Holds a global with the elapsed/unscaled and current time
struct TElapsedTime {
	float  delta = 0.f;
	double current = 0.;
	float  scale_factor = 1.0f;
	float  delta_unscaled = 0.f;
	double current_unscaled = 0.;
	void Set(double new_time) {
		delta_unscaled = (float)(new_time - current_unscaled);
		current_unscaled = new_time;
		delta = delta_unscaled * scale_factor;
		current += delta;
	}
};

extern TElapsedTime Time;

