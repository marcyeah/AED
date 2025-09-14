#include <iostream>

template <class T, int n>
struct node {
	T arr[n];
	node<T, n>* next;
};

template <class T, int n = 5>
class PriorityQueue {
	node<T, n>* list, * l, * k;
	T* end;
	T* front;
	T* rear;
	T* rprev;
	int count;

public:
	PriorityQueue() {
		list = new node<T, n>();
		l = list;
		k = nullptr;
		end = (list->arr) + n;
		front = list->arr;
		rear = list->arr;
		rprev = rear;
		count = 0;
	}

	int& operator[](int i) {
		if (front + i >= list->arr + n) {
			if (i >= n) {
				return *(l->arr + i % n);
			}
			else {
				return *(list->arr + (i - (front - list->arr) - 1));
			}
		}
		return *(front + i);
	}

	void push(T e) {
		std::cout << "enqueue " << e << std::endl;
		if (rear < end) {
			if (rear == l->arr || rear != front) {
				*rear = e;
				rear++;
			}
			else if (rear == front) {
				l->next = new node<T, n>();
				k = l;
				l = l->next;
				end = (l->arr) + n;
				rear = l->arr;
				*rear = e;
				rear++;
			}
		}
		else if (rear == end && front != l->arr) {
			rear = list->arr;
			*rear = e;
			rear++;
		}
		else {
			l->next = new node<T, n>();
			k = l;
			l = l->next;
			end = (l->arr) + n;
			rear = l->arr;
			*rear = e;
			rear++;
		}
		if (l->arr == list->arr) {
			rprev = rear;
		}

		int i = count;
		while (i) {
			if ((*this)[i] > (*this)[(i - 1) / 2]) {
				std::swap((*this)[i], (*this)[(i - 1) / 2]);
			}
			i = (i - 1) / 2;
		}
		count++;

		print();
	}

	void pop(T& e) {
		if (front == rear) {
			std::cout << "The queue is already empty." << std::endl;
			return;
		}
		if (front == end) {
			std::cout << "dequeue " << *(l->arr) << std::endl;
			e = *(l->arr);
		}
		else {
			std::cout << "dequeue " << *front << std::endl;
			e = *front;
		}

		if (front < rear) {
			if (front != end) {
				if (front + 1 == rear) {
					front = list->arr;
					rear = list->arr;
				}
				else {
					front++;
				}
			}
			else {
				node<T, n>* tmp = list;
				list = list->next;
				if (list->next = l) {
					k = nullptr;
				}
				front = l->arr;
				delete tmp;
			}
		}

		else if (front >= rear) {
			if (front != end) {
				if (front + 1 == list->arr + n) {
					node<T, n>* tmp = list;
					list = list->next;
					if (list->next = l) {
						k = nullptr;
					}
					front = l->arr;
					delete tmp;
				}
				else {
					front++;
				}
			}
			else {
				front = l->arr;
			}
		}

		int i = count;
		while (i) {
			if ((*this)[i] > (*this)[i - 1]) {
				std::swap((*this)[i], (*this)[i - 1]);
			}
			i--;
		}
		count--;

		print();
		if (l->arr == list->arr) {
			rprev = rear;
		}
	}

	void print() {
		T* p = front;
		std::cout << '[';
		if (front == list->arr || (rprev > front && rprev == rear)) {
			for (; p < rprev; p++) {
				if (p < rprev - 1) std::cout << *p << ", ";
				else std::cout << *p;
			}
		}
		else {
			while (p < list->arr + n) {
				std::cout << *p << ", ";
				p++;
			}
			p = list->arr;
			while (p < rprev) {
				if (p < rprev - 1) std::cout << *p << ", ";
				else std::cout << *p;
				p++;
			}
			if (list->next) {
				std::cout << ", ";
			}
		}
		if (list->next && rprev != rear) {
			std::cout << ", ";
			if (front == list->arr) {
				for (; p < list->arr + n; p++) {
					std::cout << *p << ", ";
				}
				p = l->arr;
				for (; p < rear; p++) {
					if (p < rear - 1) std::cout << *p << ", ";
					else std::cout << *p;
				}
			}
			else {
				p = l->arr;
				for (; p < rear; p++) {
					if (p < rear - 1) std::cout << *p << ", ";
					else std::cout << *p;
				}
			}
		}
		std::cout << ']' << std::endl;
	}

	~PriorityQueue() {
		node<T, n>* c = list;
		node<T, n>* cn = list->next;
		while (cn) {
			delete c;
			c = cn;
			cn = c->next;
		}
		delete c;
		std::cout << "Destructor call" << std::endl;
	}
};

int main() {
	const int tam = 3;
	PriorityQueue<int, tam> heaptree;

	heaptree.push(1);
	heaptree.push(2);
	heaptree.push(3);
	heaptree.push(4);
	heaptree.push(5);
	heaptree.push(6);
}