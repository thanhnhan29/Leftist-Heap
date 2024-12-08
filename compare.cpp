#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <chrono>
#include<ctime>
#include<cstdlib>
using namespace std;
struct LeftistHeap{
    int key;
    int len;
    LeftistHeap* left;
    LeftistHeap* right;
};

class MinHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }

    int left(int i) { return 2 * i + 1; }

    int right(int i) { return 2 * i + 2; }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l] < heap[smallest]) 
            smallest = l;
        
        if (r < heap.size() && heap[r] < heap[smallest]) 
            smallest = r;
        
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    int getMin() {
        if (heap.empty()) 
            throw runtime_error("Heap is empty");
        return heap[0];
    }

    void deleteMin() {
        if (heap.empty())
            throw runtime_error("Heap is empty");

        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    bool isEmpty() {
        return heap.empty();
    }

    void printHeap() {
        for (int i : heap)
            cout << i << " ";
        cout << endl;
    }
        void merge(MinHeap& other) {
        // Gộp tất cả phần tử từ heap khác vào heap hiện tại
        for (int key : other.heap) {
            this->insert(key);
        }
    }
    void del(){
        while(!isEmpty()){
            deleteMin();
        }
    }
};

int getLen(LeftistHeap* p){
    return p ? p->len : -1;
}
LeftistHeap* init(int k){
    LeftistHeap* p = new LeftistHeap{k,-1,NULL,NULL};
    return p;
}
LeftistHeap* merge(LeftistHeap* l, LeftistHeap* r) {
    if (l == NULL) return r;
    if (r == NULL) return l;
    if (l->key > r->key) swap(l, r);

    l->right = merge(l->right, r);

    if (getLen(l->left) < getLen(l->right)) swap(l->left, l->right);

    l->len = getLen(l->right) + 1;
    return l;
}

void insert(LeftistHeap* &p, int k) {
    if(p==NULL) p = new LeftistHeap{k,-1,NULL,NULL};
    else{
        LeftistHeap* newNode = new LeftistHeap{k,-1,NULL,NULL};
        p = merge(p, newNode);
    }
}

void deleteMin(LeftistHeap* &p) {
    if(p==NULL) return;
    LeftistHeap* oldRoot = p;
    p = merge(p->left, p->right);
    delete oldRoot;
}
int getmin(LeftistHeap* p){
    return p? p->key: -1;
}
void inOrderTraversal(LeftistHeap* p) {
    if(!p) return;
    if(p->left) inOrderTraversal(p->left);
    cout << p->key << " ";
    if(p->right) inOrderTraversal(p->right);
}
void delAll(LeftistHeap* &p){
    while(p){
        deleteMin(p);
    }
}
struct SkewHeapNode {
    int key;
    SkewHeapNode* left;
    SkewHeapNode* right;

    SkewHeapNode(int val) : key(val), left(nullptr), right(nullptr) {}
};

class SkewHeap {
private:
    SkewHeapNode* root;
public:
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
    SkewHeapNode* getRoot() const {
        return root;
    }
};


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

void compare_insert(LeftistHeap* &leftistheap, FibonacciHeap &fiheap, SkewHeap &skewheap, MinHeap &Mheap){
    int n = 100;
    cout<<"stt:\tleft\tfiheap\tskewheap\tMheap";
    for(int i = 0;i<=4;i++){
        cout<<"n: "<<n<<"\t";
        vector<int> a(n);
        for(int j=0;j<n;j++) a[j] = rand() % 100;

        auto start_1 = chrono::high_resolution_clock::now();
        for(int j=0;j<n;j++) insert(leftistheap,a[j]);
        auto end_1 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t1 = (end_1 - start_1);
        cout<<(double)t1.count()<<"\t";

        auto start_2 = chrono::high_resolution_clock::now();
        for(int j=0;j<n;j++) fiheap.insert(a[j]);
        auto end_2 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t2 = (end_2 - start_2);
        cout<<(double)t2.count()<<"\t";
    

        auto start_3 = chrono::high_resolution_clock::now();
        for(int j=0;j<n;j++) skewheap.insert(a[j]);
        auto end_3 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t3 = (end_3 - start_3);
        cout<<(double)t3.count()<<"\t";

        auto start_4 = chrono::high_resolution_clock::now();
        for(int j=0;j<n;j++) Mheap.insert(a[j]);
        auto end_4 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t4 = (end_4 - start_4);
        cout<<(double)t4.count()<<"\t";

        // delAll(leftistheap);
        // fiheap.del();
        // skewheap.del();
        // Mheap.del();
        cout<<endl;
        n*=10;
    }
}


