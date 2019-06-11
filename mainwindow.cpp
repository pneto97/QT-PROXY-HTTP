#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionproxy_triggered()
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::PROXY) );
}

void MainWindow::on_actionspider_triggered()
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::SPIDER));
}

void MainWindow::on_actiondump_triggered()
{
    ui->stackedWidget->setCurrentIndex(static_cast<int>(ScreenName::DUMP));
}
