#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include "seat.h"
#include "tower.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow//主窗口类
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *event);//(event?)
    explicit MainWindow(QWidget *parent = 0);//构造函数？
    ~MainWindow();//析构函数

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
