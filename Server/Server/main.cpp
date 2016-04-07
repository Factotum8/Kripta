/*#include "main.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread *thread = new QThread;
    ServerExample *serverExample = new ServerExample;

    serverExample->moveToThread(thread);
    QObject::connect(thread, SIGNAL(started()), serverExample, SLOT(run()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    return a.exec();
}*/
#include "main.h"
#include "MyServer.h"

int main(int argc, char** argv){

        QApplication app(argc, argv);
        MyServer     server(2323);

        server.show();



       return app.exec();

}
