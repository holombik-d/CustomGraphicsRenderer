#include "Timer.h"

void Timer::start()
{
	if(_isRunning)
	{
		return;
	}

	_isRunning = true;
	_startTime = std::chrono::steady_clock::now();
}

float Timer::stop()
{
	if(!_isRunning)
	{
		return 0;
	}

	_isRunning = false;
	auto stopTime = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(stopTime - _startTime).count() / 1000.f;
}