#include "utillogshell.h"
#include "recvloginfo.h"
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QTextCodec>

QThread *g_pThread = new QThread;

CUtilLogShell::CUtilLogShell(LOG_LEVEL level, const char *file, int lineNo)
{
    m_logLevel = (int)level;
    memset(m_fileName, 0x0, 256);
    const char *pos = NULL;
#ifdef Q_OS_WIN
    pos = strrchr(file, '\\');
#else
    pos = strrchr(file, '/');
#endif
    strcpy(m_fileName, pos+1);
    qDebug() << "m_fileName: " << m_fileName;
    m_lineNo = lineNo;
    m_formatLog = new CFormatLog(level);
    connect(this, SIGNAL(SendLogInfo(int, QByteArray)),
                    CRecvLogInfo::instance(), SLOT(RecvLogInfo(int, QByteArray)));

    CRecvLogInfo::instance()->moveToThread(g_pThread);
    g_pThread->start();
}

CUtilLogShell::CFormatLog& CUtilLogShell::formatLog()
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    (*m_formatLog) << "[<" << dateTime.toLatin1().data() << m_fileName << "line:" << m_lineNo << ">]";

    return (*m_formatLog);
}

CUtilLogShell::~CUtilLogShell()
{
    if (m_formatLog)
    {
        emit SendLogInfo(m_logLevel, m_formatLog->getLogInfo());
        delete m_formatLog;
        m_formatLog = NULL;
    }

    disconnect(this, SIGNAL(SendLogInfo(int, QByteArray)),
               CRecvLogInfo::instance(), SLOT(RecvLogInfo(int, QByteArray)));
}

CUtilLogShell::CFormatLog::CFormatLog(LOG_LEVEL level)
{
    m_buffer.clear();
    m_level = level;
}

CUtilLogShell::CFormatLog::~CFormatLog()
{
   // this->print();
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(bool b)
{
    QString str = ((b) ? "(true)" : "(false)");
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(char c)
{
    QString str = "";
    str.append(QChar(c));
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(signed short ss)
{
    QString str = QString::number(ss);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(unsigned short us)
{
    QString str = QString::number(us);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(int i)
{
    QString str = QString::number(i);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(unsigned int ui)
{
    QString str = QString::number(ui);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(signed long sl)
{
    QString str = QString::number(sl);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(unsigned long ul)
{
    QString str = QString::number(ul);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(long long ll)
{
    QString str = QString::number(ll);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(unsigned long long ull)
{
    QString str = QString::number(ull);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(float f)
{
    QString str = QString::number(f);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(double d)
{
    QString str = QString::number(d);
    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.length());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(const char *p)
{
    QByteArray str = ((NULL != p) ? p : "(NULL)");
    if (str == ">]") m_buffer.remove(m_buffer.size()-1, 1);
    if (str != "[<") str.append(" ");
    QByteArray tmpStr = Unicode2GBK(str);
    m_buffer.append(tmpStr.data(), tmpStr.size());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(const void *p)
{
    QString str = "";
    if (p)
    {
        int size = sizeof(const void *);
        char *pointer = new char[size + 1];
        memset(pointer, 0x0, size + 1);
        memcpy(pointer, (char*)&p, size);
        QString temp = "";
        str = "0x";
        for (int i=size-1; i>=0; i--)
        {
            temp.sprintf("%02X", (quint8)pointer[i]);
            str.append(temp);
        }
        delete []  pointer;
    }
    else
    {
        str = "(NULL)";
    }

    str.append(" ");
    m_buffer.append(str.toLatin1().data(), str.size());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(const QByteArray *p)
{
    QString str = "";
    if (p)
    {
        int size = p->size();
        QString temp = "";
        str = "Network package => ";
        for (int i=0; i<size; i++)
        {
            temp.sprintf("%02X ", (quint8)p->at(i));
            str.append(temp);
        }
    }
    else
    {
        str = "(NULL) ";
    }

    m_buffer.append(str.toLatin1().data(), str.size());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(const QByteArray &p)
{
    QByteArray str = ((!p.isEmpty()) ? p : "(NULL)");
    QByteArray tmpStr = Unicode2GBK(str);
    tmpStr.append(" ");
    m_buffer.append(tmpStr);
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(const std::string &str)
{
    std::string tmp = ((!str.empty()) ?  str : "(NULL)");
    tmp += " ";
    QByteArray tmpStr = QByteArray(tmp.c_str());
    m_buffer.append(tmpStr.data(), tmpStr.size());
    return *this;
}

CUtilLogShell::CFormatLog& CUtilLogShell::CFormatLog::operator<<(const QString &qstr)
{
    QString tmp = ((!qstr.isEmpty()) ? qstr : "(NULL)");
    tmp += " ";
    QByteArray tmpStr = tmp.toStdString().c_str();
    m_buffer.append(tmpStr.data(), tmpStr.size());
    return *this;
}

void CUtilLogShell::CFormatLog::print()
{
    int pos = m_buffer.indexOf("]");
    QByteArray temp = m_buffer.mid(pos+2, m_buffer.size());
    qDebug() << Unicode2GBK(temp).data();
}

QByteArray CUtilLogShell::CFormatLog::Unicode2GBK(QByteArray buffer)
{
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));

    return QTextCodec::codecForName("GB2312")->fromUnicode(QString(buffer));
}
