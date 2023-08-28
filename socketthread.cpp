#include "socketthread.h"

#include <QTcpSocket>

SocketThread::SocketThread(int socketDescriptor, QObject *parent)
    : QThread{parent}, socketDescriptor(socketDescriptor) {

}

void SocketThread::run() {
    QTcpSocket socket;
    if (socket.setSocketDescriptor(socketDescriptor)) {
        // 套接字描述符成功设置，可以进行读取、写入和其他操作
        qDebug() << "Socket descriptor set successfully in thread:" << QThread::currentThread();

        // 在这里可以继续使用 socket 对象进行通信操作
        // 例如，使用 socket.read() 或 socket.write() 等函数进行数据的读取和写入
    } else {
        // 套接字描述符设置失败
        qDebug() << "Failed to set socket descriptor in thread:"
                 << QThread::currentThread() << ":" << socket.errorString();
    }
}
