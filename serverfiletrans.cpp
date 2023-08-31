#include "serverfiletrans.h"
#include <QFileDialog>

ServerFileTrans::ServerFileTrans(QString ip, quint16 port, QObject *parent)
    : QObject{parent}, m_ip(ip), m_port(port) {
    thread = new QThread(this);
//    operate = new ServerOperate();
    operate = new ServerOperate;
    operate->moveToThread(thread);
    connect(thread, &QThread::finished, operate, &ServerOperate::deleteLater);
    if(operate->isListening()) {
        emit dislisten();
    } else {
        emit listen(m_ip, m_port);
    }

    connect(this, &ServerFileTrans::listen, operate, &ServerOperate::doListen);
    connect(this, &ServerFileTrans::dislisten, operate, &ServerOperate::dislisten);

    //未完工
    //hash->url


    thread->start();
}


ServerFileTrans::~ServerFileTrans() {
    thread->quit();
    thread->wait();
}
