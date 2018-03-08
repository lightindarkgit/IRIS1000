#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

#include "writeobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
signals:
    void haveClicked(QString);

private slots:
    void on_PB_start_clicked();

private:
    Ui::MainWindow *ui;

    int k;
    QThread myThread;

    WriteObject *writeStringObj;
};

#endif // MAINWINDOW_H
