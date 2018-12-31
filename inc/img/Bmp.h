#ifndef BMP_H
#define BMP_H

#include "stdio.h"
#include <iostream>
#include <fstream>
using namespace std;

/*
 * grayscale value from 0 to 255
 * a star gets recognized if grayscale > THRESHOLD
 */
#define THRESHOLD 5 //threshold for star recognizion
#define m 8 //limit for number of ones in 3x3 element

class Bmp
{
    private: 
        FILE* f;
        const char* filename;
        int width, height;
        unsigned char grayscale(unsigned char, unsigned char, unsigned char);

    public:
        Bmp(const char*);
        unsigned char* readRGB();
        int* grayscaleFromRGB(unsigned char*);
        int* digitalize(int*);
        int* erodeBinaryPic(int*);
        int* buildEarthContour(int*, int*);
        void writeToTxt(int*);
        int getWidth();
        int getHeight();

};

#endif