#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>

class LogControl
{
private:
	struct LogEntry {
		std::string Message;
		std::string MacAddress;
		std::string IP;
		std::string Account;
		time_t Timestamp;
	};

	std::string m_sDir;
	std::unique_ptr<std::ofstream> m_pStream;
	
	std::queue<LogEntry> m_LogQueue;
	std::mutex m_QueueMutex;
	std::condition_variable m_Condition;
	std::thread m_WorkerThread;
	std::atomic<bool> m_ExitThread;

	void ProcessLogs();

public:
	LogControl();
	~LogControl();

	void Initialize(std::string LogName);
	void WriteLog(std::string Message, std::string MacAddress, std::string IP, std::string Account);
	void Reset(std::string LogName);
};

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	int size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) { throw std::runtime_error("Error during formatting."); }
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
