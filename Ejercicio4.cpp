#include <iostream>

template <class T, int n>
struct node {
	T arr[n];
	node<T, n>* next;
};

template <class T, int n = 5>
class Stack {
	node<T, n>* list, *l, *k;
	T* end;
	T* elem;

public:
	Stack() {
		list = new node<T, n>();
		l = list;
		k = nullptr;
		end = (list->arr) + n;
		elem = nullptr;
	}

	void push(T e) {
		std::cout << "push " << e << std::endl;
		if (!elem) {
			elem = list->arr;
		}
		if (elem < end) {
			*elem = e;
			elem++;
			print();
		}
		else {
			l->next = new node<T, n>();
			k = l;
			l = l->next;
			end = (l->arr) + n;
			elem = l->arr;
			*elem = e;
			elem++;
			print();
		}
	}

	void pop(T& e) {
		if (elem == list->arr) {
			elem = nullptr;
		}
		if (!elem) {
			std::cout << "The stack is already empty." << std::endl;
			return;
		}
		if (elem > l->arr) {
			e = *elem;
			elem--;
		}
		else {
			node<T, n>* tmp;
			if (l != list) {
				tmp = l;
				l = k;
				l->next = nullptr;
				end = l->arr + n;
				elem = l->arr + n;
				delete tmp;
			}
			e = *elem;
			elem--;
		}
		std::cout << "pop " << *elem << std::endl;
		print();
	}

	void print() {
		node<T,n>* p = list;
		std::cout << '[';
		while (p) {
			T* end;
			if (p->next) {
				end = p->arr + n;
			}
			else {
				end = elem;
			}
			for (T* q = p->arr; end && q < end; q++) {
				if (q < end - 1 || (p->next && elem != l->arr)) std::cout << *q << ", ";
				else std::cout << *q;
			}
			p = p->next;
		}
		std::cout << ']' << std::endl;
	}

	~Stack() {
		delete list;
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
	stack.push(9);
	stack.pop(e);
	stack.pop(e);
	stack.push(7);
	stack.pop(e);
}