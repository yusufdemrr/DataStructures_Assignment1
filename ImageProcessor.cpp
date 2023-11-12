#include <iostream>
#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {
    // Create a matrix directly using direct initialization
    const double* bluredData[3] = {
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0},
            new double[3]{1.0/9.0, 1.0/9.0, 1.0/9.0}
    };

    ImageSharpening imageSharpening(3, 3, const_cast<double **>(bluredData));
    ImageMatrix sharpenedImage = imageSharpening.sharpen(img, 2);

    EdgeDetector detectedEdge;
    edgePixels = detectedEdge.detectEdges(sharpenedImage);
    DecodeMessage decodeMessage;

    std::string decodeMessageString = decodeMessage.decodeFromImage(sharpenedImage, edgePixels);

    return decodeMessageString;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message) {
    ImageSharpening imageSharpening;
    ImageMatrix sharpenedImage = imageSharpening.sharpen(img, 2);

    EdgeDetector detectedEdge;
    std::vector<std::pair<int, int>> edges = detectedEdge.detectEdges(sharpenedImage);

    EncodeMessage messageEncoder;
    ImageMatrix encodedImage = messageEncoder.encodeMessageToImage(img, message, edges);
    std::cout << encodedImage.get_width() << std::endl;
    return  encodedImage;
}
