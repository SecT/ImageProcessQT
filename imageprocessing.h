#ifndef IMAGEPROCESSING
#define IMAGEPROCESSING

#include <QImage>

void convertToGreyscale(QImage &image);
void invertColors(QImage &image);
void changeBrigthness(QImage &image, int delta);
void sharpen(QImage &image);
void blur(QImage &image);

#endif // IMAGEPROCESSING

