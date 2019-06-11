#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionproxy_triggered();

    void on_actionspider_triggered();

    void on_actiondump_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
