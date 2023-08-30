#include "clientfiletrans.h"

#include <QFileDialog>


ClientFileTrans::ClientFileTrans(QString ip, quint16 port, QObject *parent)
    : QObject{parent}, m_ip(ip), m_port(port) {
    thread = new QThread(this);
    operate = new ClientOperate;
    operate->moveToThread(thread);
    connect(thread, &QThread::finished, operate, &ClientOperate::deleteLater);
    // 信号槽安全传递
    if(operate->isConnected()) {
        emit disconnectTcp();
    } else {
        emit connectTcp(m_ip, m_port);
    }

    connect(this, &ClientFileTrans::connectTcp, operate, &ClientOperate::connectTcp);
    connect(this, &ClientFileTrans::disconnectTcp, operate, &ClientOperate::disconnectTcp);

    // 获取 progressValue
    connect(operate, &ClientOperate::progressChanged, this, [this](int value) {
        progressValue = value;
    });

    // 还有什么加的?

    thread->start();
}

ClientFileTrans::~ClientFileTrans() {
    thread->quit();
    thread->wait();
}


void ClientFileTrans::startTrans(const QString &fileHash, const QString &savePath) {

    operate->setFilePath(fileHash);
    operate->setSavePath(savePath);
    operate->startFileTransfer();
}

void ClientFileTrans::cancelTrans() {
    operate->cancelFileTransfer();
}

int ClientFileTrans::getProgressValue() const {
    return progressValue;
}
