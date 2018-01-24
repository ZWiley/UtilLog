#include "writelog.h"
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QStringList>
#include <QCoreApplication>

//FILE* CWriteLog::m_pRunFile   = NULL;
//FILE* CWriteLog::m_pErrFile   = NULL;
//FILE* CWriteLog::m_pDebugFile = NULL;
//FILE* CWriteLog::m_pInfoFile  = NULL;
//FILE* CWriteLog::m_pWarnFile  = NULL;

void CWriteLog::Run(const QByteArray &buffer)
{
    this->write(getFileName(TYPERUN), buffer, TYPERUN);
}

void CWriteLog::Info(const QByteArray &buffer)
{
    this->write(getFileName(TYPEINFO), buffer, TYPEINFO);
}

void CWriteLog::Debug(const QByteArray &buffer)
{
    this->write(getFileName(TYPEDBG), buffer, TYPEDBG);
}

void CWriteLog::Warn(const QByteArray &buffer)
{
    this->write(getFileName(TYPEWARN), buffer, TYPEWARN);
}

void CWriteLog::Error(const QByteArray &buffer)
{
    this->write(getFileName(TYPEERR), buffer, TYPEERR);
}

void CWriteLog::NetworkPackage(const QByteArray &buffer)
{
    this->write(getFileName(TYPERUN), buffer, TYPERUN);
}

QString CWriteLog::getFileName(int type)
{
    QStringList procargc = QCoreApplication::arguments();
    QFileInfo fi(procargc.at(0));
    QString filename = fi.baseName();
    switch (type)
    {
    case TYPERUN:
        filename.append("_run");
        break;

    case TYPEERR:
        filename.append("_error");
        break;

    case TYPEDBG:
        filename.append("_debug");
        break;

    case TYPEINFO:
        filename.append("_info");
        break;

    case TYPEWARN:
        filename.append("_warn");
        break;

    default:
        filename.clear();
        break;
    }

    return makeFileDate(filename);
}

QString CWriteLog::makeFileDate(const QString &_filename)
{
    qDebug() << "_filename: "<< _filename;
    QDate datanow = QDate::currentDate();
    QString filename = _filename.toLower();
    filename.append('_');
    filename.append(datanow.toString("yyyyMMdd"));
    filename = filename.toLower();

    QString strPath = QCoreApplication::applicationDirPath();
#ifdef Q_OS_WIN
    strPath += "/log/";
#else
    strPath = QString(getenv("HOME")) + QString("/var/log/");
#endif

    filename.prepend(strPath);
    filename.append(".log");
    qDebug() << filename.toLatin1().data();
    QFile file(filename);
    if (file.size() >= MAX_FILE_SIZE)
    {
        QTime timenow = QTime::currentTime();
        QString newfilename = file.fileName();
        newfilename.append(timenow.toString("hhmmss"));
        file.rename(filename, newfilename.toLower());
    }

    return filename;
}

void CWriteLog::write(const QString &filename, const QByteArray &buffer, int type)
{
    switch (type)
    {
        case TYPERUN:
        {
            if (NULL == m_pRunFile)
            {
                m_pRunFile = fopen(filename.toLatin1().data(), "a+w");
            }
            write(filename, buffer, m_pRunFile);
            break;
        }

        case TYPEERR:
        {
            if (NULL == m_pErrFile)
            {
                m_pErrFile = fopen(filename.toLatin1().data(), "a+w");
            }
            write(filename, buffer, m_pErrFile);
            break;
        }

        case TYPEDBG:
        {
            if (NULL == m_pDebugFile)
            {
                m_pDebugFile = fopen(filename.toLatin1().data(), "a+w");
            }
            write(filename, buffer, m_pDebugFile);
            break;
        }

        case TYPEINFO:
        {
            if (NULL == m_pInfoFile)
            {
                m_pInfoFile = fopen(filename.toLatin1().data(), "a+w");
            }
            write(filename, buffer, m_pInfoFile);
            break;
        }

        case TYPEWARN:
        {
            if (NULL == m_pWarnFile)
            {
                m_pWarnFile = fopen(filename.toLatin1().data(), "a+w");
            }
            write(filename, buffer, m_pWarnFile);
            break;
        }

        default:
            break;
    }
}

void CWriteLog::write(const QString &filename, const QByteArray &buffer, FILE *&pFile)
{
    QByteArray _buffer = buffer;
    _buffer.append("\n");
    int size = _buffer.size();
    char *pBuffer = new char[size+1];
    memset(pBuffer, 0x0, size+1);
    memcpy(pBuffer, _buffer.data(), size);
    fwrite(pBuffer, size, sizeof(char), pFile);
    fflush(pFile);
    delete [] pBuffer;

    QFile file(filename);
    if (file.size() >= MAX_FILE_SIZE)
    {
        fclose(pFile);
        pFile = NULL;
    }
}
