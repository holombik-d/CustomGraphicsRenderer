#pragma once
#include <iostream>

class Logger
{
public:
	template <typename ... Args>
	static void log(unsigned int logLevel, Args...args)
	{
		setLogLevel(logLevel);

		if(logLevel <= _logLevel)
		{
			std::printf(args...);
		}
	}

	static void setLogLevel(unsigned int inLogLevel)
	{
		inLogLevel <= 9 ? _logLevel = inLogLevel : _logLevel = 9;
	}
private:
	static unsigned int _logLevel;
};