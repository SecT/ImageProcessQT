#include "myqlabel.h"

myQLabel::myQLabel()
{

}

myQLabel::myQLabel(QWidget *parent):QLabel(parent)
{

}

myQLabel::~myQLabel()
{

}

void myQLabel::mouseMoveEvent(QMouseEvent *ev)
{

    this->CurrentMouseX = ev->x();
    this->CurrentMouseY = ev->y();
    emit Mouse_Pos();
}

void myQLabel::mousePressEvent(QMouseEvent *ev)
{
    this->ClickX = ev->x();
    this->ClickY = ev->y();
    emit Mouse_Pressed();
}

void myQLabel::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}

