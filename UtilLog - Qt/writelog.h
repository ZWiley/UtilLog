#ifndef WRITELOG_H
#define WRITELOG_H

#include <QString>
#include <QByteArray>

const int TYPERUN  = 0x0001;
const int TYPEERR  = 0x0002;
const int TYPEDBG  = 0x0003;
const int TYPEINFO = 0x0004;
const int TYPEWARN = 0X0005;
const qint64 MAX_FILE_SIZE = (1024*1024*5); // 5M

class CWriteLog
{
public:
   void Run(const QByteArray &buffer);
   void Info(const QByteArray &buffer);
   void Debug(const QByteArray &buffer);
   void Warn(const QByteArray &buffer);
   void Error(const QByteArray &buffer);
   void NetworkPackage(const QByteArray &buffer);

private:
   QString getFileName(int type);
   QString makeFileDate(const QString &filename);
   void write(const QString &filename, const QByteArray &buffer, int type);
   void write(const QString &filename, const QByteArray &buffer, FILE *&pFile);

private:
   QString m_fileName;
   FILE *m_pRunFile;
   FILE *m_pErrFile;
   FILE *m_pDebugFile;
   FILE *m_pInfoFile;
   FILE *m_pWarnFile;
};
#endif // WRITELOG_H
