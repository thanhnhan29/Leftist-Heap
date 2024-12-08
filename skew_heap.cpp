#include <iostream>
#include <stdexcept>
using namespace std;

struct SkewHeapNode {
    int key;
    SkewHeapNode* left;
    SkewHeapNode* right;

    SkewHeapNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

class SkewHeap {
private:
    SkewHeapNode* root;

    SkewHeapNode* merge(SkewHeapNode* h1, SkewHeapNode* h2) {
        if (!h1) return h2;
        if (!h2) return h1;
        if (h1->key > h2->key) {
            swap(h1, h2);
        }
        h1->right = merge(h1->right, h2);
        swap(h1->left, h1->right);
        return h1;
    }

public:
    SkewHeap() : root(nullptr) {}

    void insert(int key) {
        SkewHeapNode* newNode = new SkewHeapNode(key);
        root = merge(root, newNode);
    }

    int extractMin() {
        if (!root) {
            throw runtime_error("Heap is empty");
        }
        int minKey = root->key;
        SkewHeapNode* oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
        return minKey;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
    void del(){
        while(!isEmpty()){
            extractMin();
        }
    }
};

int main() {
    SkewHeap skewHeap;

    skewHeap.insert(10);
    skewHeap.insert(5);
    skewHeap.insert(30);
    skewHeap.insert(2);

    cout << "Extracted min: " << skewHeap.extractMin() << endl; // Output: 2
    cout << "Extracted min: " << skewHeap.extractMin() << endl; // Output: 5
    cout << "Extracted min: " << skewHeap.extractMin() << endl; // Output: 10
    cout << "Extracted min: " << skewHeap.extractMin() << endl; // Output: 30
    skewHeap.del();
    return 0;
}
