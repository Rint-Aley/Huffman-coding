#include "huffman_tree.h"

#include <iostream>
#include <ostream>


HuffmanTree::HuffmanTree(int capacity) : heap_size(0), pointers_size(0), capacity(capacity),
        heap_array(new Node *[capacity]), pointers(new Node *[capacity]) {
    for (int i = 0; i < capacity; ++i) {
        pointers[i] = new HuffmanTree::Node;
    }
}

HuffmanTree::HuffmanTree(unsigned long long* frequencies) : HuffmanTree(BYTE_SIZE * 2) {
    build(frequencies);
}

HuffmanTree::~HuffmanTree() {
    for (int i = 0; i < capacity; ++i) {
        if (pointers[i] != nullptr)
            delete pointers[i];
    }
    delete[] pointers;
    delete[] heap_array;
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
    if (left < heap_size && heap_array[left]->freq < heap_array[smallest]->freq)
        smallest = left;
    if (right < heap_size && heap_array[right]->freq < heap_array[smallest]->freq)
        smallest = right;
    if (smallest != index) {
        swap(heap_array[smallest], heap_array[index]);
        heapify(smallest);
    }
}

HuffmanTree::Node* HuffmanTree::erase() {
    Node *node = heap_array[0];
    heap_array[0] = heap_array[heap_size - 1];
    --heap_size;
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

    heap_array[heap_size] = pointers[pointers_size];

    left->parent = pointers[pointers_size];
    right->parent = pointers[pointers_size];

    ++pointers_size;
    ++heap_size;
    sift_up();
}

void HuffmanTree::sift_up() {
    int i = heap_size - 1;
    while (i > 0 && heap_array[(i - 1) / 2]->freq > heap_array[i]->freq) {
        swap(heap_array[i], heap_array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void HuffmanTree::build(const unsigned long long *freq) {
    unsigned char count = 0;
    for (int i = 0; i < BYTE_SIZE; ++i) {
        if (freq[i] != 0) {
            pointers[count]->freq = freq[i];
            pointers[count]->data = i;
            heap_array[count] = pointers[count];
            ++count;
        }
    }
    heap_size = count;
    pointers_size = count;
    for (int i = (heap_size - 1) / 2; i >= 0; --i) {
        heapify(i);
    }
    Node *left, *right;
    while (heap_size > 1) {
        left = erase();
        right = erase();

        insert(0, left->freq + right->freq, left, right);
    }
}