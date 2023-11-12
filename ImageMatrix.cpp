#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(){
    data = nullptr;
    height = 0;
    width = 0;
}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }
    // Initialize the data matrix with default values (e.g., 0.0)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = 0.0;
        }
    }
}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
    // Free the allocated memory
    if (data != nullptr){
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }
}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth){
    // Allocate memory for the matrix
    height = imgHeight;
    width = imgWidth;
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from inputMatrix to data
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other) {
    height = other.height;
    width = other.width;
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other) {
    if (this == &other) {
        return *this; // Self-assignment, no need to do anything
    }

    // Free the existing memory
    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }
    delete[] data;

    // Copy data from 'other' to 'data'
    height = other.height;
    width = other.width;

    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const {
    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const {
    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }

    return result;
}

void ImageMatrix::clip_pixel_values(double min_value, double max_value) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (data[i][j] < min_value) {
                data[i][j] = min_value;
            } else if (data[i][j] > max_value) {
                data[i][j] = max_value;
            }
        }
    }
}



// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    if (i >= 0 && i < height && j >= 0 && j < width) {
        return data[i][j];
    } else {
        return 0.0;
    }
}

// Setter method to set the data at the index (i, j)
void ImageMatrix::set_data(int i, int j, double value) {
    if (i >= 0 && i < height && j >= 0 && j < width) {
        data[i][j] = value;
    }
}

// Getter method for height
int ImageMatrix::get_height() const {
    return height;
}

// Getter method for width
int ImageMatrix::get_width() const {
    return width;
}

void ImageMatrix::printMatrix() const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}






