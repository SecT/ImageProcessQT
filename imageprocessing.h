#ifndef IMAGEPROCESSING
#define IMAGEPROCESSING

#include <QImage>

void convertToGreyscale(QImage &image);
void invertColors(QImage &image);
void changeBrigthness(QImage &image, int delta);
void sharpen(QImage &image);
void blur(QImage &image);
void rotate(QImage &image, int angle);
void filterOutColor(QImage &image, short color);

#endif // IMAGEPROCESSING

