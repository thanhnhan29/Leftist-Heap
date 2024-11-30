#include <iostream>
using namespace std;
struct LeftistHeap{
    int key;
    int len;
    LeftistHeap* left;
    LeftistHeap* right;
};
int getLen(LeftistHeap* p){
    return p ? p->len : -1;
}
LeftistHeap* init(int k){
    LeftistHeap* p = new LeftistHeap{k,-1,NULL,NULL};
    return p;
}
LeftistHeap* merge(LeftistHeap* l, LeftistHeap* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
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


int main() {
    LeftistHeap* heap = NULL;
    insert(heap,10);
    insert(heap,5);
    insert(heap,20);

    cout << "Insert:";
    inOrderTraversal(heap);
    cout << endl;

    deleteMin(heap);
    cout << "Delete min: ";
    inOrderTraversal(heap);
    cout << endl;
    deleteMin(heap);
    cout << "Delete min: ";
    inOrderTraversal(heap);
    cout << endl;

    delAll(heap);
    return 0;
}

