#ifndef COMMANDLINETHREAD_H
#define COMMANDLINETHREAD_H
#include <QThread>
#include <QString>

class CommandLineThread : public QThread
{
public:
    CommandLineThread(QString command);
    QString command;
    virtual void run();
};

#endif // COMMANDLINETHREAD_H
