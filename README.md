# Huffman Compression and Decompression Tool

This project demonstrates a simple implementation of Huffman coding for compressing and decompressing BMP images.

## Features

- **Compression**: Compresses BMP images by encoding their pixel data using Huffman coding, reducing file size.
- **Decompression**: Restores compressed BMP files back to their original state.

## How It Works

1. **Compression**:
   - Reads the pixel data from the BMP file.
   - Analyzes character frequency to construct a Huffman tree.
   - Encodes the pixel data using the Huffman codes.
   - Outputs an encoded BMP file and a separate file containing the Huffman codes.

2. **Decompression**:
   - Reads the encoded BMP file and the Huffman codes.
   - Decodes the pixel data using the Huffman tree.
   - Restores the original BMP image.

## Prerequisites

- A C++ compiler.
- BMP images as input files.

## Usage

### Compression

1. Place the input BMP file in the specified directory.
2. Compile and run `compression.cpp` to generate:
   - An encoded BMP file.
   - A Huffman codes file.

### Decompression

1. Use the generated encoded BMP file and Huffman codes.
2. Compile and run `decompression.cpp` to restore the original BMP image.

## Input and Output

- **Input**: BMP file (e.g., `image.bmp`).
- **Output**:
  - `encoded.bmp`: Compressed BMP file.
  - `Huffman_Code.bmp`: File storing the Huffman codes.
  - `Decompressed.bmp`: Restored BMP file.

## Files

- **compression.cpp**: Contains the implementation for compressing BMP files using Huffman coding.
- **decompression.cpp**: Contains the implementation for decompressing encoded BMP files.

## Implementation Details

- Constructs a Huffman tree based on character frequencies.
- Encodes each character as a unique binary string based on its position in the tree.
- Uses the encoded binary data to compress the BMP file.
- The decompression process reverses these steps to recreate the original BMP file.

## Limitations

- Only supports uncompressed BMP files.
- Requires the Huffman codes file to decode the compressed data.

## Future Improvements

- Extend support for other image formats.
- Optimize memory usage and speed.
- Add error handling for corrupted files.

