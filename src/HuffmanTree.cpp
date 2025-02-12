#include "HuffmanTree.h"
#include "BitWriter.h"
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

void write_bit_field(BitFieldInfo** arr, unsigned char byte, unsigned char* buffer, short length) {
    short buffer_len = (length + 7) / 8;
    unsigned char* new_buffer = new unsigned char[buffer_len];
    for (int i = 0; i < buffer_len; ++i) {
        new_buffer[i] = buffer[i];
    }
    arr[byte] = new BitFieldInfo(new_buffer, length);
}

BitFieldInfo** HuffmanTree::convert_tree_to_bit_fields()
{
    BitFieldInfo **result = new BitFieldInfo*[BYTE_SIZE];
    
    Node* current_node = get_root();
    if (current_node == nullptr) {
        return result;
    }

    unsigned char buffer[BYTE_SIZE / 8] = { 0 };
    unsigned char *new_buffer, switcher;
    short length = 1, buffer_len;

    while (true) {
        // Get to the leftmost element
        while (!current_node->left->is_leaf()) {
            current_node = current_node->left;
            ++length;
        }
        // Add this element to result
        buffer_len = (length + 7) / 8;
        write_bit_field(result, current_node->left->data, buffer, length);
        // Switch current bit
        switcher = 0x01 << ((length - 1) % 8);
        buffer[buffer_len - 1] ^= switcher;
        // Check for the right node. If it isn't a leaf, then return to the beggining
        if (!current_node->right->is_leaf()) {
            current_node = current_node->right;
            ++length;
            continue;
        }
        // Otherwise, add right element to result
        write_bit_field(result, current_node->right->data, buffer, length);
        // Depend on the written code in buffer, we return back to parents until reach element with 0 bit
        while (true) {
            if ((buffer[buffer_len - 1] & switcher) == 0 && current_node->right->is_leaf()) {
                buffer[buffer_len - 1] ^= switcher;
                write_bit_field(result, current_node->right->data, buffer, length);
            }
            else if ((buffer[buffer_len - 1] & switcher) == 0) {
                buffer[buffer_len - 1] ^= switcher;
                current_node = current_node->right;
                ++length;
                break;
            }
            buffer[buffer_len - 1] ^= switcher;
            --length;
            // When there is no bit with 0 value then return from loop
            if (length == 0) {
                return result;
            }
            buffer_len = (length + 7) / 8;
            switcher = 0x01 << ((length - 1) % 8);
            current_node = current_node->parent;
        }
    }
}
