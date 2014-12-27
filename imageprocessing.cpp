#include "imageprocessing.h"
#include <QColor>

void convertToGreyscale(QImage& imageFromLabel)
{
    QColor oldColor;

    for(int x=0;x<imageFromLabel.width();x++)
        for (int y = 0; y < imageFromLabel.height(); ++y) {
            oldColor = QColor(imageFromLabel.pixel(x,y));
            int averageColor = (oldColor.red()+oldColor.green()+oldColor.blue())/3;
            imageFromLabel.setPixel(x,y,qRgb(averageColor,averageColor,averageColor));

        }
}

void invertColors(QImage &image)
{
    QColor oldColor;

    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            oldColor = QColor(image.pixel(x,y));

            image.setPixel(x,y,qRgb(255-oldColor.red(), 255- oldColor.green(), 255 - oldColor.blue()));
        }
    }

}

void changeBrigthness(QImage &imageFromLabel, int delta = 0)
{
    QColor oldColor;
    int r,g,b;

    for (int x = 0; x < imageFromLabel.width(); ++x) {
        for (int y = 0; y < imageFromLabel.height(); ++y) {

            oldColor = QColor(imageFromLabel.pixel(x,y));

            r = oldColor.red() + delta;
            g = oldColor.green() + delta;
            b = oldColor.blue() + delta;

            r = qBound(0,r,255);
            g = qBound(0,g,255);
            b = qBound(0,b,255);

            imageFromLabel.setPixel(x,y,qRgb(r,g,b));
        }
    }
}


int getSumOfMaskValues(int** mask,const int maskSize)
{
    int sum = 0;
    for (int i = 0; i < maskSize; ++i) {
        for (int j = 0; j < maskSize; ++j) {
            sum+=mask[i][j];
        }
    }
    return sum;
}

void applyMask(QImage &image, int** mask, int maskSize)
{


    int maskValueSum = getSumOfMaskValues(mask, maskSize);

    int r = 0, g = 0, b = 0;
    QColor color;


    for (int x = maskSize/2; x < image.width() - maskSize/2; ++x) {
        for (int y = maskSize/2; y < image.height() - maskSize/2; ++y) {

            r = 0;
            g = 0;
            b = 0;

            for (int i = -maskSize/2; i <= maskSize/2; ++i) {
                for (int j = -maskSize/2; j < maskSize/2; ++j) {
                    color = QColor(image.pixel(x+i,y+j));

                    r+=color.red()*mask[maskSize/2+i][maskSize/2+j];
                    g+=color.green()*mask[maskSize/2+i][maskSize/2+j];
                    b+=color.blue()*mask[maskSize/2+i][maskSize/2+j];
                }
            }

            r = qBound(0,r/maskValueSum,255);
            g = qBound(0,g/maskValueSum,255);
            b = qBound(0,b/maskValueSum,255);

            image.setPixel(x,y,qRgb(r,g,b));

        }
    }
}

void sharpen(QImage &image)
{

    const int maskSize = 3;

    //init mask
    int** mask = new int*[maskSize];
    for (int i = 0; i < maskSize; ++i) {
        mask[i] = new int[maskSize];
    }

    mask[0][0] = 0;
    mask[0][1] = -1;
    mask[0][2] = 0;

    mask[1][0] = -1;
    mask[1][1] = 5;
    mask[1][2] = -1;

    mask[2][0] = 0;
    mask[2][1] = -1;
    mask[2][2] = 0;
    //end init mask

    applyMask(image, mask,maskSize);

    delete[] mask;
}


void blur(QImage &image)
{
    const int maskSize = 5;


    //init mask
    int** mask = new int*[maskSize];
    for (int i = 0; i < maskSize; ++i) {
        mask[i] = new int[maskSize];
    }

    mask[0][0] = 0;
    mask[0][1] = 0;
    mask[0][2] = 1;
    mask[0][4] = 0;
    mask[0][5] = 0;

    mask[1][0] = 0;
    mask[1][1] = 1;
    mask[1][2] = 3;
    mask[0][4] = 1;
    mask[0][5] = 0;

    mask[2][0] = 1;
    mask[2][1] = 3;
    mask[2][2] = 7;
    mask[0][4] = 3;
    mask[0][5] = 1;

    mask[3][0] = 0;
    mask[3][1] = 1;
    mask[3][2] = 3;
    mask[3][4] = 1;
    mask[3][5] = 0;

    mask[4][0] = 0;
    mask[4][1] = 0;
    mask[4][2] = 1;
    mask[4][4] = 0;
    mask[4][5] = 0;
    //end init mask

    applyMask(image, mask, maskSize);

    delete[] mask;

}
