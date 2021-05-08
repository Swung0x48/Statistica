#pragma once
#include <BML/BMLAll.h>
#include <chrono>

class Hiperf_Timer
{
private:
	int64_t time_ = 0;
	std::chrono::steady_clock::time_point begin_;
	bool is_running_ = false;
public:
	Hiperf_Timer(long initTime = 0) : time_(initTime) {};
	inline void Start() {
		if (!is_running_) {
			is_running_ = true;
			begin_ = std::chrono::steady_clock::now();
		}
	}
	inline void Stop() {
		if (is_running_) {
			time_ += duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - begin_).count();
			is_running_ = false;
		}
	}
	inline void Reset() {
		time_ = 0;
	}
	inline int64_t GetTime() {
		if (is_running_)
			return this->time_ + duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - begin_).count();

		return this->time_;
	}


};

