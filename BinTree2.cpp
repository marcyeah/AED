#include <iostream>
#include <queue>
#include <stack>

template <class T>
struct Node {
    Node<T>* nodes[2];
    T value;
    int height;
    int hd;
    Node(T v) {
        value = v;
        nodes[0] = nodes[1] = 0;
        height = 0;
        hd = 0;
    }
};

template <class T>
class CBinTree {
private:
    Node<T>* root = nullptr;
public:
    bool Find(T x, Node<T>**& p, std::stack<Node<T>*>& path) {
        for (p = &root; *p && (*p)->value != x; p = &((*p)->nodes[x > (*p)->value])) {
            path.push(*p);
        }
        return *p != 0;
    }

    bool Ins(T x) {
        Node<T>** p;
        std::stack<Node<T>*> path;
        if (Find(x, p, path)) return 0;
        *p = new Node<T>(x);
        while (!path.empty()) {
            Node<T>* actual = path.top();
            int lh = actual->nodes[0] ? actual->nodes[0]->height : 0;
            int rh = actual->nodes[1] ? actual->nodes[1]->height : 0;
            actual->height = std::max(lh, rh) + 1;
            actual->hd = rh - lh;
            int heightdiff = actual->hd;
            if (heightdiff == 2 && actual->nodes[1]) {
                if (actual->nodes[1]->hd == 1) {
                    std::swap(actual->value, actual->nodes[1]->value);
                    Node<T>* tmp = actual->nodes[1];
                    Node<T>* a = actual->nodes[0];
                    int arh = a && a->nodes[1] ? a->nodes[1]->height : 0;
                    int ch = actual->nodes[1]->nodes[1] ? actual->nodes[1]->nodes[1]->height : 0;
                    actual->nodes[1] = actual->nodes[1]->nodes[1];
                    actual->nodes[0] = tmp;
                    tmp->nodes[1] = tmp->nodes[0];
                    tmp->nodes[0] = a;
                    tmp->height = std::max(lh, arh) + 1;
                    actual->height = std::max(tmp->height, ch) + 1;
                    break;
                }
                else if (actual->nodes[1]->hd == -1) {
                    std::swap(actual->value, actual->nodes[1]->nodes[0]->value);
                    Node<T>* tmp = actual->nodes[0];
                    Node<T>* a = actual->nodes[1]->nodes[0];
                    Node<T>* ar = a->nodes[1];
                    int arh = ar ? ar->height : 0;
                    int alh = a->nodes[0] ? a->nodes[0]->height : 0;
                    int ch = actual->nodes[1]->nodes[1] ? actual->nodes[1]->nodes[1]->height : 0;
                    int blh = tmp ? tmp->height : 0;
                    actual->nodes[0] = a;
                    a->nodes[1] = a->nodes[0];
                    a->nodes[0] = tmp;
                    actual->nodes[1]->nodes[0] = ar;
                    a->height = std::max(blh, alh) + 1;
                    actual->nodes[1]->height = std::max(ch, arh) + 1;
                    actual->height = std::max(actual->nodes[1]->height, a->height) + 1;
                    break;
                }
            }
            else if (heightdiff == -2 && actual->nodes[0]) {
                if (actual->nodes[0]->hd == -1) {
                    std::swap(actual->value, actual->nodes[0]->value);
                    Node<T>* tmp = actual->nodes[0];
                    Node<T>* b = actual->nodes[1];
                    int blh = b && b->nodes[0] ? b->nodes[0]->height : 0;
                    int ah = actual->nodes[0]->nodes[0] ? actual->nodes[0]->nodes[0]->height : 0;
                    actual->nodes[0] = actual->nodes[0]->nodes[0];
                    actual->nodes[1] = tmp;
                    tmp->nodes[0] = tmp->nodes[1];
                    tmp->nodes[1] = b;
                    tmp->height = std::max(lh, blh) + 1;
                    actual->height = std::max(tmp->height, ah) + 1;
                    break;
                }
                else if (actual->nodes[0]->hd == 1) {
                    std::swap(actual->value, actual->nodes[0]->nodes[1]->value);
                    Node<T>* tmp = actual->nodes[1];
                    Node<T>* a = actual->nodes[0]->nodes[1];
                    Node<T>* ar = a->nodes[0];
                    int arh = ar ? ar->height : 0;
                    int alh = a->nodes[1] ? a->nodes[1]->height : 0;
                    int ch = actual->nodes[0]->nodes[0] ? actual->nodes[0]->nodes[0]->height : 0;
                    int blh = tmp ? tmp->height : 0;
                    actual->nodes[1] = a;
                    a->nodes[0] = a->nodes[1];
                    a->nodes[1] = tmp;
                    actual->nodes[0]->nodes[1] = ar;
                    a->height = std::max(blh, alh) + 1;
                    actual->nodes[0]->height = std::max(ch, arh) + 1;
                    actual->height = std::max(actual->nodes[0]->height, a->height) + 1;
                    break;
                }
            }
            path.pop();
        }
        return 1;
    }

