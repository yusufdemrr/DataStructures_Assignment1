// DecodeMessage.cpp

#include "DecodeMessage.h"

// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}


std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {

    std::string binaryString;

    // Remove LSB from edgePixels
    for (const auto& pixel : edgePixels) {
        double pixelValue = image.get_data(pixel.first, pixel.second);
        int lsb = static_cast<int>(pixelValue) & 1;
        binaryString += std::to_string(lsb);
    }

    // Convert binary string to 7-bit groups
    while (binaryString.length() % 7 != 0) {
        binaryString = "0" + binaryString;
    }

    // Convert 7-bit groups to ASCII characters
    std::string decodedMessage;
    for (size_t i = 0; i < binaryString.length(); i += 7) {
        std::string binaryChar = binaryString.substr(i, 7);
        int decimalValue = 0;

        // Convert 7-bit binary value to decimal value
        for (int j = 0; j < 7; j++) {
            decimalValue = (decimalValue << 1) | (binaryChar[j] - '0');
        }

        // Create ASCII characters and add them to the message
        if (decimalValue <= 32) {
            decimalValue += 33;
        }
        else if (decimalValue == 127) {
            decimalValue = 126;
        }

        decodedMessage += static_cast<char>(decimalValue);
    }

    return decodedMessage;
}

