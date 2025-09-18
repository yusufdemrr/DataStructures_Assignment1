# Image Steganography & Processing (C++)

Tiny C++ toolkit for grayscale image processing and LSB-based steganography.
Includes convolution, sharpening, Sobel edge detection, and encode/decode of hidden text.

## Features

* **Convolution** with custom kernel, stride, optional zero-padding
* **Sharpening** via unsharp mask: `I + k*(I − blur(I))`
* **Edge detection** using **Sobel** (Gx/Gy) and mean-magnitude threshold
* **Steganography**:

  * Character transform (prime index → add Fibonacci), right circular shift (len/2)
  * 7-bit ASCII to binary, **LSB** embed & recover

## Project Structure

```
Convolution.{h,cpp}     // 2D convolution with custom kernel
DecodeMessage.{h,cpp}   // Read LSBs from edge pixels and rebuild 7-bit text
EdgeDetector.{h,cpp}    // Sobel Gx/Gy + threshold → edge pixel coordinates
EncodeMessage.{h,cpp}   // Transform text → 7-bit → embed into LSBs
ImageLoader.{h,cpp}     // Load grayscale matrix from plain-text file
ImageMatrix.{h,cpp}     // Simple double** matrix, ops (+, -, * scalar)
ImageProcessor.{h,cpp}  // High-level encode/decode pipelines
ImageSharpening.{h,cpp} // Blur + unsharp sharpening
```

## Build

Requires a C++17 compiler (g++/clang).

```bash
# build
g++ -std=c++17 -O2 *.cpp -o stego

# run (example below writes/reads nothing, just demo flow)
./stego
```

## Input Format

`ImageLoader` expects a **plain-text** grayscale matrix:

* Each line = one row
* Values separated by spaces (e.g., `0 … 255` as doubles)

Example (3×3):

```
12 34 56
78 90 123
200 210 220
```

## Quick Start

Create a `main.cpp` like this (minimal demo of the API):

```cpp
#include <iostream>
#include "ImageMatrix.h"
#include "ImageProcessor.h"

int main() {
    // 1) Load grayscale image from a text file
    ImageMatrix img("input.txt"); // rows of numbers

    ImageProcessor p;

    // 2) Encode a hidden message
    std::string secret = "HELLO WORLD";
    ImageMatrix encoded = p.encodeHiddenMessage(img, secret);

    // (Optional) Print a few values to verify it changed
    std::cout << "Encoded image size: "
              << encoded.get_height() << "x" << encoded.get_width() << "\n";

    // 3) Decode it back (from the processed image)
    std::string recovered = p.decodeHiddenMessage(encoded);
    std::cout << "Recovered message: " << recovered << "\n";

    return 0;
}
```

Compile with `main.cpp` included:

```bash
g++ -std=c++17 -O2 main.cpp *.cpp -o stego && ./stego
```

## API at a Glance

* **ImageMatrix**

  * `ImageMatrix(path)` load from text file
  * `get_height()/get_width()`, `get_data(i,j)`, `set_data(i,j,val)`
  * Operators: `+`, `-`, `*(double)`; `clip_pixel_values(min,max)`
* **Convolution**

  * `convolve(ImageMatrix)` with provided `kernelHeight/Width`, `stride`, `padding`
* **ImageSharpening**

  * `sharpen(ImageMatrix, k)` → unsharp mask (blur by 3×3 average)
* **EdgeDetector**

  * `detectEdges(ImageMatrix)` → `std::vector<std::pair<int,int>>` of edge pixels
* **EncodeMessage**

  * Transform text → right rotate by `len/2` → 7-bit → embed into LSBs
* **DecodeMessage**

  * Read LSBs from positions → pad to 7-bit groups → ASCII recover
* **ImageProcessor**

  * `encodeHiddenMessage(img, message)` (high-level)
  * `decodeHiddenMessage(img)` (high-level)

## Algorithms (Short Notes)

* **Sobel**: `Gx/Gy` 3×3 kernels → gradient magnitude `sqrt(Ix^2 + Iy^2)` → threshold = mean magnitude.
* **Convolution**: optional zero-padding (bool), `stride=1` by default.
* **Sharpening**: `I_sharp = I + k*(I − blur(I))`, `blur(I)` by 3×3 average.
* **Steganography**: transform + rotate text → 7-bit binary → embed in LSBs of edge pixels.

## Known Limitations

* Grayscale only (single channel), text-matrix input only
* Mean threshold for edges is simple; may include noise or miss weak edges
* LSB hiding is fragile (lossy compression, heavy filtering, resaves may destroy bits)
