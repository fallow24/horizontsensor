#include "Bmp.h"

/*
 * dig = Binärisierung des Bildes
 * erod = erodiertes Bild
 */

Bmp::Bmp(const char* filename) { 
    this->filename = filename;
    f = fopen(filename, "rb");
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    width = *(int*)&info[18];
    height = *(int*)&info[22];
}

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
    int* dig = new int[width * height];

    printf("Converting grayscale to binary...");
    fflush(stdout);

    for(int i = 0; i < width * height; i++) gray[i] > THRESHOLD ? dig[i] = 1 : dig[i] = 0;   
    
    printf(" done!\n");
    fflush(stdout);

    return dig;
}

unsigned char Bmp::grayscale(unsigned char r, unsigned char g, unsigned char b) {
    unsigned char gray;
    
    //grayscale = 0,299 × red + 0,587 × green + 0,114 × blue
    gray = 0.299 * r + 0.587 * g + 0.114 * b;
        
    return gray;
}

int* Bmp::erodeBinaryPic(int* dig) {
    //erode pic
    int* erod = new int[width * height];

    //fill border with 0
    //top
    for(int i = 0; i < height; i++) dig[i] = 0;
    //bottom
    for(int i = 0; i < height; i++) dig[width * (height-1) + i] = 0;
    //left
    for(int i = 0; i < height; i++) dig[i*width] = 0;
    //right
    for(int i = 0; i < height; i++) dig[i*width-1] = 0;

    //iterate over picture with 3x3; a_ij is element in the middle
    for(int i = width + 1; i < width * (height - 1) - 2; i++) {
        int ones = 0;
        if(dig[i - width - 1] == 1) ones++;
        if(dig[i - width] == 1) ones++;
        if(dig[i - width + 1] == 1) ones++;
        if(dig[i - 1] == 1) ones++;
        if(dig[i] == 1) ones++;
        if(dig[i + 1] == 1) ones++;
        if(dig[i + width - 1] == 1) ones++;
        if(dig[i + width] == 1) ones++;
        if(dig[i + width + 1] == 1) ones++;

        ones <= m ? erod[i] = 0 : erod[i] = 1;      
    }

    return erod;
}

int* Bmp::buildEarthContour(int* dig, int* erod) {
    int* diff = new int[width * height];

    for(int i = 0; i < width * height; i++) diff[i] = dig[i] - erod[i];

    return diff;
}

void Bmp::writeToTxt(int* pic) {
    ofstream file;
    file.open("pic.txt");

    for(int i = 0; i < width * height; i++) {
        if(i != 0 && i % width == 0) file << endl;
        file << pic[i];
    }

    file.close();
}

int Bmp::getWidth() {
    return width;
}

int Bmp::getHeight() {
    return height;
}