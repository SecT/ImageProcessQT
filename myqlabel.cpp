#include "myqlabel.h"

myQLabel::myQLabel()
{
    isFirstClick = false;
}

myQLabel::myQLabel(QWidget *parent):QLabel(parent)
{
    isFirstClick = false;
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



    if(!isFirstClick){
        this->ClickX = ev->x();
        this->ClickY = ev->y();
    }
    else
    {
        this->ClickX_2 = ev->x();
        this->ClickY_2 = ev->y();
    }

    isFirstClick = !isFirstClick;
    emit Mouse_Pressed();
}

void myQLabel::leaveEvent(QEvent *)
{
    emit Mouse_Left();
}

