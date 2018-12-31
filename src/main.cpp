#include "Bmp.h"
#include "Matrix.h"

Bmp file("Erde.bmp");

int width = file.getWidth(), heigth = file.getHeight(); //Width and heigth of the picture

int main()
{
    unsigned char* rgb_picture = file.readRGB();
    int* grayscale_picture = file.grayscaleFromRGB(rgb_picture);
    int* dig = file.digitalize(grayscale_picture);
    int* erod = file.erodeBinaryPic(dig);
    int* diff = file.buildEarthContour(dig, erod);
    file.writeToTxt(diff);
}