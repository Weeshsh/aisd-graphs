#pragma once

class Vector {
private:
    int* values;
    int size;
    int length;

public:
    Vector();
    void pushBack(int value);
    void removeLast();

    void clear();
    void reserve(int len);

    int getSize() const;
    int& operator[](int index);

    ~Vector();
};