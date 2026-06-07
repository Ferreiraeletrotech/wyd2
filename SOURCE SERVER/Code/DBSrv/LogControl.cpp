#include "LogControl.h"
#include <ctime>

using namespace std;

LogControl::LogControl() : m_ExitThread(false)
{
	m_sDir = std::string();
	m_pStream = std::make_unique<std::ofstream>();
	m_WorkerThread = std::thread(&LogControl::ProcessLogs, this);
}

LogControl::~LogControl()
{
	m_ExitThread = true;
	m_Condition.notify_one();
	if (m_WorkerThread.joinable())
		m_WorkerThread.join();

	if (m_pStream && m_pStream->is_open()) {
		m_pStream->close();
	}
}

void LogControl::Initialize(std::string LogName)
{
	if (LogName.empty())
		return;

	std::lock_guard<std::mutex> lock(m_QueueMutex);
	m_sDir = LogName;

	if (m_pStream->is_open()) {
		m_pStream->close();
		m_pStream->clear();
	}

	m_pStream->open(m_sDir.c_str(), std::ios_base::app);
}

void LogControl::Reset(std::string LogName)
{
	Initialize(LogName);
}

void LogControl::WriteLog(std::string Message, std::string MacAddress, std::string IP, std::string Account)
{
	LogEntry entry;
	entry.Message = Message;
	entry.MacAddress = MacAddress;
	entry.IP = IP;
	entry.Account = Account;
	time(&entry.Timestamp);

	{
		std::lock_guard<std::mutex> lock(m_QueueMutex);
		m_LogQueue.push(entry);
	}
	m_Condition.notify_one();
}

void LogControl::ProcessLogs()
{
	while (!m_ExitThread || !m_LogQueue.empty())
	{
		std::unique_lock<std::mutex> lock(m_QueueMutex);
		m_Condition.wait(lock, [this] { return !m_LogQueue.empty() || m_ExitThread; });

		while (!m_LogQueue.empty())
		{
			LogEntry entry = m_LogQueue.front();
			m_LogQueue.pop();

			if (m_pStream && m_pStream->is_open())
			{
				struct tm when;
				localtime_r(&entry.Timestamp, &when);

				char tmp_msg[2048] = { 0, };
				snprintf(tmp_msg, sizeof(tmp_msg), "(%02d/%02d/%04d|%02d:%02d:%02d) [%s|%s|%s] : %s\n",
					when.tm_mday, when.tm_mon + 1, when.tm_year + 1900, when.tm_hour, when.tm_min, when.tm_sec,
					entry.Account.c_str(), entry.MacAddress.c_str(), entry.IP.c_str(), entry.Message.c_str());

				*m_pStream << tmp_msg;
				m_pStream->flush();
			}
		}
	}
}
