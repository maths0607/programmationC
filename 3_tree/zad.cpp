#include <iostream>
#include <queue>
using namespace std;

struct BNode
{
    int data; // элемент данных
    BNode *left, *right; // указатели на сыновей
    BNode(int d, BNode *l = nullptr, BNode *r = nullptr) :
    data(d), left(l), right(r) {} // конструктор
};


struct BTree
{   
    BNode * root; // корень дерева
    BTree (BNode *p) : root(p) {}
    static void f_print(BNode* r, int indent=0 );
   
   
   
    void print() // метод печати
    {
        f_print(root); // вызывает рекурсивную функцию
    }
    bool empty(){
        return root == nullptr;
    }
    //1.
    BNode* mostLeftGrandSon(){
        if(empty()) return nullptr;
        BNode* mostleftson = root->left? root->left : root->right;
        if(!mostleftson) return nullptr;
        return mostleftson->left? mostleftson->left:mostleftson->right;
    }
    //2.
    void rotateLeft(){
        BNode *rightchild = root-> right;
        if (rightchild ==nullptr) return ;
        root->right = rightchild->left;
        rightchild->left = root;
        root = rightchild;
    }
    //3.
    BNode* left_ouzel(){
        if(empty()) return nullptr;
        BNode *current = root;
        while(current && current->left){
            current = current->left;
        }
        return current;
    }
    //4.
    BNode* most_left_list(){
        if(empty()) return nullptr;
        BNode* current=root;
        while (current) {
            if (!current->left && !current->right) {
                return current; 
            }
            current = current->left ? current->left : current->right;
        }   
    }
    //5.
    void dele_most_left(){
        if(empty()) return ;
        if(!root->left && !root->right){
            delete root;
            root = nullptr;
        }
        BNode* current=root;
        BNode* currentChild;
        while (current) {
            currentChild = current->left ? current->left : current->right;
           if (!currentChild->left && !currentChild->right) {
                if(current->left){
                    delete current->left;
                    current->left =nullptr;
                    break;
                }else{
                    delete current->right;
                    current->right =nullptr;
                    break;
                }
            }
            current = current->left ? current->left : current->right;
        }   
    }
    //6. 
    BNode* second_most_left_list(){
        if(empty()) return nullptr; 

        queue<BNode*> q;
        q.push(root);
        int left_leaf_count = 0;

    while (!q.empty()) {
        BNode* current_node = q.front();
        q.pop();

        if (!current_node->left && !current_node->right) {
            left_leaf_count++;

            if (left_leaf_count == 2) {
                return current_node;
            }
        }

        if (current_node->left) {
            q.push(current_node->left);
        }
        if (current_node->right) {
            q.push(current_node->right);
        }
    }

    return nullptr;

    }
    

    

    
};
void BTree::f_print(BNode* r, int indent ) // indent - отступ
{
    if (r == nullptr) return;
    f_print(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
    cout << ' ';
    cout << r->data << endl;
    f_print(r->left, indent + 3);
}