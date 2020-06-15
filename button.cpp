#include "button.h"
#include <QPushButton>
#include <QPixmap>

button::button(QString pic):QPushButton(0)//传0？
{
    QPixmap btnpicture (pic);
    this->setFixedSize(btnpicture.width(),btnpicture.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(btnpicture);
    this->setIconSize(QSize(btnpicture.width(),btnpicture.height()));

}
