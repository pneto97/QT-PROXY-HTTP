#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "proxy.h"
#include "webtools.h"
#include <QDebug>
#include <QString>
#include "proxy.h"

namespace Ui {
class MainWindow;
}

enum class ScreenName{

    PROXY = 0,
    SPIDER = 1,
    DUMP =2
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendRequestAndReply(QString,QString);
    void unlockSpider();

private slots:
    void on_actionproxy_triggered();

    void on_actionspider_triggered();

    void on_actiondump_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void on_textReceived(QString );
    void on_requestReceived(QString);
    void on_requestSent();
    void on_replyReceived(QString);
    void on_replyRetrieved();
    void on_nodeSpider(QString);



private:
    Ui::MainWindow *ui;
    QThread proxyThread;
    Proxy proxy;
    QThread webtoolsThread;
    WebTools webtools;

    void setScreen(ScreenName screenName);

};

#endif // MAINWINDOW_H
