#include <iostream>
#include <ctime>
#include <chrono>
#include <cstring>

static void build_arr(int* begin, int tam) {
	srand(time(NULL));
	for (int* p = begin; p < begin + tam; p++) {
		*p = rand();
	}
}

/*-------------------------- DIRECT --------------------------*/
static void direct_bubble_sort(int* begin, int tam) {
	for (int i = 0; i < tam - 1; i++) {
		for (int* p = begin; p < begin + tam - 1 - i; p++) {
			if (*p > *(p + 1)) { // if (*p < *(p + 1))
				std::swap(*p, *(p + 1));
			}
		}
	}
}

/*-------------------------- FUNCTOR --------------------------*/
struct Functor_Ascending {
	inline bool operator() (int a, int b) const {
		return a > b;
	}
};

struct Functor_Descending {
	inline bool operator() (int a, int b) const {
		return a < b;
	}
};

template <class Functor_Order>
static void functor_bubble_sort(int* begin, int tam, Functor_Order& b) {
	for (int i = 0; i < tam - 1; i++) {
		for (int* p = begin; p < begin + tam - 1 - i; p++) {
			if (b(*p, *(p + 1)))
			{
				std::swap(*p, *(p + 1));
			}
		}
	}
}

/*-------------------- FUNCTION POINTER --------------------*/
static bool function_pointer_ascending(int a, int b) {
	return a > b;
}

static bool function_pointer_descending(int a, int b) {
	return a < b;
}

static void function_pointer_bubble_sort(int* begin, int tam, bool (*order)(int, int)) {
	for (int i = 0; i < tam - 1; i++) {
		for (int* p = begin; p < begin + tam - 1 - i; p++) {
			if (order(*p, *(p + 1)))
			{
				std::swap(*p, *(p + 1));
			}
		}
	}
}

/*------------------------ POLYMORPHISM ------------------------*/
class Polymorphism_Order {
public:
	virtual bool cmp(int a, int b) = 0;
};

class Polymorphism_Ascending : public Polymorphism_Order {
public:
	bool cmp(int a, int b) override {
		return a > b;
	}
};

class Polymophism_Descending : public Polymorphism_Order {
public:
	bool cmp(int a, int b) override {
		return a < b;
	}
};

static void polymorphism_bubble_sort(int* begin, int tam, Polymorphism_Order& b) {
	for (int i = 0; i < tam - 1; i++) {
		for (int* p = begin; p < begin + tam - 1 - i; p++) {
			if (b.cmp(*p, *(p + 1)))
			{
				std::swap(*p, *(p + 1));
			}
		}
	}
}

int main() {
	int tam;
	std::cout << "Enter the size of the array: ";
	std::cin >> tam;
	int* original_arr = new int[tam];
	int* arr = new int[tam];
	build_arr(original_arr, tam);

	/*-------------------------- DIRECT --------------------------*/
	memcpy(arr, original_arr, tam * sizeof(int));
	auto start = std::chrono::high_resolution_clock::now();
	direct_bubble_sort(arr, tam);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "DIRECT" << '\n' << "It took me " << duration.count() / 1000 << '.' << duration.count() % 1000 << " seconds\n" << std::endl;

	/*-------------------------- FUNCTOR --------------------------*/
	memcpy(arr, original_arr, tam * sizeof(int));
	Functor_Ascending functor_ba;
	start = std::chrono::high_resolution_clock::now();
	functor_bubble_sort(arr, tam, functor_ba);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "FUNCTOR" << '\n' << "It took me " << duration.count() / 1000 << '.' << duration.count() % 1000 << " seconds\n" << std::endl;
	
	/*-------------------- FUNCTION POINTER --------------------*/
	memcpy(arr, original_arr, tam * sizeof(int));
	bool (*order)(int, int);
	order = function_pointer_ascending;
	start = std::chrono::high_resolution_clock::now();
	function_pointer_bubble_sort(arr, tam, order);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "FUNCTION POINTER" << '\n' << "It took me " << duration.count() / 1000 << '.' << duration.count() % 1000 << " seconds\n" << std::endl;
	
	/*------------------------ POLYMORPHISM ------------------------*/
	memcpy(arr, original_arr, tam * sizeof(int));
	Polymorphism_Ascending polymorphism_ba;
	start = std::chrono::high_resolution_clock::now();
	polymorphism_bubble_sort(arr, tam, polymorphism_ba);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	std::cout << "POLYMORPHISM" << '\n' << "It took me " << duration.count() / 1000 << '.' << duration.count() % 1000 << " seconds" << std::endl;

	delete[] arr;
}