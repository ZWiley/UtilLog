#ifndef UTILLOGSHELL_H
#define UTILLOGSHELL_H
//#if defined(UTILLOGSHELL_LIBRARY)
//#  define UTILLOGSHELLSHARED_EXPORT Q_DECL_EXPORT
//#else
//#  define UTILLOGSHELLSHARED_EXPORT Q_DECL_IMPORT
//#endif

#include <string>
#include <QObject>

/*
 1、windows：   请在当前工作目录上一层新建log文件夹，程序生成的日志文件均在此目录下面。
 2、linux/unix：请在$HOME目录下新建$HOME/var/log/文件夹，程序生成的日志文件均在此目录下面。
 */
class CUtilLogShell : public QObject
{
    Q_OBJECT
public:
    typedef enum Log_Level
    {
        RUN=1, ERROR, DEBUG, INFO, WARN, NETPACKAGE
    } LOG_LEVEL;

    CUtilLogShell(LOG_LEVEL level, const char *file, int lineNo);
   ~CUtilLogShell();

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
        CFormatLog& operator<<(const QByteArray *p);
        CFormatLog& operator<<(const QByteArray &p);
        CFormatLog& operator<<(const std::string &str);
        CFormatLog& operator<<(const QString &qstr);

    public:
        QByteArray getLogInfo(){return m_buffer;}

    private:
        void print();
        static QByteArray Unicode2GBK(QByteArray buffer);

    private:
        QByteArray m_buffer;
        LOG_LEVEL  m_level;
    };

signals:
    void SendLogInfo(int logLevel, QByteArray logInfo);

public:
    CFormatLog& formatLog();

private:
    CFormatLog *m_formatLog;
    char                m_fileName[256];
    int                   m_lineNo;
    int                   m_logLevel;
};

#define LOG_RUN        CUtilLogShell(CUtilLogShell::RUN,        __FILE__, __LINE__).formatLog()
#define LOG_DEBUG      CUtilLogShell(CUtilLogShell::DEBUG,      __FILE__, __LINE__).formatLog()
#define LOG_WARN       CUtilLogShell(CUtilLogShell::WARN,       __FILE__, __LINE__).formatLog()
#define LOG_ERROR      CUtilLogShell(CUtilLogShell::ERROR,      __FILE__, __LINE__).formatLog()
#define LOG_INFO       CUtilLogShell(CUtilLogShell::INFO,       __FILE__, __LINE__).formatLog()
#define LOG_NETPACKAGE CUtilLogShell(CUtilLogShell::NETPACKAGE, __FILE__, __LINE__).formatLog()

#endif // UTILLOGSHELL_H
