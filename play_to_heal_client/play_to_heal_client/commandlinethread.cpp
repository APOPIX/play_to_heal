#include "commandlinethread.h"
#include <QThread>
#include <QProcess>
#include <QString>

CommandLineThread::CommandLineThread(QString command)
{
    this->command = command;
}

void CommandLineThread::run(){
    QProcess process(this);
    process.start(this->command);
    process.waitForFinished();
    process.close();
}
