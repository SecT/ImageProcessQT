#ifndef MYQIMAGE_H
#define MYQIMAGE_H

#include <QImage>

class myQImage : public QImage
{
public:
    myQImage();
    myQImage(QImage image);
    ~myQImage();


    void convertToGreyscale();
    void invertColors();
    void changeBrigthness(int delta);
    void sharpen();
    void blur();
    void rotate(int angle);
    void filterOutColor(int color);

private:
    void applyMask(int** mask, int maskSize);

};

#endif // MYQIMAGE_H
