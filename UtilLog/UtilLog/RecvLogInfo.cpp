#include "RecvLogInfo.h"
#include "writelog.h"

RecvLogInfo RecvLogInfo::m_instance;
mutex RecvLogInfo::m_mutex;

RecvLogInfo::RecvLogInfo()
{
}


RecvLogInfo::~RecvLogInfo()
{
}

void RecvLogInfo::write(int logLevel, const char* buffer)
{
	m_mutex.lock();
	if (buffer)
	{
		switch (logLevel)
		{
		case RUN:
			writelog::Instance()->Run(buffer);
			break;

		case ERRORS:
			writelog::Instance()->Error(buffer);
			break;

		case DEBUGS:
			writelog::Instance()->Debug(buffer);
			break;

		case INFO:
			writelog::Instance()->Info(buffer);
			break;

		case WARN:
			writelog::Instance()->Warn(buffer);
			break;

		case NETPACKAGE:
			writelog::Instance()->NetworkPackage(buffer);
			break;

		default:
			break;
		}
	}
	m_mutex.unlock();
}
