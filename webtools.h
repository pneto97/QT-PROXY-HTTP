#ifndef WEBTOOLS_H
#define WEBTOOLS_H

#include <QObject>
#include <QString>
#include <QThread>
#include <QDebug>

enum class Operation{
    SPIDER = 0,
    DUMP = 1
};


class WebTools : public QObject
{
    Q_OBJECT
public:
    explicit WebTools(QObject *parent = nullptr);
    void doSetup(QThread &cThread, Operation op);
    void stop();

private:
    bool stopFlag;


signals:

public slots:
    void runSpider();
    void runDump();
};

#endif // WEBTOOLS_H
