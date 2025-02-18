#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#define BYTE_SIZE 256

#include "BitWriter.h"

class HuffmanTree {
public:
    struct Node {
        unsigned char data;
        long long freq;
        Node *left, *right, *parent;
        bool is_leaf() const {return left == nullptr && right == nullptr;}
        Node() : data(0), freq(0), left(nullptr), right(nullptr), parent(nullptr) {}
        Node(unsigned char data, unsigned long long frequency) : data(data), freq(frequency),
            left(nullptr), right(nullptr), parent(nullptr) {}
        inline bool operator==(const Node& node) const {
            return data == node.data && freq == node.freq;
        }
        ~Node() {
            delete left;
            delete right;
        }
    };

    HuffmanTree(int capacity);

    HuffmanTree(unsigned long long* frequencies);

    ~HuffmanTree();

    // after building we have only one node in heap, this node is huffman tree
    void build(const unsigned long long *frequencies);
    
    Node* get_root() const { return heap_array[0]; }

    BitFieldInfo** convert_tree_to_bit_fields() const;

    int get_number_of_nodes() const { return pointers_size; }

    int get_number_of_leafs() const { return (pointers_size + 1) / 2; }
private:
    int capacity;

    // Array for heap implementation
    Node **heap_array;
    int heap_size;

    // the array where all pointers are stored
    Node **pointers;
    int pointers_size;

    void swap(Node *&a, Node *&b);

    void heapify(int index);

    void sift_up();

    void insert(unsigned char data, long long freq, Node *left = nullptr, Node *right = nullptr);

    Node *erase();
};

#endif //HUFFMAN_TREE_H
