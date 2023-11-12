#include "EncodeMessage.h"
#include "ImageMatrix.h"
#include <cmath>
#include <algorithm>
#include <bitset>
#include <iostream>


// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {
    
}


void EncodeMessage::applyCharacterTransformation(std::string &message) {
    for (size_t i = 0; i < message.length(); i++) {
        // Check if the index is a prime number
        if (isPrime(i)) {
            // Calculate the corresponding Fibonacci number
            int fibonacci = calculateFibonacci(i);

            // Adjust the ASCII value of the character
            int asciiValue = static_cast<int>(message[i]) + fibonacci;

            // Ensure the character is printable within ASCII range
            if (asciiValue <= 32) {
                asciiValue += 33;
            }
            else if (asciiValue >= 127) {
                asciiValue = 126;
            }

            // Update the character in the message
            message[i] = static_cast<char>(asciiValue);
        }
    }
}

void EncodeMessage::rightCircularShift(std::string &message) {
    int shift = message.length() / 2;

    std::rotate(message.rbegin(), message.rbegin() + shift, message.rend());

}

void EncodeMessage::embedBinaryMessage(ImageMatrix &img, const std::string &binaryMessage, const std::vector<std::pair<int, int>> &positions) {
    // Iterate over the edge pixel positions and binary message
    for (size_t i = 0; i < positions.size() && i < binaryMessage.length(); i++) {
        int row = positions[i].first;
        int col = positions[i].second;
        int pixelValue = img.get_data(row, col);


        int btoembed = binaryMessage[i] & 1;
        int newPixelValue = (pixelValue & 0xFFFFFFE) |   btoembed;

        // Update the pixel value
        img.set_data(row, col, newPixelValue);
    }
}

// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>> &positions) {
    // Make a copy of the input image
    ImageMatrix encodedImage = img;

    // Apply character transformation to the message
    std::string transformedMessage = message;
    applyCharacterTransformation(transformedMessage);

    // Apply right circular shift to the transformed message
    rightCircularShift(transformedMessage);

    std::cout << transformedMessage << std::endl;

    // Convert the transformed message to binary
    std::string binaryMessage = textToBinary(transformedMessage);

    // Embed the binary message into the image
    embedBinaryMessage(encodedImage, binaryMessage, positions);

    return encodedImage;
}

bool EncodeMessage::isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int EncodeMessage::calculateFibonacci(int n) {
    double goldenRatio = (1 + sqrt(5)) / 2;
    return static_cast<int>(round(pow(goldenRatio, n) / sqrt(5)));
}

std::string EncodeMessage::textToBinary(const std::string &text) {
    std::string binaryString;
    for (char c : text) {
        binaryString += std::bitset<7>(c).to_string();
    }
    std::cout << binaryString << std::endl;

    return binaryString;
}
