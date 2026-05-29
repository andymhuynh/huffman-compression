# Huffman Coding Compressor

A C++ implementation of Huffman Coding for lossless text compression and decompression.

## Overview

This project implements a Huffman Coding compressor in C++. It builds a frequency table from text input, constructs a Huffman tree, generates variable-length binary codes, and uses those codes to compress and decompress text files.

## Features

- Builds character frequency tables from text files
- Constructs a Huffman tree for variable-length encoding
- Generates binary codes for each character
- Compresses text using Huffman encoding
- Decompresses encoded files back into original text
- Includes sample text files for testing

## Technologies

- C++
- CMake
- Binary Trees
- File I/O
- Data Structures

## Project Structure

- Huffman.cpp
- Huffman.h
- HuffmanDriver.cpp
- Node.h
- CMakeLists.txt
- Storage/
- images/
- text_files/

## Build and Run

```bash
mkdir build
cd build
cmake ..
make



```

## What I Learned

- How Huffman Coding reduces file size using variable-length encoding
- How to construct and traverse binary trees
- How to work with file input and output in C++
- How to organize compression and decompression workflows
