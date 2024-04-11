#pragma once
#include "chrono"

class Timer
{
public:
	void start();
	float stop();

private:
	bool _isRunning = false;
	std::chrono::time_point<std::chrono::steady_clock> _startTime;
};