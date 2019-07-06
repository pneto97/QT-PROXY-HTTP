#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setScreen(ScreenName::PROXY);

    //interface mostra o request quando o proxy manda
    connect(&proxy, SIGNAL(requestReceived(QString)),this, SLOT(on_requestReceived(QString)), Qt::QueuedConnection);

    //conecta botao à acão do proxy
    connect(this, SIGNAL(sendRequestAndReply(QString,QString)), &proxy, SLOT(on_buttonPressed(QString,QString)), Qt::QueuedConnection);

    //conecta botao a acão do spider/dump

    connect(this, SIGNAL(sendUrlAndDepth(QString,QString)), &webtools, SLOT(on_buttonPressed(QString,QString)), Qt::QueuedConnection);

    //interface do Spider mostra os nós da árvore
    connect(&webtools, SIGNAL(nodeSpider(QString)), this, SLOT(on_nodeSpider(QString)), Qt::QueuedConnection);

    //ao enviar o request, desabilita o botao e a edicao do request
    connect(&proxy, SIGNAL(requestSent()),this, SLOT(on_requestSent()), Qt::QueuedConnection);

    //interface mostra o reply e habilita o botao
     connect(&proxy, SIGNAL(replyReceived(QString)),this, SLOT(on_replyReceived(QString)), Qt::QueuedConnection);

     //ao enviar o reply para o client, inicia novamente
     connect(&proxy, SIGNAL(replyRetrieved()),this, SLOT(on_replyRetrieved()), Qt::QueuedConnection);




}

MainWindow::~MainWindow()
{
    delete ui;
}

//methods

void MainWindow::setScreen(ScreenName screenName){

    //para a thread do proxy
    proxy.stop();
    if(proxyThread.isRunning()){
        proxyThread.terminate();
  //      proxy.close_sockets();
    }

    //para a thread do proxy ou spider
    webtools.stop();

    switch(screenName){
        
        //se for a do proxy, apaga o texto e configura a thread
        case ScreenName::PROXY:
           qDebug() << "Proxy";

           ui->plainTextEdit->setPlainText("");
           ui->plainTextEdit_2->setPlainText("");

            proxy.doSetup(proxyThread);
            proxy.moveToThread(&proxyThread);
            proxyThread.start();
            break;

        case ScreenName::SPIDER:
            qDebug() << "Spider";

            if(webtoolsThread.isRunning())
                webtoolsThread.wait();

            ui->plainTextEdit_3->setPlainText("");
            webtools.doSetup(webtoolsThread, Operation::SPIDER);
            webtools.moveToThread(&webtoolsThread);
            //webtoolsThread.start();
            break;

        case ScreenName::DUMP:
            qDebug() << "DUMP";

            if(webtoolsThread.isRunning())
                webtoolsThread.wait();

            webtools.doSetup(webtoolsThread, Operation::DUMP);
            webtools.moveToThread(&webtoolsThread);
            //webtoolsThread.start();
            break;
    }


    ui->stackedWidget->setCurrentIndex( static_cast<int>(screenName) );


}

//slots

void MainWindow::on_actionproxy_triggered()
{
   setScreen(ScreenName::PROXY);
}

void MainWindow::on_actionspider_triggered()
{
    setScreen(ScreenName::SPIDER);
}

void MainWindow::on_actiondump_triggered()
{
    setScreen(ScreenName::DUMP);
}

void MainWindow::on_textReceived(QString txt){
    ui->plainTextEdit->document()->setPlainText(txt);
    ui->pushButton->setDisabled(false);

}

//quando proxy recebe o request
void MainWindow::on_requestReceived(QString req){
    ui->plainTextEdit->document()->setPlainText(req);
    ui->pushButton->setText("Send request");

    ui->pushButton->setDisabled(false);
    ui->plainTextEdit_2->setDisabled(true);
    ui->plainTextEdit->setDisabled(false);

}

//quando o proxy manda o request
void MainWindow::on_requestSent(){
    ui->plainTextEdit->setDisabled(true);
}

//quando proxy recebe a resposta
void MainWindow::on_replyReceived(QString reply){

    ui->plainTextEdit_2->document()->setPlainText(reply);
    ui->plainTextEdit_2->setDisabled(false);
    ui->plainTextEdit->setDisabled(true);


    ui->pushButton->setText("Retrieve reply");
    ui->pushButton->setDisabled(false);
}

//quando a resposta é mandada do proxy para o browser
void MainWindow::on_replyRetrieved(){
    ui->plainTextEdit->setDisabled(true);
    ui->plainTextEdit_2->setDisabled(true);
    ui->pushButton->setDisabled(true);
}


void MainWindow::on_nodeSpider(QString node){
    ui->plainTextEdit_3->appendPlainText(node);
}


void MainWindow::on_pushButton_clicked()
{
    //qDebug() << "clicou";
    emit sendRequestAndReply(ui->plainTextEdit->toPlainText(), ui->plainTextEdit_2->toPlainText() );
    ui->pushButton->setDisabled(true);
    //emit sendRequest("TESTE");
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "clicouSpider";
    ui->plainTextEdit_3->setPlainText("");

    webtoolsThread.start();
    emit sendUrlAndDepth(ui->textEdit->toPlainText(), ui->textEdit_3->toPlainText());
    //qDebug() << ui->textEdit->toPlainText();
    //qDebug() << ui->textEdit_3->toPlainText();

}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << "clicouDump";
    webtoolsThread.start();
    emit sendUrlAndDepth(ui->textEdit_2->toPlainText(), ui->textEdit_4->toPlainText());
}
