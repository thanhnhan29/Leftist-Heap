#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
using namespace std;


struct FibonacciNode {
    int key;
    int degree;
    bool marked;
    FibonacciNode* parent;
    FibonacciNode* child;
    FibonacciNode* left;
    FibonacciNode* right;

    FibonacciNode(int value)
        : key(value), degree(0), marked(false), parent(nullptr), child(nullptr), left(this), right(this) {}
};

class FibonacciHeap {
private:
    FibonacciNode* minNode;
    int nodeCount;

    void link(FibonacciNode* y, FibonacciNode* x) {
        y->left->right = y->right;
        y->right->left = y->left;

        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->right = y;
            y->left = y;
        } else {
            y->right = x->child;
            y->left = x->child->left;
            x->child->left->right = y;
            x->child->left = y;
        }

        x->degree++;
        y->marked = false;
    }

    void consolidate() {
        int maxDegree = static_cast<int>(log2(nodeCount)) + 1;
        vector<FibonacciNode*> A(maxDegree, nullptr);

        vector<FibonacciNode*> rootList;
        FibonacciNode* current = minNode;
        do {
            rootList.push_back(current);
            current = current->right;
        } while (current != minNode);

        for (auto w : rootList) {
            FibonacciNode* x = w;
            int d = x->degree;
            while (A[d] != nullptr) {
                FibonacciNode* y = A[d];
                if (x->key > y->key) {
                    swap(x, y);
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }

        minNode = nullptr;
        for (auto x : A) {
            if (x != nullptr) {
                if (minNode == nullptr || x->key < minNode->key) {
                    minNode = x;
                }
            }
        }
    }

public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}

    void insert(int key) {
        FibonacciNode* newNode = new FibonacciNode(key);
        if (minNode == nullptr) {
            minNode = newNode;
        } else {
            newNode->right = minNode->right;
            newNode->left = minNode;
            minNode->right->left = newNode;
            minNode->right = newNode;
            if (newNode->key < minNode->key) {
                minNode = newNode;
            }
        }
        nodeCount++;
    }

    int getMin() {
        if (minNode == nullptr) throw runtime_error("Heap is empty");
        return minNode->key;
    }

    void extractMin() {
        if (minNode == nullptr) throw runtime_error("Heap is empty");

        FibonacciNode* z = minNode;
        if (z->child != nullptr) {
            FibonacciNode* child = z->child;
            do {
                FibonacciNode* next = child->right;
                child->parent = nullptr;

                child->left->right = child->right;
                child->right->left = child->left;

                child->right = minNode->right;
                child->left = minNode;
                minNode->right->left = child;
                minNode->right = child;

                child = next;
            } while (child != z->child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            minNode = nullptr;
        } else {
            minNode = z->right;
            consolidate();
        }

        delete z;
        nodeCount--;
    }

    bool isEmpty() {
        return minNode == nullptr;
    }
    void del(){
        while(!isEmpty()) extractMin();
    }
        void merge(FibonacciHeap& other) {
        if (other.minNode == nullptr) return; // Không có gì để merge nếu heap khác rỗng
        if (minNode == nullptr) {
            minNode = other.minNode;
        } else {
            // Nối danh sách gốc của hai heap
            FibonacciNode* temp = minNode->right;
            minNode->right = other.minNode->right;
            other.minNode->right->left = minNode;
            other.minNode->right = temp;
            temp->left = other.minNode;

            // Cập nhật minNode
            if (other.minNode->key < minNode->key) {
                minNode = other.minNode;
            }
        }
        nodeCount += other.nodeCount;

        // Reset heap khác sau khi merge
        other.minNode = nullptr;
        other.nodeCount = 0;
    }
};


int main() {
    FibonacciHeap heap;

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
