#include "Bmp.h"
#include "Matrix.h"

Bmp file("Erde.bmp");

int width = file.getWidth(), heigth = file.getHeight(); //Width and heigth of the picture

int main()
{
    unsigned char* rgb_picture = file.readRGB();
    int* grayscale_picture = file.grayscaleFromRGB(rgb_picture);

    Matrix m(2,2);
    m(1,1) = 2;
    m(0,1) = 4;
    m.printMatrix();
    Matrix p(3,2);
    p.printMatrix();

    Matrix a = m + p;

    a.printMatrix();
}