    Node<T>** rep(Node<T>** p) {
        Node<T>** q = &((*p)->nodes[1]);
        for (; (*q)->nodes[0]; q = &((*q)->nodes[0]));
        return q;
    }

    bool Rem(T x) {
        Node<T>** p;
        std::stack<Node<T>*> path;
        if (!Find(x, p, path)) return 0;
        if ((*p)->nodes[0] && (*p)->nodes[1]) {
            Node<T>** q = rep(p);
            (*p)->value = (*q)->value;
            p = q;
        }
        Node<T>* tmp = *p;
        *p = (*p)->nodes[(*p)->nodes[1] != 0];
        delete tmp;
        while (!path.empty()) {
            Node<T>* actual = path.top();
            int lh = actual->nodes[0] ? actual->nodes[0]->height : 0;
            int rh = actual->nodes[1] ? actual->nodes[1]->height : 0;
            actual->height = std::max(lh, rh) + 1;
            actual->hd = rh - lh;
            int heightdiff = actual->hd;
            if (heightdiff == 2 && actual->nodes[1]) {
                if (actual->nodes[1]->hd == 1) {
                    std::swap(actual->value, actual->nodes[1]->value);
                    Node<T>* tmp = actual->nodes[1];
                    Node<T>* a = actual->nodes[0];
                    int arh = a && a->nodes[1] ? a->nodes[1]->height : 0;
                    int ch = actual->nodes[1]->nodes[1] ? actual->nodes[1]->nodes[1]->height : 0;
                    actual->nodes[1] = actual->nodes[1]->nodes[1];
                    actual->nodes[0] = tmp;
                    tmp->nodes[1] = tmp->nodes[0];
                    tmp->nodes[0] = a;
                    tmp->height = std::max(lh, arh) + 1;
                    actual->height = std::max(tmp->height, ch) + 1;
                    break;
                }
                else if (actual->nodes[1]->hd == -1) {
                    std::swap(actual->value, actual->nodes[1]->nodes[0]->value);
                    Node<T>* tmp = actual->nodes[0];
                    Node<T>* a = actual->nodes[1]->nodes[0];
                    Node<T>* ar = a->nodes[1];
                    int arh = ar ? ar->height : 0;
                    int alh = a->nodes[0] ? a->nodes[0]->height : 0;
                    int ch = actual->nodes[1]->nodes[1] ? actual->nodes[1]->nodes[1]->height : 0;
                    int blh = tmp ? tmp->height : 0;
                    actual->nodes[0] = a;
                    a->nodes[1] = a->nodes[0];
                    a->nodes[0] = tmp;
                    actual->nodes[1]->nodes[0] = ar;
                    a->height = std::max(blh, alh) + 1;
                    actual->nodes[1]->height = std::max(ch, arh) + 1;
                    actual->height = std::max(actual->nodes[1]->height, a->height) + 1;
                    break;
                }
            }
            else if (heightdiff == -2 && actual->nodes[0]) {
                if (actual->nodes[0]->hd == -1) {
                    std::swap(actual->value, actual->nodes[0]->value);
                    Node<T>* tmp = actual->nodes[0];
                    Node<T>* b = actual->nodes[1];
                    int blh = b && b->nodes[0] ? b->nodes[0]->height : 0;
                    int ah = actual->nodes[0]->nodes[0] ? actual->nodes[0]->nodes[0]->height : 0;
                    actual->nodes[0] = actual->nodes[0]->nodes[0];
                    actual->nodes[1] = tmp;
                    tmp->nodes[0] = tmp->nodes[1];
                    tmp->nodes[1] = b;
                    tmp->height = std::max(lh, blh) + 1;
                    actual->height = std::max(tmp->height, ah) + 1;
                    break;
                }
                else if (actual->nodes[0]->hd == 1) {
                    std::swap(actual->value, actual->nodes[0]->nodes[1]->value);
                    Node<T>* tmp = actual->nodes[1];
                    Node<T>* a = actual->nodes[0]->nodes[1];
                    Node<T>* ar = a->nodes[0];
                    int arh = ar ? ar->height : 0;
                    int alh = a->nodes[1] ? a->nodes[1]->height : 0;
                    int ch = actual->nodes[0]->nodes[0] ? actual->nodes[0]->nodes[0]->height : 0;
                    int blh = tmp ? tmp->height : 0;
                    actual->nodes[1] = a;
                    a->nodes[0] = a->nodes[1];
                    a->nodes[1] = tmp;
                    actual->nodes[0]->nodes[1] = ar;
                    a->height = std::max(blh, alh) + 1;
                    actual->nodes[0]->height = std::max(ch, arh) + 1;
                    actual->height = std::max(actual->nodes[0]->height, a->height) + 1;
                    break;
                }
            }
            path.pop();
        }
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