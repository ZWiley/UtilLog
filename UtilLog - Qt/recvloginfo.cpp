#include "recvloginfo.h"
#include "writelog.h"
#include <QByteArray>

CWriteLog g_writeLog;
CRecvLogInfo CRecvLogInfo::m_instance;

CRecvLogInfo::CRecvLogInfo(QObject *parent) :  QObject(parent)
{
}

void CRecvLogInfo::RecvLogInfo(int logLevel, QByteArray logInfo)
{
    write(logLevel, logInfo);
}

void CRecvLogInfo::write(int logLevel, const QByteArray &buffer)
{    
    if (!buffer.isEmpty())
    {
        switch (logLevel)
        {
        case CRecvLogInfo::RUN:
            g_writeLog.Run(buffer);
            break;

        case CRecvLogInfo::ERROR:
            g_writeLog.Error(buffer);
            break;

        case CRecvLogInfo::DEBUG:
            g_writeLog.Debug(buffer);
            break;

        case CRecvLogInfo::INFO:
            g_writeLog.Info(buffer);
            break;

        case CRecvLogInfo::WARN:
            g_writeLog.Warn(buffer);
            break;

        case CRecvLogInfo::NETPACKAGE:
            g_writeLog.NetworkPackage(buffer);
            break;

        default:
            break;
        }
    }
}
