#include <iostream>
#include <queue>

template <class T>
struct Node {
    Node<T>* nodes[2];
    T value;
    Node(T v) {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
};

template <class T>
class CBinTree {
private:
    Node<T>* root = nullptr;
public:
    bool Find(T x, Node<T>**& p) {
        for (p = &root; *p && (*p)->value != x; p = &((*p)->nodes[x > (*p)->value]));
        return *p != 0;
    }

    bool Ins(T x) {
        Node<T>** p;
        if (Find(x, p)) return 0;
        *p = new Node<T>(x);
        return 1;
    }

    Node<T>** rep(Node<T>** p) {
        Node<T>** q = &((*p)->nodes[1]);
        for (; (*q)->nodes[0]; q = &((*q)->nodes[0]));
        return q;
    }

    bool Rem(T x) {
        Node<T>** p;
        if (!Find(x, p)) return 0;
        if ((*p)->nodes[0] && (*p)->nodes[1]) {
            Node<T>** q = rep(p);
            (*p)->value = (*q)->value;
            p = q;
        }
        Node<T>* tmp = *p;
        *p = (*p)->nodes[(*p)->nodes[1] != 0];
        delete tmp;
        return 1;
    }

    int Height(Node<T>* n) {
        if (!n) return 0;
        int l = Height(n->nodes[0]);
        int r = Height(n->nodes[1]);
        return ((l > r) ? l : r) + 1;
    }

    int Altura() {
        return Height(root);
    }

    void Level() {
        std::queue<Node<T>*> q;
        Node<T>* n = root;
        int a = 1;
        q.push(n);
        while (!q.empty()) {
            n = q.front();
            std::cout << n->value << " ";
            if (n->nodes[0]) {
                q.push(n->nodes[0]);
            }
            if (n->nodes[1]) {
                q.push(n->nodes[1]);
            }
            q.pop();
        }
    }
};

int main() {
    CBinTree<int> t;
    t.Ins(80);
    t.Ins(100);
    t.Ins(70);
    t.Ins(75);
    t.Ins(73);
    t.Rem(75);
    t.Rem(100);
    t.Level();
    std::cout << '\n' << t.Altura();
}