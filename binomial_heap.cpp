#include <iostream>
#include <climits>
using namespace std;

struct BinomialNode {
    int key;
    int degree;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int value) : key(value), degree(0), parent(nullptr), child(nullptr), sibling(nullptr) {}
};

class BinomialHeap {
private:
    BinomialNode* head;

    BinomialNode* mergeTrees(BinomialNode* b1, BinomialNode* b2) {
        if (b1->key > b2->key) {
            swap(b1, b2);
        }
        b2->parent = b1;
        b2->sibling = b1->child;
        b1->child = b2;
        b1->degree++;
        return b1;
    }

    BinomialNode* unionHeaps(BinomialNode* h1, BinomialNode* h2) {
        if (!h1) return h2;
        if (!h2) return h1;

        BinomialNode* newHead = nullptr;
        BinomialNode* tail = nullptr;

        BinomialNode* a = h1;
        BinomialNode* b = h2;

        while (a && b) {
            if (a->degree <= b->degree) {
                if (!newHead) {
                    newHead = a;
                    tail = a;
                } else {
                    tail->sibling = a;
                    tail = a;
                }
                a = a->sibling;
            } else {
                if (!newHead) {
                    newHead = b;
                    tail = b;
                } else {
                    tail->sibling = b;
                    tail = b;
                }
                b = b->sibling;
            }
        }

        if (a) tail->sibling = a;
        if (b) tail->sibling = b;

        return newHead;
    }

    BinomialNode* adjustHeap(BinomialNode* h) {
        if (!h || !h->sibling) return h;

        BinomialNode* prev = nullptr;
        BinomialNode* curr = h;
        BinomialNode* next = h->sibling;

        while (next) {
            if ((curr->degree != next->degree) || (next->sibling && next->sibling->degree == curr->degree)) {
                prev = curr;
                curr = next;
            } else {
                if (curr->key <= next->key) {
                    curr->sibling = next->sibling;
                    curr = mergeTrees(curr, next);
                } else {
                    if (!prev) {
                        h = next;
                    } else {
                        prev->sibling = next;
                    }
                    curr = mergeTrees(next, curr);
                }
            }
            next = curr->sibling;
        }

        return h;
    }

public:
    BinomialHeap() : head(nullptr) {}

    void insert(int key) {
        BinomialNode* newNode = new BinomialNode(key);
        head = unionHeaps(head, newNode);
        head = adjustHeap(head);
    }

    int getMin() {
        if (!head) throw runtime_error("Heap is empty");

        BinomialNode* minNode = head;
        BinomialNode* curr = head;
        while (curr) {
            if (curr->key < minNode->key) {
                minNode = curr;
            }
            curr = curr->sibling;
        }

        return minNode->key;
    }

    void extractMin() {
        if (!head) throw runtime_error("Heap is empty");

        BinomialNode* minNode = head;
        BinomialNode* prevMinNode = nullptr;
        BinomialNode* curr = head;
        BinomialNode* prev = nullptr;

        while (curr) {
            if (curr->key < minNode->key) {
                minNode = curr;
                prevMinNode = prev;
            }
            prev = curr;
            curr = curr->sibling;
        }

        if (prevMinNode) {
            prevMinNode->sibling = minNode->sibling;
        } else {
            head = minNode->sibling;
        }

        BinomialNode* child = minNode->child;
        BinomialNode* newHead = nullptr;
        while (child) {
            BinomialNode* nextChild = child->sibling;
            child->sibling = newHead;
            child->parent = nullptr;
            newHead = child;
            child = nextChild;
        }

        head = unionHeaps(head, newHead);
        head = adjustHeap(head);

        delete minNode;
    }

    bool isEmpty() {
        return head == nullptr;
    }
    void del(){
        while(!isEmpty()) extractMin();
    }
};

int main() {
    BinomialHeap heap;

    heap.insert(10);
    heap.insert(3);
    heap.insert(15);
    heap.insert(5);

    cout << "Minimum: " << heap.getMin() << endl; // Output: 3
    heap.extractMin();
    cout << "Minimum: " << heap.getMin() << endl; // Output: 5
    heap.extractMin();
    cout << "Minimum: " << heap.getMin() << endl; // Output: 10
    heap.del();
    return 0;
}
