# Huffman Coding Compressor

A C++ implementation of Huffman Coding for lossless text compression and decompression.

## Overview

This project implements a Huffman Coding compressor in C++. It builds a frequency table from text input, constructs a Huffman tree, generates variable-length binary codes, and uses those codes to compress and decompress text files.

The project demonstrates data structures, file I/O, binary trees, priority-based encoding, and lossless compression logic.

## Features

- Builds character frequency tables from text files
- Constructs a Huffman tree for variable-length encoding
- Generates binary codes for each character
- Compresses text using Huffman encoding
- Decompresses encoded files back into original text
- Includes sample text files for testing
- Uses separate source/header files for maintainability

## Technologies

- C++
- CMake
- Binary trees
- File I/O
- Data structures
- Lossless compression

## Core Concepts

This project demonstrates:

- Huffman Coding
- Binary tree traversal
- Character frequency analysis
- Variable-length prefix codes
- Text compression and restoration
- File serialization and deserialization

## Project Structure

.
├── Huffman.cpp
├── Huffman.h
├── HuffmanDriver.cpp
├── Node.h
├── CMakeLists.txt
├── Storage/
├── images/
└── text_files/

## Build and Run

```bash
mkdir build
cd build
cmake ..
make
