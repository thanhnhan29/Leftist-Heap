#include <iostream>
#include<vector>
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
    LeftistHeap* oldRoot = p;
    p = merge(p->left, p->right);
    delete oldRoot;
}
int getMin(LeftistHeap *&p){
    int tmp = p->key;
    deleteMin(p);
    return tmp;
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
int len(LeftistHeap* p) {
    int tmp = 0;
    if(!p) return tmp;
    if(p->left) tmp += len(p->left);
    tmp += 1;
    if(p->right) tmp += len(p->right);
    return tmp;
}
bool empty(LeftistHeap *p){
    return (p==NULL);
}
LeftistHeap* buildheap(vector<int> a){
    LeftistHeap* p = NULL;
    for(auto e: a){
        insert(p,e);
    }
    return p;
}

int main() {

    LeftistHeap* f1 = NULL;
    LeftistHeap* f2 = NULL;

    int n = 10;

    /// Test build heap tu 1 array
    vector<int> a(n);
    for(int i=0;i<n;i++) a[i] = rand()%1000;
    cout<<"moi cau duoi day se la cac heap rieng biet (co gia tri nhu mang a)\n";
    cout<<"---------\n";
    cout<<"Build heap tu array:\n";
    cout<<"a[i]: ";
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<endl;
    f1 = buildheap(a);
    cout<<"f1: ";
    while(!empty(f1)){
        cout<<getMin(f1)<<" ";
    } 
    cout<<endl;

    /// Test delete vai gia tri tu heap
    f1 = buildheap(a); // do da xoa het heap de in ra day tren, nen phai tao lai
    for(int i=0;i<5;i++) deleteMin(f1);
    cout<<"---------\n";
    cout<<"Sau khi xoa 5 gia tri nho nhat\n";
    cout<<"f1: ";
    while(!empty(f1)){
        cout<<getMin(f1)<<" ";
    } 
    cout<<endl;  



    cout<<"---------\n";
    /// test insert them 1 gia tri nho va 1 gia tri lon
    f1 = buildheap(a);
    cout<<"se insert gia tri -10 va gia tri 100000\n";
    insert(f1,-10);
    insert(f1,100000);
    cout<<"f1: ";
    while(!empty(f1)){
        cout<<getMin(f1)<<" ";
    } 
    cout<<endl; 
    cout<<"---------\n";



    // test get gia tri root;  
    f1 = buildheap(a);
    int tmp = getMin(f1);
    cout<<"Min: "<<tmp<<endl; 
    insert(f1,tmp);
    cout<<"---------\n";
    //test tinh so luong nut cua cay (do khong yeu cau dpt nen nhom em chon cach O(n) de bao toan struct heap nhu dinh nghia)
    cout<<"so nut: "<<len(f1)<<endl;
    

    cout<<"---------\n";
    // test rong
    cout<<(empty(f1)?"rong":"khong rong")<<endl;

    // delete all
    delAll(f1);


    cout<<"---------\n";
    vector<int> b(n);
    for(int i=0;i<n;i++) b[i] = rand()%10000;
    cout<<"a[i]: ";
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<"\nb[i]: ";
    for(int i=0;i<n;i++) cout<<b[i]<<" ";
    cout<<endl;
    cout<<"thao tac merge 2 heap: \n";
    f2 = buildheap(b);
    f1 = buildheap(a);
    f1 = merge(f1,f2);
    f2 = NULL; // sau khi merge f2 vao f1, thi tat ca cac null cua f2 da nam trong f1, nen f2 se dua ve NULL

    cout<<"f1: ";
    while(!empty(f1)){
        cout<<getMin(f1)<<" ";
    } 
    cout<<endl; 
    // khong can phai deleteAll nua, do getMin da xoa lun nut goc r.
    return 0;
}

