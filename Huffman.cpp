#include <iostream>
#include <map>
#include <sstream>
#include "Huffman.h"

map<char, string> codes;

/**
 * Constructor of the Huffman class
 */
Huffman::Huffman() {
    root = nullptr;
    storage = new Storage();
}

/**
  * Destructor of the Huffman class
  */
Huffman::~Huffman() {
    delete storage;
}

/**
 * Compresses a file using Huffman coding
 * @param in_file The input file to compress
 * @param out_file The output file to write the compressed data
 */
void Huffman::compress(string in_file, string out_file) {
    map<char, int> frequencies;
    ifstream input(in_file);
    if (!input.is_open()) {
        cout << "Error opening input file: " << in_file << endl;
    }

    // Generate frequency table
    cout << "Generating frequency table..." << endl;
    char character;
    while (input.get(character)) {
        frequencies[character]++;
    }
    input.close();

    // Generate priority queue
    cout << "Generating priority queue..." << endl;
    priority_queue<Node*, vector<Node*>,compareWeights> queue;
    for(pair<char, int> frequency : frequencies) {
        Node* node = new Node (frequency.first, frequency.second);
        queue.push(node);
    }

    // Creating Huffman tree
    cout << "Creating Huffman tree..." << endl;
    HuffmanBuildTree(queue);

    // Generate codes
    cout << "Generating codes..." << endl;
    HuffmanGetCodes(root, "");

    string header = "";
    for (auto it = frequencies.cbegin(); it != frequencies.cend(); it++) {
        header += to_string(int(it->first)) + ":" + to_string(it->second) + ",";
    }

    header = header.substr(0, header.size() - 1);

    // Writing compressed file
    cout << "Writing compressed file..." << endl;
    input.open(in_file);
    storage->open(out_file, "write");

    storage->setHeader(header);

    while (input.get(character)) {
        storage->insert(codes[character]);
    }
    input.close();
    storage->close();
}

/**
  * Decompresses a compressed file using Huffman coding
  * @param in_file The input file receiving the compressed data
  * @param out_file The output file to write the decompressed data
  */
void Huffman::decompress(string in_file, string out_file) {
    map<char, int> frequencies;
    int frequency, char_count=0, char_output=0;
    storage->open(in_file, "read");

    // Reading header
    cout << "Reading header..." << endl;
    string header = storage->getHeader();
    stringstream ssheader (header);
    string item;
    char character;
    string val;
    string code;
    while (getline (ssheader, item, ',')) {
        string schar;
        stringstream ssitem (item);
        getline(ssitem, schar, ':');
        getline(ssitem, val, ':');
        character = char(stoi(schar));
        try {
            frequency = stoi(val);
            char_count += frequency;
            frequencies[character] = frequency;
        }
        catch(...) {
            cout << schar << endl << endl;
        }
    }

    // Generate priority queue
    cout << "Generating priority queue..." << endl;
    priority_queue<Node*, vector<Node*>,compareWeights> queue;
    for(pair<char, int> frequency : frequencies) {
        Node* node = new Node (frequency.first, frequency.second);
        queue.push(node);
    }

    // Creating Huffman tree
    cout << "Creating Huffman tree..." << endl;
    HuffmanBuildTree(queue);

    // Writing decompressed data to the output file
    cout << "Decompressing data..." << endl;
    ofstream output(out_file);
    string binary_string;
    Node* node = root;
    while(storage->extract(binary_string)) {
        for(char bit:binary_string) {
            if (bit == '0') {
                node = node->zero;
            } else {
                node = node->one;
            }
            if (node->letter != '\0') {
                output << node->letter;
                node = root;
                char_output++;
                cout << node->letter;
            }
            if(char_output == char_count)
                break;
        }
    }

    output.close();
    storage->close();
}

/**
 * Encodes a text string using Huffman coding
 * @param text The text string to encode
 * @return The encoded text string
 */
string Huffman::encode(string text) {
    HuffmanGetCodes(root, "");

    string encoded_text;
    for (char character : text) {
        encoded_text += codes[character];
    }

    return encoded_text;
}

/**
 * Using Huffman codes for each character in the frequency table
 * @param root The root node of the Huffman tree
 * @param prefix The current prefix code for the node
 */
string Huffman::decode(string encoded_text) {
    string decoded_text;
    Node* node = root;

    for(char bit : encoded_text) {
        if (bit == '0') {
            node = node->zero;
        } else {
            node = node->one;
        }

        if (node->letter != '\0') {
            decoded_text += node->letter;
            node = root;
        }
    }

    return decoded_text;
}

/**
 * Builds the Huffman tree using the frequency table
 * @param queue The priority queue containing the nodes of the Huffman tree
 */
void Huffman::HuffmanBuildTree(priority_queue<Node*, vector<Node*>, compareWeights>& queue) {
    while (queue.size() > 1) {
        Node* left = queue.top();
        queue.pop();
        Node* right = queue.top();
        queue.pop();

        int weight = left->weight + right->weight;
        Node* parent = new Node ('\0', weight, left, right);
        queue.push(parent);
    }

    root = queue.top();
}

/**
 * Making Huffman codes for each character from the frequency table
 * @param root The root node of the Huffman tree
 * @param prefix The current prefix code for the node
 */
void Huffman::HuffmanGetCodes(Node* root, string prefix) {
    if(root->zero)
        HuffmanGetCodes(root->zero, prefix + '0');
    if(root->one)
        HuffmanGetCodes(root->one, prefix + '1');

    if (!root->zero && !root->one) {
        root->code = prefix;
        codes[root->letter] = root->code;
    }
}