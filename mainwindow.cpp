#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

#include "imageprocessing.h"

#include "myqlabel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->ImageLabel, SIGNAL(Mouse_Pos()      ),  this,      SLOT(mouse_current_pos() ) );
    connect(ui->ImageLabel, SIGNAL(Mouse_Pressed()  ),  this,      SLOT(mouse_pressed() )     );
    connect(ui->ImageLabel, SIGNAL(Mouse_Left()  ),  this,         SLOT(mouse_left()     ));

    //Initial geometry for image
    BaseImagePosX = ui->ImageLabel->geometry().x();
    BaseImagePosY = ui->ImageLabel->geometry().y();
    BaseImageHeight = ui->ImageLabel->height();

    ui->horizontalSlider->setMaximum(ui->ImageLabel->height());
    ui->horizontalSlider->setValue(ui->ImageLabel->height());


    ImageBackup = ui->ImageLabel->pixmap()->toImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouse_current_pos()
{
//    ui->lineEdit_2->setText(QString("X: %1, Y: %2").arg(ui->ImageLabel->CurrentMouseX)
//                            .arg(ui->ImageLabel->CurrentMouseY));
}

void MainWindow::mouse_pressed()
{
    ui->lineEdit_2->setText(QString("X: %1, Y: %2").arg(ui->ImageLabel->ClickX)
                            .arg(ui->ImageLabel->ClickY));
}

void MainWindow::mouse_left()
{

}

void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText("Hello world!");
}

void MainWindow::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_horizontalSlider_valueChanged(int newSliderValue)
{

    //move the center of the label

    ui->ImageLabel->setGeometry(BaseImagePosX + (BaseImageHeight - newSliderValue) / 2,
                                BaseImagePosY + (BaseImageHeight - newSliderValue) / 2,
                                newSliderValue, newSliderValue);
    ui->ImageLabel->updateGeometry();

    //debug
    ui->lineEdit->setText(QString::number(ui->ImageLabel->geometry().x()) + " " + QString::number(ui->ImageLabel->height()) );

}



void MainWindow::on_openImageButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open image"),
                       "C://",
                       "All files (*.*);;Images(*.jpg *.gif *.png *.bmp)"
                                                   );

    if(filename.isEmpty())
        return;

    QImage newImage;
    newImage.load(filename);

    //create backup
    ImageBackup.load(filename);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(newImage));

    ui->statusBar->showMessage("Loaded image: " + filename);
}

void MainWindow::on_saveImageButton_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save image"), "C://");

    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    imageFromLabel.save(filename);
}



void MainWindow::on_greyscaleButton_clicked()
{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    convertToGreyscale(imageFromLabel);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}


void MainWindow::on_IncreaseBrightnessButton_clicked()
{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    int delta = 10;

    changeBrigthness(imageFromLabel, delta);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_decreaseBrightnessButton_clicked()
{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    int delta = -10;

    changeBrigthness(imageFromLabel, delta);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}


void MainWindow::on_resetImageButton_clicked()
{
    ui->ImageLabel->setPixmap(QPixmap::fromImage(ImageBackup));
}

void MainWindow::on_sharpenButton_clicked()
{
    QImage  imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    sharpen(imageFromLabel);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_blurButton_clicked()



{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    blur(imageFromLabel);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_invertColorsButton_clicked()
{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    invertColors(imageFromLabel);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_rotateRightButton_clicked()
{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    rotate(imageFromLabel, 90);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_rotateLeftButton_clicked()
{
    QImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    rotate(imageFromLabel, -90);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}
