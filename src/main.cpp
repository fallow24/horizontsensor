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
    Matrix p(2,2);
    p(0,0) = 1;
    p(0,1) = 2;
    p(1,0) = 3;
    p(1,1) = 4;
    p.printMatrix();

    Matrix a = m * p;

    a.printMatrix();
}