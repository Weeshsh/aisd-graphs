#include "Vector.h"

class Stack {
private:
    Vector elements;
    int size;
    
public:
    Stack();

    void push(int data);

    int pop();

    bool isEmpty() const;
    int getSize() const;

    ~Stack();
};
