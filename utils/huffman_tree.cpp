#include "huffman_tree.h"

#include <iostream>
#include <ostream>


HuffmanTree::HuffmanTree(int capacity) : size(0), pointers_size(0), capacity(capacity), code_index(0),
                                         array(new Node *[capacity]),
                                         pointers(new Node *[capacity]), code_string(new char[capacity]) {
    for (int i = 0; i < capacity; ++i) {
        pointers[i] = new HuffmanTree::Node;
    }
}

HuffmanTree::~HuffmanTree() {
    for (int i = 0; i < capacity; ++i) {
        delete pointers[i];
    }
    delete[] pointers;
    delete[] array;
    delete[] code_string;
}

void HuffmanTree::swap(Node *&a, Node *&b) {
    Node *tmp = a;
    a = b;
    b = tmp;
}

void HuffmanTree::heapify(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < size && array[left]->freq < array[smallest]->freq)
        smallest = left;
    if (right < size && array[right]->freq < array[smallest]->freq)
        smallest = right;
    if (smallest != index) {
        swap(array[smallest], array[index]);
        heapify(smallest);
    }
}

HuffmanTree::Node *HuffmanTree::erase() {
    Node *node = array[0];
    array[0] = array[size - 1];
    --size;
    heapify(0);
    return node;
}

void HuffmanTree::insert(unsigned char data, long long freq, Node *left, Node *right) {
    if (pointers_size >= capacity) {
        std::cerr << "Heap is full" << std::endl;
        return;
    }
    pointers[pointers_size]->data = data;
    pointers[pointers_size]->freq = freq;
    pointers[pointers_size]->left = left;
    pointers[pointers_size]->right = right;

    array[size] = pointers[pointers_size];

    ++pointers_size;
    ++size;
    sift_up();
}

void HuffmanTree::sift_up() {
    int i = size - 1;
    while (i > 0 && array[(i - 1) / 2]->freq > array[i]->freq) {
        swap(array[i], array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void HuffmanTree::build(const unsigned char *data, const long long *freq, int length) {
    for (int i = 0; i < length; ++i) {
        pointers[i]->freq = freq[i];
        pointers[i]->data = data[i];
        array[i] = pointers[i];
    }
    size = length;
    pointers_size = length;
    for (int i = (size - 1) / 2; i >= 0; --i) {
        heapify(i);
    }
    Node *left, *right;
    while (size > 1) {
        left = erase();
        right = erase();

        insert(0, left->freq + right->freq, left, right);
    }
}

void HuffmanTree::inorder_walk(std::unordered_map<unsigned char, std::string> &codes, Node *node) {
    if (node->left != nullptr) {
        code_string[code_index++] = '0';
        inorder_walk(codes, node->left);
        --code_index;
    }
    if (node->is_byte()) {
        for (int i = 0; i < code_index; ++i) {
            codes[node->data].push_back(code_string[i]);
        }
    }
    if (node->right != nullptr) {
        code_string[code_index++] = '1';
        inorder_walk(codes, node->right);
        --code_index;
    }
}

void HuffmanTree::get_codes(std::unordered_map<unsigned char, std::string> &codes) {
    Node *node = array[0];
    inorder_walk(codes, node);
}

void HuffmanTree::print() {
    int height = (int) ceil(log2(size + 1));
    int maxNodesInLevel = 1;
    int elementsOnLevel = 0;

    for (int level = 0; level < height; level++) {
        int spaces = (int) pow(2, height - level) - 1 + 10;

        for (int i = elementsOnLevel; i < size && i < elementsOnLevel + maxNodesInLevel; ++i) {
            for (int j = 0; j < spaces; j++)
                std::cout << ' ';
            std::cout << array[i]->data << ' ' << array[i]->freq;
            for (int j = 0; j < spaces; j++)
                std::cout << ' ';
        }
        std::cout << '\n';
        elementsOnLevel += maxNodesInLevel;
        maxNodesInLevel *= 2;
    }
    printf("\n");
    for (int i = 0; i < size; ++i) {
        std::cout << array[i]->data << ' ' << array[i]->freq << ' ';
    }

}