#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>//一个类 画界面
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
#include <QDebug>
#include "button.h"
#include "sceneone.h"

MainWindow::MainWindow(QWidget *parent) ://mainwindow的构造函数，只调用一次，不利于界面实时更新
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    button *startbutton = new button(":/stabtn.png");
    startbutton->setParent(this);
    startbutton->move(320,400);
    Sceneone *so = new Sceneone;
    connect(startbutton,&button::clicked,this,[=](){
        this->close();
        so->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)//每次打开mainwindow的时候都会运行这个函数
{
    QPainter painter(this);//this 是说在主窗口画的意思
    QPixmap background(":/firstpage.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),background);

}
