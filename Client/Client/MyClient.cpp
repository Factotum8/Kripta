/*#include "ClientExample.h"
#include <iostream>
#include <QCoreApplication>
#include <QString>
#include <QSslSocket>
#include <QThread>

using namespace std;
ClientExample::ClientExample(QObject *parent) : QObject(parent)
{
}


void ClientExample::run()
{
    QString hostName = "127.0.0.1";    // DO NOT CHANGE THIS AS IT MUST MATCH THE FQDN OF THE CERTIFICATE (you MUST create your own certificate in order to change this)
    quint16 port = 22333;

    QSslSocket sslSocket;
    sslSocket.addCaCertificates("sslserver.pem");
    sslSocket.connectToHostEncrypted(hostName, port);

    if (sslSocket.waitForEncrypted(-1))    // Wait until encrypted connection is established, -1 means no timeout
    {
        qDebug() << "Connected";
    char sennd [1024];
    cin>>sennd;
    sslSocket.write(sennd);
        //    sslSocket.write("Hello, World!Ira");    // Send message to the server

        if (sslSocket.waitForBytesWritten(-1))    // Wait until message is sent (also makes QSslSocket flush the buffer)
            qDebug() << "Message sent";
        else
            qDebug().nospace() << "ERROR: could not send message (" << qPrintable(sslSocket.errorString()) << ")";

        while (!sslSocket.waitForDisconnected())    // Wait until disconnected
            QThread::msleep(10);

        qDebug() << "Disconnected";
    }

    else
    {
        qDebug().nospace() << "ERROR: could not establish encrypted connection (" << qPrintable(sslSocket.errorString()) << ")";
    }

    this->deleteLater();
    QThread::currentThread()->quit();
    qApp->exit();
}
*/

#include "MyClient.h"
#include <iostream>

using namespace std;

MyClient::MyClient(const QString& strHost,
                   int            nPort,
                   QWidget*       pwgt /*=0*/
                  ) : QWidget(pwgt)
                    , m_nNextBlockSize(0)
{    QString hostName = "127.0.0.1";

   // m_pTcpSocket = new QTcpSocket(this);
     m_pTcpSocket = new QSslSocket (this);

 //   m_pTcpSocket->connectToHost(strHost, nPort);
     m_pTcpSocket->addCaCertificates("sslserver.pem");
     m_pTcpSocket->connectToHostEncrypted(hostName, nPort);
    cout<<"2\n";
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
           );
    cout<<"\n3\n";
    m_ptxtInfo  = new QTextEdit;
    m_ptxtInput = new QLineEdit;

    connect(m_ptxtInput, SIGNAL(returnPressed()),
            this,        SLOT(slotSendToServer())
           );
    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}

void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_2);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QString str;
        in>>str;
        m_ptxtInfo->append(" " + str);
        m_nNextBlockSize = 0;
    }
}

void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(m_pTcpSocket->errorString())
                    );
    m_ptxtInfo->append(strError);
}


void MyClient::slotSendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);

     //   out << quint16(0) << QTime::currentTime() << m_ptxtInput->text();

    out << quint16(0) << m_ptxtInput->text();
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    m_ptxtInput->setText("");
}

void MyClient::slotConnected()
{
    m_ptxtInfo->append("Received the connected() signal");
}

