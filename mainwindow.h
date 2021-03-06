#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QString>

#include "proxy.h"
#include "webtools.h"

namespace Ui {
class MainWindow;
}

//enum com as telas possíveis
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
    //emitido quando mandamos o request ou response da interface para a thread
    void sendRequestAndReply(QString, QString);
    
    //emitido quando manda url e profundidade da interface do spider ou dump para a thtrad
    void sendUrlAndDepth(QString, QString);

    void unlockSpider();

private slots:
    void on_actionproxy_triggered();

    void on_actionspider_triggered();

    void on_actiondump_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

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
    
    // troca de tela e inicia thread
    void setScreen(ScreenName screenName);

};

#endif // MAINWINDOW_H
