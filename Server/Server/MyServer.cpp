/*#include "MyServer.h"

#include "SslServer.h"

#include <QCoreApplication>
#include <QHostAddress>
#include <QSslSocket>
#include <QThread>

ServerExample::ServerExample(QObject *parent) : QObject(parent)
{
}


void ServerExample::run()
{
    QHostAddress address = QHostAddress::Any;
    quint16 port = 22333;

    SslServer sslServer;
    sslServer.setSslLocalCertificate("sslserver.pem");
    sslServer.setSslPrivateKey("sslserver.key");
    sslServer.setSslProtocol(QSsl::TlsV1_2);

    if (sslServer.listen(address, port))
        qDebug().nospace() << "Now listening on " << qPrintable(address.toString()) << ":" << port;
    else
        qDebug().nospace() << "ERROR: could not bind to " << qPrintable(address.toString()) << ":" << port;

 while(1){
    if (sslServer.waitForNewConnection(-1))    // Wait until a new connection is received, -1 means no timeout
    {
        qDebug() << "New connection";
        QSslSocket *sslSocket = dynamic_cast<QSslSocket*>(sslServer.nextPendingConnection());

        if (sslSocket->waitForReadyRead(5000))    // Wait until some data is received, 5000 ms timeout (-1 doesn't work here)
        {
            QByteArray message = sslSocket->readAll();    // Read message
            qDebug() << "Message:" << QString(message);

            sslSocket->disconnectFromHost();    // Disconnect
            sslSocket->waitForDisconnected();    // Wait until disconnected
            qDebug() << "Disconnected";
        }

        else
        {
            qDebug().nospace() << "ERROR: could not receive message (" << qPrintable(sslSocket->errorString()) << ")";
        }
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslServer.errorString()) << ")";
    }
}
    this->deleteLater();
    QThread::currentThread()->quit();
    qApp->exit();
}*/


#include "MyServer.h"


MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt)
                                                    , m_nNextBlockSize(0)
{  // SslServer sslServer;
    m_ptcpServer = new  SslServer(this);
    m_ptcpServer->setSslLocalCertificate("sslserver.pem");
    m_ptcpServer->setSslPrivateKey("sslserver.key");
    m_ptcpServer->setSslProtocol(QSsl::TlsV1_2);


    if (!m_ptcpServer->listen(QHostAddress::Any, nPort)) {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + m_ptcpServer->errorString()
                             );
        m_ptcpServer->close();
        return;
    }connect(m_ptcpServer, SIGNAL(newConnection()),
             this,         SLOT(slotNewConnection())
            );


    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

/*virtual*/ void MyServer::slotNewConnection()
{
    //QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    QSslSocket* pClientSocket = dynamic_cast<QSslSocket*>(m_ptcpServer->nextPendingConnection());

    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
           );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
           );

    sendToClient(pClientSocket, "Server Response: Connected!");
}

void MyServer::slotReadClient()
{
   //  QTcpSocket* pClientSocket = (QTcpSocket*)sender();
   // QSslSocket *sslSocket = dynamic_cast<QSslSocket*>(m_ptcpServer.nextPendingConnection());
    QSslSocket* pClientSocket = (QSslSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;

        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QString str;

        in>>str;
        QString strMessage =
             "Client has sended - " + str;
                   m_ptxt->append(strMessage);

        m_nNextBlockSize = 0;

        sendToClient(pClientSocket,
                     "Server Response: Received \"" + str + "\""
                    );
    }
}

void MyServer::sendToClient(QSslSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
}
