#include <iostream>
#include <vector>
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

class LazyBinomialHeap {
private:
    vector<BinomialNode*> roots;

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

    void consolidate() {
        vector<BinomialNode*> newRoots(roots.size(), nullptr);

        for (auto tree : roots) {
            while (tree) {
                int d = tree->degree;
                if (newRoots[d] == nullptr) {
                    newRoots[d] = tree;
                    break;
                } else {
                    tree = mergeTrees(tree, newRoots[d]);
                    newRoots[d] = nullptr;
                }
            }
        }

        roots.clear();
        for (auto tree : newRoots) {
            if (tree) {
                roots.push_back(tree);
            }
        }
    }

public:
    LazyBinomialHeap() {}

    void insert(int key) {
        roots.push_back(new BinomialNode(key));
    }

    int getMin() {
        if (roots.empty()) throw runtime_error("Heap is empty");

        int minKey = INT_MAX;
        for (auto tree : roots) {
            if (tree && tree->key < minKey) {
                minKey = tree->key;
            }
        }
        return minKey;
    }

    void extractMin() {
        if (roots.empty()) throw runtime_error("Heap is empty");

        int minIndex = -1;
        int minKey = INT_MAX;

        for (int i = 0; i < roots.size(); ++i) {
            if (roots[i] && roots[i]->key < minKey) {
                minKey = roots[i]->key;
                minIndex = i;
            }
        }

        if (minIndex == -1) return;

        BinomialNode* minNode = roots[minIndex];
        roots.erase(roots.begin() + minIndex);

        BinomialNode* child = minNode->child;
        vector<BinomialNode*> newTrees;

        while (child) {
            BinomialNode* next = child->sibling;
            child->sibling = nullptr;
            child->parent = nullptr;
            newTrees.insert(newTrees.begin(), child);
            child = next;
        }

        roots.insert(roots.end(), newTrees.begin(), newTrees.end());
        consolidate();

        delete minNode;
    }

    bool isEmpty() {
        return roots.empty();
    }
    void del(){
        while(!isEmpty()) extractMin();
    }
};

int main() {
    LazyBinomialHeap heap;

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
