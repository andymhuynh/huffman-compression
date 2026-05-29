#include <string>
#include <queue>
#include <fstream>
#include "Node.h"
#include "Storage/Storage.h"
using namespace std;

#ifndef HUFFMAN_H
#define HUFFMAN_H

class Huffman {
public:
    /**
     * Constructor of the Huffman class
     */
    Huffman();

    /**
     * Destructor of the Huffman class
     */
    ~Huffman();

    /**
     * Compresses a file using Huffman coding
     * @param in_file The input file to compress
     * @param out_file The output file to write the compressed data
     */
    void compress(string in_file, string out_file);

    /**
     * Decompresses a compressed file using Huffman coding
     * @param in_file The input file receiving the compressed data
     * @param out_file The output file to write the decompressed data
     */
    void decompress(string in_file, string out_file);

    /**
     * Encodes a text string using Huffman coding
     * @param text The text string to encode
     * @return The encoded text string
     */
    string encode(string text);

    /**
     * Using Huffman codes for each character in the frequency table
     * @param root The root node of the Huffman tree
     * @param prefix The current prefix code for the node
     */
    string decode(string encoded_text);

private:
    /**
     * Builds the Huffman tree using the frequency table
     * @param queue The priority queue containing the nodes of the Huffman tree
     */
    void HuffmanBuildTree(priority_queue<Node*, vector<Node*>, compareWeights>& queue);

    /**
     * Making Huffman codes for each character from the frequency table
     * @param root The root node of the Huffman tree
     * @param prefix The current prefix code for the node
     */
    void HuffmanGetCodes(Node* root, string prefix);

    /**
     * The root node of the Huffman tree
     */
    Node* root;

    /**
     * Store the Huffman codes and compressed data
     */
    Storage* storage;

};

#endif //HUFFMAN_H