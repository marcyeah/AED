#include <iostream>

template <class T, int n = 5>
class Queue {
	T* arr;
	T* front;
	T* rear;

public:
	Queue() {
		arr = new T[n];
		front = arr;
		rear = arr;
	}

	void enqueue(T e) {
		std::cout << "enqueue " << e << std::endl;
		if (rear < arr + n) {
			if (rear == arr || rear != front) {
				*rear = e;
				rear++;
				print();
			}
			else if (rear == front) {
				std::cout << "The limit has been exceeded." << std::endl;
			}
		}
		else if (rear == arr + n && front != arr) {
			rear = arr;
			*rear = e;
			rear++;
			print();
		}
		else {
			std::cout << "The limit has been exceeded." << std::endl;
		}
	}

	void dequeue(T& e) {
		if (front == rear && rear == arr) {
			std::cout << "The queue is already empty." << std::endl;
			return;
		}
		if (front == arr + n) {
			std::cout << "dequeue " << *arr << std::endl;
			e = *arr;
		}
		else {
			std::cout << "dequeue " << *front << std::endl;
			e = *front;
		}
		
		if ((rear > front || front != arr) && front + 1 != rear) {
			if (front == arr + n && rear < front) {
				front = arr;
				if (rear == arr + 1) {
					rear = arr;
				}
			}
			else {
				front++;
			}
			print();
		}
		else if (front + 1 == rear) {
			front = arr;
			rear = arr;
			print();
		}
	}

	void print() {
		T* p = front;
		std::cout << '[';
		if (front == arr || rear > front) {
			for (; p < rear; p++) {
				if (p < rear - 1) std::cout << *p << ", ";
				else std::cout << *p;
			}
		}
		else {
			while (p < arr + n) {
				std::cout << *p << ", ";
				p++;
			}
			p = arr;
			while (p < rear) {
				if (p < rear - 1) std::cout << *p << ", ";
				else std::cout << *p;
				p++;
			}
		}
		std::cout << ']' << std::endl;
	}

	~Queue() {
		delete[] arr;
		std::cout << "Destructor call" << std::endl;
	}
};

int main() {
	const int tam = 3;
	Queue<int, tam> queue;
	int e;

	for (int i = 4; i <= 6; i++) {
		queue.enqueue(i);
	}

	queue.dequeue(e);
	queue.enqueue(16);
	queue.dequeue(e);
	queue.dequeue(e);
	queue.dequeue(e);
}