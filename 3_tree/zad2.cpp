#include <iostream>
#include <queue>
#include <limits>
#include <string>
#include <stack>
using namespace std;

struct BNode
{
    int data; // элемент данных
    BNode *left, *right,*father; // указатели на сыновей

    BNode(int d,BNode* f=nullptr, BNode *l = nullptr, BNode *r = nullptr) :
    data(d), left(l), right(r) ,father(f){} // конструктор
};
void f_print(BNode* r, int indent = 0) // indent - отступ
{
    if (r == nullptr) return;
    f_print(r->right, indent + 3);
    for (int i = 0; i < indent; ++i)
    cout << ' ';
    cout << r->data << endl;
    f_print(r->left, indent + 3);
}

struct BTree
{
    BNode * root; // корень дерева
    BTree (BNode *p) : root(p) {}
    // конструктор по указателю на узел
    void print() // метод печати
    {
        f_print(root); // вызывает рекурсивную функцию
    }
    bool empty(){
        return (root == nullptr);
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
        if(rightchild->left){
            rightchild->left->father = root;
        }
        rightchild->father=root;
        root->father=rightchild;

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

        stack<BNode*> q;
        q.push(root);
        int left_leaf_count = 0;

    while (!q.empty()) {
        BNode* current_node = q.top();
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
    //8.
    void delet_ouzel(BNode* & p){
        if(p->left && p->right){
            cout<<"problem";
        }
        if(!p->left && !p->right){
            if(p->father->left == p){
                p->father->left = nullptr;
            }else{
                 p->father->right =nullptr;
            }
            delete p;
            return;
        }
        if(p->father->left == p){
                p->father->left = p->left?p->left:p->right;
        }else{
                 p->father->right = p->left?p->left:p->right;
            }
        return;

    }


    ///ОБХОД
    //1
    int sum(BNode * p){
        if(!p) return 0;
        return p->data + sum(p->left) + sum(p->right);
    }
    int sum(){
        return sum(root);
    }
    //2
    int count_neg(BNode *p){
        if(!p) return 0;
        return (p->data<0 ? 1 : 0)+count_neg(p->left)+count_neg(p->right);
    }
    int count_neg(){
        return count_neg(root);
    }
    //3
    int high(BNode *p){
        if(!p) return 0;
        int h1 = high(p->left);
        int h2 = high(p->right);
        return 1 + (h1<h2? h2:h1);
    }
    int high(){
        return high(root);
    }
    //4
    void reflect(BNode *p){
        if(!p) return;
        // BNode *temp = p->left;
        // p->left = p->right;
        // p->right = temp;
        swap(p->left,p->right);
        reflect(p->left);
        reflect(p->right);    

    }
    void reflect(){
        reflect(root);
    }
    //5
    int mult(BNode *p){
        if(!p) return 1;
        return ((p->right && p->left)? p->data : 1)*mult(p->left)*mult(p->right);

    }
    int mult(){
        return mult(root);
    }
    //6
    float eval(BNode *p){
        if(!p->left && !p->right) return p->data;
        switch (p->data)
        {
        case 1 :
            return eval(p->left)+eval(p->right);
            break;
        
        case 2 :
        return eval(p->left)-eval(p->right);
            break;
        case 3 :
            return eval(p->left)*eval(p->right);
            break;
        case 4 :
            return eval(p->left)/eval(p->right);
        break;
        default:
            cout<<"operation error";
            break;
        }
    }
    float eval(){
        return eval(root);
    }
    //7
    BNode* find_from(int d,BNode *p){
        if(!p) return nullptr;
        if( p->data == d) return p;
        BNode *temp=find_from(d,p->left);
        return temp ? temp:find_from(d,p->right);
    }
    BNode* find(int d){
        return find_from(d,root);
    }
    //8
    int inf = numeric_limits<int>::max();
    int min_from(BNode* p){
        if(!p) return inf;
        int a1=min_from(p->left);
        int a2=min_from(p->right);
        int a3 = (a1<a2 ? a1 : a2);
        return (a3<p->data? a3 : p->data);
    }
    int min(){
        return min_from(root);
    }
    //DOPOL
    //1 &2
    BNode* copyFrom(BNode *p){
        if(!p) return nullptr;
        BNode *res = new BNode(p->data);
        res->left = copyFrom(p->left);
        res->right = copyFrom(p->right); 
    }
    BNode* copy(){
        return copyFrom(root);
    }
    BNode* UcopyFrom(BNode *p,BNode *pere){
        if(!p) return nullptr;
        BNode *res = new BNode(p->data);
        res->father = pere;
        res->left = UcopyFrom(p->left,res);
        res->right = UcopyFrom(p->right,res); 
    }
    BNode* Ucopy(){
        return UcopyFrom(root,nullptr);
    }
    //3
    int alt_sum_rec(BNode * p,bool isleft){
        if(!p) return 0;
        int sum = (isleft ? p->data:-p->data);  
        sum+= alt_sum_rec(p->left,true)+alt_sum_rec(p->right,false);
        return sum;
    }
    int alt_sum(){
        return alt_sum_rec(root,true) - root->data;
    }
    //4

    //DELETE
    void f_del(BNode *&p)
    {
        if (p == nullptr)
            return;
    
        f_del(p->left);
        f_del(p->right);
        delete p;
        p = nullptr;
    }
    //1
    void del0(BNode *&p)
    {
        if (p == nullptr)
            return;
        if (p->data == 0)
        {   
            f_del(p);
            return;
        }
        del0(p->left);
        del0(p->right);
    }
    
    //2
    void del_list(BNode *&p)
    {
        if (p == nullptr)
            return;
        if (p->left == nullptr && p->right == nullptr)
        {
            f_del(p);
            return;
        }
        del_list(p->left);
        del_list(p->right);
    }
    //3
    void enlarge(BNode *&p, int d)
    {
        if (p != nullptr)
        {
            enlarge(p->left, d);
            enlarge(p->right, d);
            return;
        }
        p = new BNode(d);
    }
    //4
    void del1(BNode *&p)
    {
        if (p == nullptr)
            return;
        if (p->data == 1)
        {
            f_del(p->left);
            BNode * temp = p;
            p = p->right;
            delete  temp;
            del1(p);
            return;
        }
        del1(p->right);
        del1(p->left);
    }
    //обход по глубину

    void profondeur (BNode * p)
    {
    stack <BNode *> s; // используем стек
    // в стеке хранятся указатели на узлы дерева
    BNode * t;
    if (p == nullptr) // если дерево пусто
        return;
    s.push(p); // кладем в стек указатель на узел
    while (!s.empty()) // пока стек не пуст
        {
        t = s.top(); // t - верхний элемент стека
        cout << t->data << endl;
        s.pop(); // выталкиваем его из стека
        if (t->left != nullptr) // если есть левый сын

            s.push(t->left); // кладем в стек
        if (t->right != nullptr) // аналогично правый

            s.push(t->right);
        }
    }
    // обход по ширину
    void largeur (BNode * p)
    {
    queue <BNode *> s; // используем стек
    // в стеке хранятся указатели на узлы дерева
    BNode * t;
    if (p == nullptr) // если дерево пусто
        return;
    s.push(p); // кладем в стек указатель на узел
    while (!s.empty()) // пока стек не пуст
    {
        t = s.front(); // t - верхний элемент стека
        cout << t->data << endl;
        s.pop(); // выталкиваем его из стека
        if (t->left != nullptr) // если есть левый сын

            s.push(t->left); // кладем в стек
        if (t->right != nullptr) // аналогично правый

            s.push(t->right);
    }
    }


};
int main(){
    return 0;
}

/* 
string leftTree(string chaine){
    int q=0 ;bool changed=0;
    int i;
    for (i=0;i<chaine.size();i++){
        if(chaine[i]=='(' ){
            q++;changed=1;
        }else{
            if(chaine[i]==')'){
                q--;changed=1;
            }
        }
        if(q==0 && changed ) break;
    }
    if(i==chaine.size()){
        int x=chaine.find_first_of(",");
        return chaine.substr(0,x-1);
    }
    return chaine.substr(0,i+1);

}
string rightTree(string chaine){
    int q=0 ;bool changed=0;
    int i;
    for (i=0;i<chaine.size();i++){
        cout<<i;
        if(chaine[i]=='(' ){
            q++;changed=1;
        }else{
            if(chaine[i]==')'){
                q--;changed=1;
            }
        }
        if(q==0 && changed ) break;
    }
    if(i==chaine.size()){
        int x=chaine.find_first_of(",");
        return chaine.substr(x+1,chaine.size()-x);
    }
    return chaine.substr(i+2,chaine.size()-i-1);

}
BNode* input(string chaine){
    
        string point=".";
        if (chaine == point) return nullptr;
        auto first_open = chaine.find_first_of("(");
        auto last_close = chaine.find_last_of(")");
        if(first_open==string::npos){
            cout<<chaine<<endl;
            int racine = stoi(chaine);
            BNode *root=new BNode(racine);
            return root;
        }else{
            cout<<chaine.substr(0,first_open)<<endl;
        int racine = stoi(chaine.substr(0,first_open));
        
        BNode *root=new BNode(racine);
        string chaine2 = chaine.substr(first_open+1,last_close-first_open);
        root->left= input(leftTree(chaine2));
        root->right = input(rightTree(chaine2));
        return root;
        }
        
    }
int main(){
    string s = "1(2,3)";
    BNode* a=input(s);
    f_print(a);
    return 0;
}
*/
