#ifndef RECVLOGINFO_H
#define RECVLOGINFO_H

#include <QObject>

class CRecvLogInfo : public QObject
{
    Q_OBJECT
public:
    explicit CRecvLogInfo(QObject *parent = 0);
    static CRecvLogInfo* instance(){return &m_instance;}

    typedef enum Log_Level
    {
        RUN=1, ERROR, DEBUG, INFO, WARN, NETPACKAGE
    } LOG_LEVEL;

private slots:
    void RecvLogInfo(int logLevel, QByteArray logInfo);

private:
    static void write(int logLevel, const QByteArray &buffer);

private:
    static CRecvLogInfo m_instance;
};

#endif // RECVLOGINFO_H
