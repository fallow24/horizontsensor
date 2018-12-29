#include <stdio.h>
#include "Bmp.h"

unsigned char* Bmp::readRGB() {
    printf("Read .bmp file... ");
    fflush(stdout);
    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);
    printf(" done!\n");
    fflush(stdout);

    return data; 
}

int* Bmp::grayscaleFromRGB(unsigned char* rgb) {//methode verkürzt und vereinfacht LG Nils ;)
    int* grayscaledImage = new int[width * height]; 
    
    printf("Converting .bmp file in grayscale...");
    fflush(stdout);
    unsigned char r, g, b;

    for(int i = 0; i < width * height; i++) grayscaledImage[i] = grayscale(rgb[3*i], rgb[3*i+1], rgb[3*i+2]);

    printf(" done!\n");
    fflush(stdout);
    
    return grayscaledImage;
}

int* Bmp::digitalize(int* gray) {//methode verkürzt und vereinfacht LG Nils ;)
    int* digitalImage = new int[width * height];

    printf("Converting grayscale to binary...");
    fflush(stdout);

    for(int i = 0; i < width * height; i++) gray[i] > THRESHOLD ? digitalImage[i] = 1 : digitalImage[i] = 0;   
    
    printf(" done!\n");
    fflush(stdout);

    return digitalImage;
}

unsigned char Bmp::grayscale(unsigned char r, unsigned char g, unsigned char b) 
{
    unsigned char gray;
    
    //grayscale = 0,299 × red + 0,587 × green + 0,114 × blue
    gray = 0.299 * r + 0.587 * g + 0.114 * b;
        
    return gray;
}

int Bmp::getWidth()
{
    return width;
}

int Bmp::getHeight()
{
    return height;
}