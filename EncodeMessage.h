#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();

    ImageMatrix encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions);


private:
    // Helper function to apply character transformation
    void applyCharacterTransformation(std::string &message);

    // Helper function for right circular shifting
    void rightCircularShift(std::string &message);

    // Helper function to embed binary message into image
    void embedBinaryMessage(ImageMatrix &img, const std::string &binaryMessage, const std::vector<std::pair<int, int>> &positions);

    bool isPrime(int n);

    int calculateFibonacci(int n);

    std::string textToBinary(const std::string &text);
};

#endif // ENCODE_MESSAGE_H
