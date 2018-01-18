#ifndef RECVLOGINFO_H
#define RECVLOGINFO_H
#include <mutex>
using namespace std;

class RecvLogInfo
{
public:
	static RecvLogInfo* instance() { return &m_instance; }
private:
	RecvLogInfo();
	~RecvLogInfo();

	typedef enum Log_Level
	{
		RUN = 1,
		ERRORS, 
		DEBUGS, 
		INFO, 
		WARN, 
		NETPACKAGE
	}LOG_LEVEL;

private:
	static RecvLogInfo m_instance;
	static mutex m_mutex;

public:
	static void write(int logLevel, const char* buffer);
};

#endif