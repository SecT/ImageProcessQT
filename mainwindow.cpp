#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"

//#include "imageprocessing.h"
#include "myqimage.h"

#include "myqlabel.h"


#include <QSettings>

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

    loadSettings();
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

    QImage imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    imageFromLabel.save(filename);
}



void MainWindow::on_greyscaleButton_clicked()
{
    myQImage imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    imageFromLabel.convertToGreyscale();

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}


void MainWindow::on_IncreaseBrightnessButton_clicked()
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    int delta = 10;

    imageFromLabel.changeBrigthness(delta);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_decreaseBrightnessButton_clicked()
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    int delta = -10;

    imageFromLabel.changeBrigthness(delta);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}


void MainWindow::on_resetImageButton_clicked()
{
    ui->ImageLabel->setPixmap(QPixmap::fromImage(ImageBackup));

    ui->redChannelBox->setChecked(true);
    ui->greenChannelBox->setChecked(true);
    ui->blueChannelBox->setChecked(true);
}

void MainWindow::on_sharpenButton_clicked()
{
    myQImage  imageFromLabel(ui->ImageLabel->pixmap()->toImage());

    imageFromLabel.sharpen();

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_blurButton_clicked()



{
    myQImage imageFromLabel(ui->ImageLabel->pixmap()->toImage());

    imageFromLabel.blur();

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_invertColorsButton_clicked()
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    imageFromLabel.invertColors();

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_rotateRightButton_clicked()
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    imageFromLabel.rotate(90);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_rotateLeftButton_clicked()
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    imageFromLabel.rotate( -90);

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}


void MainWindow::on_redChannelBox_stateChanged(int state)
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    if(state == Qt::Unchecked)
    {
        imageFromLabel.filterOutColor(Qt::red);
    }

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_greenChannelBox_stateChanged(int state)
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    if(state == Qt::Unchecked)
    {
        imageFromLabel.filterOutColor(Qt::green);
    }

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::on_blueChannelBox_stateChanged(int state)
{
    myQImage imageFromLabel;
    imageFromLabel = ui->ImageLabel->pixmap()->toImage();

    if(state == Qt::Unchecked)
    {
        imageFromLabel.filterOutColor(Qt::blue);
    }

    ui->ImageLabel->setPixmap(QPixmap::fromImage(imageFromLabel));
}

void MainWindow::saveSettings()
{
    QSettings settings( QApplication::applicationDirPath()+"\\settings.ini",QSettings::IniFormat);

    if(!settings.contains("translationsPath"))
    {
        settings.setValue("translationsPath",QApplication::applicationDirPath());

    }
}

void MainWindow::loadSettings()
{
    QSettings settings( QApplication::applicationDirPath()+"\\settings.ini",QSettings::IniFormat);


    //if first time running program
    saveSettings();

    translationsDir = settings.value("translationsPath",QApplication::applicationDirPath()).toString();


}
