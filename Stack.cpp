#include "Stack.h"

Stack::Stack() : elements(), size(0) {};

void Stack::push(int data) {
	size++;
	this->elements.pushBack(data);
}

int Stack::pop() {
	if (size == 0) {
		return -1;
	}
	size--;
	int res = this->elements[size];
	this->elements.removeLast();
	return res;
}

bool Stack::isEmpty() const {
	return this->size==0;
}

int Stack::getSize() const {
	return this->size;
}

Stack::~Stack() {
	elements.clear();
}