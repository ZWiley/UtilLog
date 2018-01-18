#include "writelog.h"

#include <time.h>
#include <sys/timeb.h>  
#include <sys/stat.h>   
#include <fcntl.h>

using namespace std;

writelog writelog::m_instance;
FILE *writelog::m_pRunFile = NULL;
FILE *writelog::m_pErrFile = NULL;
FILE *writelog::m_pDebugFile = NULL;
FILE *writelog::m_pInfoFile = NULL;
FILE *writelog::m_pWarnFile = NULL;

writelog* writelog::Instance()
{
	return &m_instance;
}

writelog::writelog()
{
	m_Bytes = 0;
	memset(m_szExeName, 0x0, MAX_PATH);
	char szExe[MAX_PATH] = { 0x0 };
	GetModuleFileName(NULL, szExe, MAX_PATH);	
	const char* pszExeName = strrchr(szExe, '\\');
	// \xxx.exe
	int len = strlen(pszExeName);
	strncpy(m_szExeName, pszExeName + 1, len-5); 
}

writelog::~writelog()
{

}

void writelog::Run(const char* buffer)
{
	this->write(getFileName(TYPERUN), buffer, TYPERUN);
}

void writelog::Info(const char* buffer)
{
	this->write(getFileName(TYPEINFO), buffer, TYPEINFO);
}

void writelog::Debug(const char* buffer)
{
	this->write(getFileName(TYPEDBG), buffer, TYPEDBG);
}

void writelog::Warn(const char* buffer)
{
	this->write(getFileName(TYPEWARN), buffer, TYPEWARN);
}

void writelog::Error(const char* buffer)
{
	this->write(getFileName(TYPEERR), buffer, TYPEERR);
}

void writelog::NetworkPackage(const char* buffer)
{
	this->write(getFileName(TYPERUN), buffer, TYPERUN);
}

std::string writelog::getFileName(int type)
{
	char szLogPath[MAX_PATH] = {0x0};
	strcat(szLogPath, m_szExeName);
	switch (type)
	{
	case TYPERUN:
		strcat(szLogPath, "_run");
		break;

	case TYPEERR:
		strcat(szLogPath, "_error");
		break;

	case TYPEDBG:
		strcat(szLogPath, "_debug");
		break;

	case TYPEINFO:
		strcat(szLogPath, "_info");
		break;

	case TYPEWARN:
		strcat(szLogPath, "_warn");
		break;

	}
	return makeFileDate(szLogPath);
}

char* LogFileTime(bool isDate = true)
{
	struct  tm      *ptm;
	struct  timeb   stTimeb;
	static  char    szTime[9] = {0x0};

	ftime(&stTimeb);
	ptm = localtime(&stTimeb.time);
	if (isDate)
	{
		sprintf(szTime, "_%04d%02d%02d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
	}
	else
	{
		sprintf(szTime, "_%02d%02d%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	}
	
	return szTime;
}

std::string writelog::makeFileDate(const string &filename)
{
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;
	string strOldLogFilePath = string(szFilePath) + string("log\\") + filename + LogFileTime() + string(".log");
	return strOldLogFilePath;
}

void writelog::write(const string &filename, const char* buffer, int type)
{
	switch (type)
	{
	case TYPERUN:
	{
		if (NULL == m_pRunFile)
		{
			m_pRunFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pRunFile);
		break;
	}

	case TYPEERR:
	{
		if (NULL == m_pErrFile)
		{
			m_pErrFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pErrFile);
		break;
	}

	case TYPEDBG:
	{
		if (NULL == m_pDebugFile)
		{
			m_pDebugFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pDebugFile);
		break;
	}

	case TYPEINFO:
	{
		if (NULL == m_pInfoFile)
		{
			m_pInfoFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pInfoFile);
		break;
	}

	case TYPEWARN:
	{
		if (NULL == m_pWarnFile)
		{
			m_pWarnFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pWarnFile);
		break;
	}

	default:
		break;
	}
}

void writelog::write(const string &filename, const char* buffer, FILE *&pFile)
{	
	string _buffer = buffer;
	_buffer.append("\n");
	int len = _buffer.length();
	fwrite(_buffer.c_str(), _buffer.length(), sizeof(char), pFile);
	fflush(pFile);

	// 累加写入内容大小再比较
	m_Bytes += len;
	if (m_Bytes >= MAX_FILE_SIZE)
	{
		m_Bytes = 0;
		fclose(pFile);

		string strNewLogFile = filename + LogFileTime(false);
		rename(filename.c_str(), strNewLogFile.c_str());

		pFile = NULL;
	}	

	Sleep(10);
}
