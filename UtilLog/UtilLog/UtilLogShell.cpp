#include "UtilLogShell.h"
#include "recvloginfo.h"

#include <string>
#include <time.h>
#include <atlstr.h>
#include <sys/timeb.h>  

using namespace std;

char* log_Time(void)
{
	struct  tm      *ptm;
	struct  timeb   stTimeb;
	static  char    szTime[23];

	ftime(&stTimeb);
	ptm = localtime(&stTimeb.time);
	sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d.%03d", ptm->tm_year + 1900,
		    ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, stTimeb.millitm/1000);
	return szTime;
}

UtilLogShell::UtilLogShell(LOG_LEVEL level, const char *file, int lineNo)
{
	m_logLevel = int(level);
	memset(m_fileName, 0x0, MAX_PATH);
	const char* pos = NULL;
	pos = strrchr(file, '\\');
	strcpy(m_fileName, pos + 1);

	m_lineNo = lineNo;
	m_formatLog = new CFormatLog(level);
}

UtilLogShell::~UtilLogShell()
{
	if (m_formatLog)
	{
		RecvLogInfo::instance()->write(m_logLevel, m_formatLog->getLogInfo().c_str());
		delete m_formatLog;
		m_formatLog = NULL;
	}
}

UtilLogShell::CFormatLog& UtilLogShell::formatLog()
{
	(*m_formatLog) << "[<" << log_Time() << m_fileName << "line:" << m_lineNo << ">]";

	return (*m_formatLog);
}

UtilLogShell::CFormatLog::CFormatLog(LOG_LEVEL level)
{
	m_buffer.clear();
	m_level = level;
}

UtilLogShell::CFormatLog::~CFormatLog()
{

}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(bool b)
{
	string str = ((b) ? "(true)" : "(false)");
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(char c)
{
	string str = "";
	str.push_back(c);
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(signed short ss)
{
	string str = to_string(ss);
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(unsigned short us)
{ 
	string str = to_string(us);	 
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(int i)
{
	string str = to_string(i);	 
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(unsigned int ui)
{
	string str = to_string(ui);	 
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(signed long sl)
{
	string str = to_string(sl);
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(unsigned long ul)
{
	string str = to_string(ul);	 
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(long long ll)
{ 
	string str = to_string(ll);	 
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(unsigned long long ull)
{ 
	string str = to_string(ull);	 
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(float f)
{
	string str = to_string(f);
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(double d)
{
	string str = to_string(d);
	str.append(" ");
	m_buffer.append(str.c_str(), str.length());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(const char *p)
{
	string str = ((NULL != p) ? p : "(NULL)");
	if (str == ">]") 
		str.erase(str.end());
	if (str != "[<") 
		str.append(" ");
	m_buffer.append(str.data(), str.size());
	return *this;
}

UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(const void *p)
{
	string str = "";
	if (p)
	{
		int size = sizeof(const void *);
		char *pointer = new char[size + 1];
		memset(pointer, 0x0, size + 1);
		memcpy(pointer, (char*)&p, size);
		string temp = "";
		str = "0x";
		for (int i = size - 1; i >= 0; i--)
		{
			sprintf(const_cast<char*>(temp.c_str()), "%02X", (int)pointer[i]);
			str.append(temp);
		}
		delete[] pointer;
	}
	else
	{
		str = "(NULL)";
	}

	str.append(" ");
	m_buffer.append(str.c_str(), str.size());
	return *this;
}


UtilLogShell::CFormatLog& UtilLogShell::CFormatLog::operator<<(const std::string &str)
{
	string tmp = ((!str.empty()) ? str : "(NULL)");
	tmp += " ";
	string tmpStr = string(tmp.c_str());
	m_buffer.append(tmpStr.data(), tmpStr.size());
	return *this;
}