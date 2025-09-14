#include <iostream>

template <class T>
struct nodo {
	T value;
	nodo<T>* next;
	nodo(T v, nodo<T>* n = nullptr) {
		value = v;
		next = n;
	}
};

template <class T>
class LE {
	nodo<T>* HEAD = nullptr;
public:
	bool ADD(T value) {
		std::cout << "obj.ADD(" << value << ")" << std::endl;
		nodo<T>** pos;
		if (!find(value, pos)) {
			nodo<T>* tmp = new nodo<T>(value);
			tmp->next = *pos;
			*pos = tmp;
			print();
			return 1;
		}
		else {
			std::cout << "El elemento " << value << " ya se encuentra en la lista" << std::endl;
			return 0;
		}
	}

	bool DEL(T value) {
		std::cout << "obj.DEL(" << value << ")" << std::endl;
		nodo<T>** pos;
		if (find(value, pos)) {
			nodo<T>* tmp = *pos;
			*pos = tmp->next;
			delete tmp;
			print();
			return 1;
		}
		else {
			std::cout << "El elemento " << value << " no se encuentra en la lista" << std::endl;
			return 0;
		}
	}

	bool find(T value, nodo<T>**& pos) {
		for (pos = &HEAD; *pos && (*pos)->value < value; pos = &((*pos)->next));
		return *pos && (*pos)->value == value;
	}

	void print() {
		std::cout << "HEAD -> ";
		for (nodo<T>* p = HEAD; p; p = p->next) {
			std::cout << p->value << " -> ";
		}
		std::cout << "NULL" << std::endl;
	}

	~LE() {
		std::cout << "\nLlamada al destructor" << std::endl;
		print();
		while (HEAD) {
			DEL(HEAD->value);
		}
	}
};

int main() {
	LE<int> list;
	std::cout << "Creacion de lista enlazada" << std::endl;
	list.print();
	std::cout << "\nLlamadas a los metodos: " << std::endl;
	list.ADD(7);
	list.ADD(11);
	list.ADD(11);
	list.ADD(5);
	list.ADD(15);
	list.DEL(11);
	list.DEL(10);
	list.DEL(5);
	list.DEL(15);
}