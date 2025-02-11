#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#define BYTE_SIZE 256

class HuffmanTree {
public:
    struct Node {
        unsigned char data;
        long long freq;
        Node *left, *right, *parent;
        bool is_byte() const {return left == nullptr && right == nullptr;}
        Node() : data(0), freq(0), left(nullptr), right(nullptr), parent(nullptr) {}
        Node(unsigned char data, unsigned long long frequency) : data(data), freq(frequency),
            left(nullptr), right(nullptr), parent(nullptr) {}
        inline bool operator==(const Node& node) {
            return data == node.data && freq == node.freq;
        }
    };

    // after building we have only one node in heap, this node is huffman tree
    void build(const unsigned long long *frequencies);

    // TODO: create new get_codes it 
    // void get_codes(std::unordered_map<unsigned char, std::string> &codes);

    Node* get_root() const { return heap_array[0]; }

    HuffmanTree(int capacity);

    HuffmanTree(unsigned long long* frequencies);

    ~HuffmanTree();
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
