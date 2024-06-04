#include "vector.h"
#include <iostream>

const int GROWTH = 4;

Vector::Vector() : values(new int[1] {0}), size(1), length(0) {}

void Vector::pushBack(int value) {
    if (length + 1 > size) {
        size *= GROWTH;
        int* temp = new int[size];
        for (int i = 0; i < length; i++) {
            temp[i] = values[i];
        }
        delete[] values;
        values = temp;
    }
    values[length++] = value;
}

void Vector::clear() {
    delete[] values;
    values = new int[1] {0};
    size = 1;
    length = 0;
}

void Vector::reserve(int len) {
    delete[] values;
    values = new int[len];
    size = len;
    length = 0;
}

int Vector::getSize() const {
    return this->length;
}

Vector::~Vector() {
    delete[] values;
}
    
int& Vector::operator[](int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Vector index out of range");
    }
    return values[index];
}

void Vector::removeLast() {
    if (length > 0) {
        length--;
        if (length < size / GROWTH) {
            size /= GROWTH;
            if (size == 0) {
                size = 1;
            }
            int* temp = new int[size];
            for (int i = 0; i < length; i++) {
                temp[i] = values[i];
            }
            delete[] values;
            values = temp;
        }
    }
}
