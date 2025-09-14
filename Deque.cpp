#include <iostream>

template <class T, int tam = 3, int n = tam * 2>
class Deque {
    T** map;
    T** p;
    T** q;
    T* head;
    T* tail;
public:
    Deque() {
        map = new T*[tam];
        p = map + (tam / 2);
        q = map + (tam / 2);
        head = nullptr;
        tail = nullptr;
    }

    void push_back(T value) {
        *q = new T[n];
        if (!tail) {
            tail = *q + tam - 1;
            head = tail;
        }
        else if (*q + tam - 1 < tail) {
            T** newmap = new T* [tam * 3];
            T** tmp = map;
            for (T** m = p, ** n = newmap + tam + (p - map); m < q; m++, n++) {
                *n = *m;
            }
            p = newmap + tam + (p - map);
            q = newmap + tam + (q - map);
            *p = new T[n];
            tail = *q;
            map = newmap;
            tam *= 3;
            delete[] tmp;
        }
        *tail = value;
        tail++;
    }

    void push_front(T value) {
        *p = new T[n];
        if (!head) {
            head = *p + tam - 1;
            tail = head;
        }
        else if (head < *p) {
            T** newmap = new T * [tam * 3];
            T** tmp = map;
            for (T** m = p, **n = newmap + tam + (p - map); m < q; m++, n++) {
                *n = *m;
            }
            p = newmap + tam + (p - map);
            *p = new T[n];
            q = newmap + tam + (q - map);
            head = *p + n - 1;
            map = newmap;
            tam *= 3;
            delete[] tmp;
        }
        *head = value;
        head--;
    }

    void pop_back() {
        if (head == tail) {
            std::cout << "The deque is already empty" << std::endl;
            return;
        }
        if (p != q && tail == *q) {
            
        }

    }

    void pop_front() {

    }

    void print() {

    }

    ~Deque() {

    }
};

int main()
{
    std::cout << "Hello World!\n";
}