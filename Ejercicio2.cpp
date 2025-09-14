#include <iostream>

template <class T, int n = 5>
class Stack {
	T* arr;
	T* elem;

public:
	Stack() {
		arr = new T[n];
		elem = nullptr;
	}

	void push(T e) {
		std::cout << "push " << e << std::endl;
		if (!elem) {
			elem = arr;
		}
		if (elem < arr + n) {
			*elem = e;
			elem++;
			print();
		}
		else {
			std::cout << "The limit has been exceeded." << std::endl;
		}
	}

	void pop(T& e) {
		if (elem == arr) {
			elem = nullptr;
		}
		if (!elem) {
			std::cout << "The stack is already empty." << std::endl;
			return;
		}
		if (elem > arr) {
			e = *elem;
			elem--;
		}
		std::cout << "pop " << *elem << std::endl;
		print();
	}

	void print() {
		std::cout << '[';
		for (T* p = arr; p < elem; p++) {
			if (p < elem - 1) std::cout << *p << ", ";
			else std::cout << *p;
		}
		std::cout << ']' << std::endl;
	}

	~Stack(){
		delete[] arr;
		std::cout << "Destructor call" << std::endl;
	}
};

int main() {
	const int tam = 15;
	Stack<int, tam> stack;
	int e;
	
	for (int i = 1; i <= tam; i++) {
		stack.push(i);
	}

	for (int i = tam; i > 0; i--) {
		stack.pop(e);
	}

	stack.pop(e);
	stack.push(7);
	stack.pop(e);
	stack.pop(e);
	stack.pop(e);
}