void compare_getmin(int n, LeftistHeap* &leftistheap, FibonacciHeap &fiheap, SkewHeap &skewheap, MinHeap &Mheap){
    cout<<"stt:\tleft\tfiheap\tskewheap\tRegularheap\n";
    cout<<n<<"\t";
    auto start_1 = chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++) deleteMin(leftistheap);
    auto end_1 = chrono::high_resolution_clock::now();
    chrono::duration<double>  t1 = (end_1 - start_1);
    cout<<(double)t1.count()<<"\t";

    auto start_2 = chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++)    fiheap.extractMin();
    auto end_2 = chrono::high_resolution_clock::now();
    chrono::duration<double>  t2 = (end_2 - start_2);
    cout<<(double)t2.count()<<"\t";


    auto start_3 = chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++)    skewheap.extractMin();
    auto end_3 = chrono::high_resolution_clock::now();
    chrono::duration<double>  t3 = (end_3 - start_3);
    cout<<(double)t3.count()<<"\t";

    auto start_4 = chrono::high_resolution_clock::now();
    for(int i=0;i<n;i++)    Mheap.deleteMin();
    auto end_4 = chrono::high_resolution_clock::now();
    chrono::duration<double>  t4 = (end_4 - start_4);
    cout<<(double)t4.count()<<"\t";

    cout<<endl;
    n*=10;
    
}

void compare_merge(){
    cout<<"stt:\tleft\tfiheap\tskewheap\tRegularheap\n";
    int n = 100;

    int m = 100;
    vector<LeftistHeap*> LH(m,NULL);
    vector<FibonacciHeap> FH(m);
    vector<SkewHeap> SH(m);
    vector<MinHeap> MH(m);
    for(int i=0;i<=2;i++){

        vector<vector<int>> a(m,vector<int>(n));
        for(int j=0;j<m;j++) 
            for(int z=0;z<n;z++)
                a[j][z] = rand() % 100;
        for(int j=0;j<m;j++){
            for(int z=0;z<n;z++){
                insert(LH[j],a[j][z]);
                FH[j].insert(a[j][z]);
                SH[j].insert(a[j][z]);
                MH[j].insert(a[j][z]);
            }
        }
        //cout<<leftistheap1->key<<" "<<leftistheap2->key<<endl;
        auto start_1 = chrono::high_resolution_clock::now();
        for(int j=1;j<m;j++) LH[0] = merge(LH[0],LH[j]);
        auto end_1 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t1 = (end_1 - start_1);
        cout<<(double)t1.count()<<"\t";

        auto start_2 = chrono::high_resolution_clock::now();
        for(int j=1;j<m;j++) FH[0].merge(FH[j]);
        auto end_2 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t2 = (end_2 - start_2);
        cout<<(double)t2.count()<<"\t";


        auto start_3 = chrono::high_resolution_clock::now();
        for(int j=1;j<m;j++) SH[0].merge(SH[0].getRoot(),SH[j].getRoot());
        auto end_3 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t3 = (end_3 - start_3);
        cout<<(double)t3.count()<<"\t";

        auto start_4 = chrono::high_resolution_clock::now();
        for(int j=1;j<m;j++) MH[0].merge(MH[j]);
        auto end_4 = chrono::high_resolution_clock::now();
        chrono::duration<double>  t4 = (end_4 - start_4);
        cout<<(double)t4.count()<<"\t";

        // for(int j=0;j<100;j++){
        //     delAll(LH[j]);
        //     FH[j].del();
        //     SH[j].del();
        //     MH[j].del();
        // }
        cout<<endl;
        n*=10;
    }


}

int main() {
    // LeftistHeap* LH = NULL;
    // FibonacciHeap FH;
    // SkewHeap SH;
    // MinHeap MH;
    // compare_insert(LH,FH,SH,MH);
    // compare_getmin(1000000,LH,FH,SH,MH);
    compare_merge();
    return 0;
}

/*
getmin
stt:    left    fiheap  skewheap        Regularheap
10000   0.00743396      0.138308        0.00730746      0.00386229
stt:    left    fiheap  skewheap        Regularheap
100000  0.0443286       0.4125  0.055149        0.0363801
stt:    left    fiheap  skewheap        Regularheap
1000000 0.452097        3.92153 0.583363        0.327813
*/