
/*#include "ClientExample.h"

#include <QCoreApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread *thread = new QThread;
    ClientExample *clientExample = new ClientExample;

    clientExample->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), clientExample, SLOT(run()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    return a.exec();
}*/

#include "main.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);


    MyClient   client("localhost", 2323);

    client.show();

    return app.exec();
}
