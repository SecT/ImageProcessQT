#ifndef MYQLABEL_H
#define MYQLABEL_H


#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class myQLabel : public QLabel
{

Q_OBJECT
public:
    explicit myQLabel();
    explicit myQLabel(QWidget* parent = 0);
    ~myQLabel();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);



    int ClickX,ClickY;
    int CurrentMouseX,CurrentMouseY;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();

public slots:


};

#endif // MYQLABEL_H
