// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>
#include "Convolution.h"
#include "ImageMatrix.h"
#include "ImageLoader.h"

// Default constructor
EdgeDetector::EdgeDetector() {

}

// Destructor
EdgeDetector::~EdgeDetector() {

}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {

    std::vector<std::pair<int, int>> edgePixels;

    double** Gx = new double*[3];
    double** Gy = new double*[3];
    for (int i = 0; i < 3; ++i) {
        Gx[i] = new double[3];
        Gy[i] = new double[3];
    }

    Gx[0][0] = -1; Gx[0][1] = 0; Gx[0][2] = 1;
    Gx[1][0] = -2; Gx[1][1] = 0; Gx[1][2] = 2;
    Gx[2][0] = -1; Gx[2][1] = 0; Gx[2][2] = 1;

    Gy[0][0] = -1; Gy[0][1] = -2; Gy[0][2] = -1;
    Gy[1][0] = 0; Gy[1][1] = 0; Gy[1][2] = 0;
    Gy[2][0] = 1; Gy[2][1] = 2; Gy[2][2] = 1;

    Convolution convolution(Gx, 3, 3, 1, true);
    ImageMatrix Ix = convolution.convolve(input_image);

    convolution = Convolution(Gy, 3, 3, 1, true);
    ImageMatrix Iy = convolution.convolve(input_image);

    // Calculate the edge strength of each pixel and add it to a vector
    std::vector<double> gradientMagnitudes;
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            double magnitude = sqrt(Ix.get_data(i, j) * Ix.get_data(i, j) + Iy.get_data(i, j) * Iy.get_data(i, j));
            gradientMagnitudes.push_back(magnitude);
        }
    }

    // Calculate average of gradient sizes
    double sum = 0;
    for (double magnitude : gradientMagnitudes) {
        sum += magnitude;
    }
    double averageMagnitude = sum / gradientMagnitudes.size();

    // Set threshold value
    double threshold = averageMagnitude;

    // Find edge pixels using threshold value
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            double magnitude = sqrt(Ix.get_data(i, j) * Ix.get_data(i, j) + Iy.get_data(i, j) * Iy.get_data(i, j));

            if (magnitude > threshold) {
                edgePixels.push_back(std::make_pair(i, j));
            }
        }
    }

    // Release memory allocated for Gx and Gy
//    for (int i = 0; i < 3; ++i) {
//        delete[] Gx[i];
//        delete[] Gy[i];
//    }
//    delete[] Gx;
//    delete[] Gy;

    return edgePixels;
}


