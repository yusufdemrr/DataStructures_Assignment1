#include "ImageSharpening.h"
#include "Convolution.h"
#include "ImageMatrix.h"

// Default constructor
ImageSharpening::ImageSharpening() {
    // Initialize the blurring kernel as a 3x3 averaging kernel
    kernelHeight = 3;
    kernelWidth = 3;
    blurringKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        blurringKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            blurringKernel[i][j] = 1.0 / 9.0;
        }
    }
}

ImageSharpening::ImageSharpening(int kernelHeight, int kernelWidth, double** kernelData)
        : kernelHeight(kernelHeight), kernelWidth(kernelWidth) {
    // Allocate memory for blurringKernel
    blurringKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        blurringKernel[i] = new double[kernelWidth];
        for (int j = 0; j < kernelWidth; ++j) {
            blurringKernel[i][j] = kernelData[i][j];
        }
    }
}

ImageSharpening::~ImageSharpening(){
    // Free the memory used by blurringKernel if it's allocated
    if (blurringKernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] blurringKernel[i];
        }
        delete[] blurringKernel;
    }
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    // Create a convolution object with the blurring kernel
    Convolution convolution(blurringKernel, kernelHeight, kernelWidth, 1, true);

    // Calculate the blurred image by convolving the input with the blurring kernel
    ImageMatrix blurredImage = convolution.convolve(input_image);

    // Calculate the sharpened image using the provided algorithm
    ImageMatrix sharpenedImage = input_image + ((input_image - blurredImage) * k);

    // Clip pixel values to the [0, 255] range
    sharpenedImage.clip_pixel_values(0.0, 255.0);


    return sharpenedImage;
}
