#pragma once
#include <string>

using namespace std;

class UtilLogShell
{
public:

	typedef enum Log_Level
	{
		RUN_LOG = 1, ERROR_LOG, DEBUG_LOG, INFO_LOG, WARN_LOG, NETPACKAGE_LOG
	} LOG_LEVEL;

	UtilLogShell(LOG_LEVEL level, const char *file, int lineNo);
	~UtilLogShell();

private:
	class CFormatLog
	{
	public:
		CFormatLog(LOG_LEVEL level);
		~CFormatLog();

		CFormatLog& operator<<(bool b);
		CFormatLog& operator<<(char c);
		CFormatLog& operator<<(signed short ss);
		CFormatLog& operator<<(unsigned short us);
		CFormatLog& operator<<(int i);
		CFormatLog& operator<<(unsigned int ui);
		CFormatLog& operator<<(signed long sl);
		CFormatLog& operator<<(unsigned long ul);
		CFormatLog& operator<<(long long ll);
		CFormatLog& operator<<(unsigned long long ull);
		CFormatLog& operator<<(float f);
		CFormatLog& operator<<(double d);
		CFormatLog& operator<<(const char *p);
		CFormatLog& operator<<(const void *p);
		CFormatLog& operator<<(const std::string &str);

	public:
		string getLogInfo(){ return m_buffer; }

	private:
		void print();

	private:
		string		m_buffer;
		LOG_LEVEL	m_level;
	};

public:
	CFormatLog& formatLog();

private:
	CFormatLog *m_formatLog;
	char        m_fileName[256];
	int         m_lineNo;
	int         m_logLevel;

};

#define LOG_RUN        UtilLogShell(UtilLogShell::RUN_LOG,        __FILE__, __LINE__).formatLog()
#define LOG_DEBUG      UtilLogShell(UtilLogShell::DEBUG_LOG,      __FILE__, __LINE__).formatLog()
#define LOG_WARN       UtilLogShell(UtilLogShell::WARN_LOG,       __FILE__, __LINE__).formatLog()
#define LOG_ERROR      UtilLogShell(UtilLogShell::ERROR_LOG,      __FILE__, __LINE__).formatLog()
#define LOG_INFO       UtilLogShell(UtilLogShell::INFO_LOG,       __FILE__, __LINE__).formatLog()
#define LOG_NETPACKAGE UtilLogShell(UtilLogShell::NETPACKAGE_LOG, __FILE__, __LINE__).formatLog()