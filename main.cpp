#include <QApplication>

#include "ServerWidget.h"
#include "ClientWidget.h"

#include <QNetworkInterface>
#include <QHostAddress>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //客户端作为接收端
    ClientWidget c_w;
    c_w.move(100, 100);
    c_w.show();

    ClientWidget c_w2;
    c_w2.move(100, 600);
    c_w2.show();

    //服务端作为发送端
    ServerWidget s_w;
    s_w.move(600, 100);
    s_w.show();




//    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
//    foreach (QNetworkInterface interface, interfaces) {
//        QList<QNetworkAddressEntry> addressEntries = interface.addressEntries();
//        foreach (QNetworkAddressEntry entry, addressEntries) {
//            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol && entry.ip() != QHostAddress::LocalHost) {
//                qDebug() << "IP Address:" << entry.ip().toString();
//            }
//        }
//    }

    return a.exec();
}
