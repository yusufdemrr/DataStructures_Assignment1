#ifndef IMAGE_SHARPENING_H
#define IMAGE_SHARPENING_H

#include "ImageMatrix.h"
#include "Convolution.h"

class ImageSharpening {
    public:
        ImageSharpening(); // default constructor
        ImageSharpening(int kernelHeight, int kernelWidth, double** blurringKernel);
        ~ImageSharpening(); 

        ImageMatrix sharpen(const ImageMatrix& input_image, double k);  

    private:
    double** blurringKernel; // Kernel for blurring
    int kernelHeight; // Height of the kernel
    int kernelWidth; // Width of the kernel
};

#endif // IMAGE_SHARPENING_H



