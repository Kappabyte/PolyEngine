#pragma once
#define DEBUG(...)
#define INFO(...)
#define WARN(...)
#define ERROR(...)
#define FATAL(...)

enum class LogLevel {
	DEBUG,
	INFO,
	WARN,
	ERROR,
	FATAL
};


class Logger {
public:
	static Logger* getInstance() {
		if (!instance) instance = new Logger;
		return instance;
	}

	void log(LogLevel level, ...);
private:
	Logger() {}
	static Logger* instance;
};