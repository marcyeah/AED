#include <iostream>

template <class T, int n = 5>
class Vector {
	T tam = n;
	T* arr = new T[n];
	T* elem = arr;
public:
	void push_back(T e) {
		if (elem < arr + tam) {
			*elem = e;
			elem++;
		}
		else {
			T* newarr = new T[tam * 2];
			for (int i = 0; i < tam; i++) {
				newarr[i] = arr[i];
			}
			tam *= 2;
			arr = newarr;
			delete[] newarr;
		}
	}

	void push_front(T e) {
		if (elem < arr + tam) {
			for (T* p = arr + 1; p <= elem; p++) {
				std::swap(*p, *arr);
			}
			*arr = e;
			elem++;
		}
		else {
			T* newarr = new T[tam * 2];
			for (int i = 0; i < tam; i++) {
				newarr[i] = arr[i];
			}
			tam *= 2;
			arr = newarr;
			delete[] newarr;
		}
	}

	void pop_front(T& e) {
		if (elem > arr) {
			e = *arr;
			for (T* p = arr; p < elem - 1; p++) {
				p = p + 1;
			}
			elem--;
		}
		else {
			std::cout << "The vector is already empty" << std::endl;
		}
	}

	void pop_back(T& e) {
		e = *(elem - 1);
		if (elem > arr) {
			elem--;
		}
		else {
			std::cout << "The vector is already empty" << std::endl;
		}
	}

	void print() {
		std::cout << '[';
		for (T* p = arr; p < elem; p++) {
			if (p < elem - 1) std::cout << *p << ", ";
			else std::cout << *p;
		}
		std::cout << ']' << std::endl;
	}

	~Vector() {
		delete[] arr;
	}
};

template<class T>
struct nodo {
	T value;
	nodo<T>* next;
	nodo<T>* prev;
	nodo(T v, nodo<T>* n = nullptr, nodo<T>* p = nullptr) {
		value = v;
		next = n;
		prev = p;
	}
};

template<class T>
class LDE {
	nodo<T>* HEAD;
	nodo<T>* TAIL;
	nodo<T>** p;
	nodo<T>** n;
	nodo<T>** q;
	nodo<T>** m;
public:
	LDE() {
		HEAD = nullptr;
		TAIL = nullptr;
		p = &HEAD;
		q = &TAIL;
	}

	void push_back(T e) {
		nodo<T>* tmp = new nodo<T>(e);
		tmp->prev = TAIL;
		tmp->next = nullptr;
		TAIL = tmp;
		*p = tmp;
		p = &(tmp->next);
	}

	void push_front(T e) {
		nodo<T>* tmp = new nodo<T>(e);
		tmp->prev = nullptr;
		tmp->next = HEAD;
		HEAD = tmp;
		*q = tmp;
		q = &(tmp->prev);
	}

	void pop_back() {
		if (*q) {
			nodo<T>* tmp = TAIL;
			TAIL = tmp->prev;
			*n = nullptr;
			p = n;

			delete tmp;
		}
	}

	void pop_front() {
		if (*p) {
			nodo<T>* tmp = HEAD;
			if (tmp->next) {
				HEAD = tmp->next;
				q = &(HEAD->prev);
				delete tmp;
			}
			else {
				q = &TAIL;
				delete tmp;
			}
		}
	}

	void print() {
		std::cout << "HEAD -> ";
		for (nodo<T>* p = HEAD; p; p = p->next) {
			std::cout << p->value << " -> ";
		}
		std::cout << "NULL" << std::endl;
	}

	~LDE(){
		std::cout << "\nLlamada al destructor" << std::endl;
		print();
		while (HEAD) {
			pop_front();
		}
	}
};

int main() {
	LDE<int> v;
	int e;
	v.push_back(8);
	v.print();
	v.push_back(9);
	v.print();
	v.push_front(7);
	v.print();
	v.pop_front();
	v.print();
	v.pop_back();
	v.print();
}