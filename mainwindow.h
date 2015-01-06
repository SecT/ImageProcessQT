#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    unsigned int BaseImagePosX;
    unsigned int BaseImagePosY;
    unsigned int BaseImageHeight;

    QImage ImageBackup;



    ~MainWindow();

//    void convertToGreyscale(QColor oldColor, QImage imageFromLabel);


private slots:

    void mouse_current_pos();

    void mouse_pressed();
    void mouse_left();

    void on_pushButton_clicked();

    void on_clearButton_clicked();

    void on_actionExit_triggered();

    void on_horizontalSlider_valueChanged(int newSliderValue);

//    void on_spinBox_valueChanged(int arg1);

//    void on_spinBox_valueChanged(const QString &arg1);


    void on_openImageButton_clicked();

    void on_saveImageButton_clicked();

    void on_greyscaleButton_clicked();


    void on_IncreaseBrightnessButton_clicked();

    void on_decreaseBrightnessButton_clicked();

    void on_resetImageButton_clicked();

    void on_sharpenButton_clicked();

    void on_blurButton_clicked();

    void on_invertColorsButton_clicked();

    void on_rotateRightButton_clicked();

    void on_rotateLeftButton_clicked();

    //void on_redChannelButton_toggled(bool checked);

    void on_redChannelBox_stateChanged(int arg1);

    void on_greenChannelBox_stateChanged(int arg1);

    void on_blueChannelBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;

    QString translationsDir;

    void saveSettings();
    void loadSettings();

};



#endif // MAINWINDOW_H
