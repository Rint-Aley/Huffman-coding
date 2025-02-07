#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H


#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <string>
#include <iostream>

class HuffmanTree {
public:
    struct Node {
        unsigned char data;
        long long freq;
        Node *left, *right;
        bool is_byte() const {return left == nullptr && right == nullptr;}
        Node() : data(0), freq(0), left(nullptr), right(nullptr) {}
    };

    // after building we have only one node in heap, this node is huffman tree
    void build(const unsigned char *data, const long long *freq, int length);

    void get_codes(std::unordered_map<unsigned char, std::string> &codes);

    void print();

    Node * get_huffman_tree(){
        return array[0];
    }

    HuffmanTree(int capacity);

    ~HuffmanTree();
private:
    char *code_string;
    int code_index = 0;

    int capacity;

    // array for heap implementation
    Node **array;
    int size;

    // the array where all pointers are stored
    Node **pointers;
    int pointers_size;

    void swap(Node *&a, Node *&b);

    void heapify(int index);

    void sift_up();

    void insert(unsigned char data, long long freq, Node *left = nullptr, Node *right = nullptr);

    Node *erase();

    void inorder_walk(std::unordered_map<unsigned char, std::string> &codes, Node *node);


};


#endif //HUFFMAN_TREE_H
