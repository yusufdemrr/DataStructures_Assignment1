#include "ImageMatrix.h"
#include "Convolution.h"

// Default constructor 
Convolution::Convolution() : customKernel(nullptr), kernelHeight(0), kernelWidth(0), stride(1), padding(false) {
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad)
        :  kernelHeight(kh), kernelWidth(kw), stride(stride_val), padding(pad) {
    this->customKernel = new double *[kh];
    for (int i = 0; i < kh; i++) {
        this->customKernel[i] = new double[kw];
    }

    for (int i = 0; i < kh; i++) {
        for (int j = 0; j < kw; j++) {
            this->customKernel[i][j] = customKernel[i][j];
        }
    }
}

// Destructor
Convolution::~Convolution() {
    // Free the memory used by customKernel if it's allocated
    if (customKernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }
}

// Copy constructor
Convolution::Convolution(const Convolution &other)
        : kernelHeight(other.kernelHeight), kernelWidth(other.kernelWidth), stride(other.stride), padding(other.padding) {

    // Allocate memory for customKernel and copy the data
    customKernel = new double *[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        customKernel[i] = new double[kernelWidth];
    }

    for (int i = 0; i < kernelHeight; ++i) {
        for (int j = 0; j < kernelWidth; ++j) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }
}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {
    if (this == &other) {
        return *this; // Self-assignment, no need to do anything
    }

    // Free the memory used by customKernel if it's allocated
    if (customKernel != nullptr) {
        for (int i = 0; i < kernelHeight; ++i) {
            delete[] customKernel[i];
        }
        delete[] customKernel;
    }

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    padding = other.padding;

    // Allocate memory for customKernel and copy the data
    customKernel = new double*[kernelHeight];
    for (int i = 0; i < kernelHeight; ++i) {
        customKernel[i] = new double[kernelWidth];
    }

    for (int i = 0; i < kernelHeight; ++i) {
        for (int j = 0; j < kernelWidth; ++j) {
            customKernel[i][j] = other.customKernel[i][j];
        }
    }

    return *this;
}


// Convolve Function: Responsible for convolving the input image with a kernel and return the convolved image.
ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();

    // Calculate the output dimensions based on the convolution parameters
    int outputHeight = (inputHeight - kernelHeight + 2 * (padding ? 1 : 0)) / stride + 1;
    int outputWidth = (inputWidth - kernelWidth + 2 * (padding ? 1 : 0)) / stride + 1;


    // Create a new ImageMatrix object for the convolved image
    ImageMatrix convolvedImage(outputHeight, outputWidth);

    // Iterate over the input image with stride and apply the convolution operation
    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            double sum = 0.0;
            for (int ki = 0; ki < kernelHeight; ki++) {
                for (int kj = 0; kj < kernelWidth; kj++) {
                    int rowIndex = i * stride + ki - (padding ? 1 : 0);
                    int colIndex = j * stride + kj - (padding ? 1 : 0);
                    if (rowIndex >= 0 && rowIndex < inputHeight && colIndex >= 0 && colIndex < inputWidth) {
                        double inputValue = input_image.get_data(rowIndex, colIndex);
                        sum += inputValue * customKernel[ki][kj];
                    }
                }
            }
            convolvedImage.set_data(i, j, sum);
        }
    }

    return convolvedImage;
}