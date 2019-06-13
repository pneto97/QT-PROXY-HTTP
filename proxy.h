#ifndef PROXY_H
#define PROXY_H

#include <QObject>
#include <QDebug>
#include <QThread>

class Proxy : public QObject
{
    Q_OBJECT
public:
    explicit Proxy(QObject *parent = nullptr);
    void doSetup(QThread &cThread);
    bool stop;

signals:

public slots:
    void doWork();
};

#endif // PROXY_H