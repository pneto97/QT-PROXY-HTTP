#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QString>

class Proxy : public QObject
{
    Q_OBJECT
public:
    explicit Proxy(QObject *parent = nullptr);
    void doSetup(QThread &cThread);
    void stop();

private:
    bool stopFlag;

signals:
    void textReceived(QString );

public slots:
    void doWork();
};

#endif // PROXY_H
