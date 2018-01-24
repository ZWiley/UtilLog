#include <QCoreApplication>
#include <QDebug>
#include "utillogshell.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LOG_RUN << "1hellow world!";

    LOG_RUN << "2hellow world!";

    LOG_RUN << "3hellow world!";

    return a.exec();
}
