#include <iostream>
using namespace std;
template<class T>
struct ANode
{

    T data;
    ANode<T> *down, *right;
    ANode(T dd, ANode<T> *d = nullptr, ANode<T> *r = nullptr) :
    data(dd), down(d), right(r) {}

};
template<class T>
struct ATree
{
    ANode <T> * root;
    ATree(ANode<T>*p) : root(p){}
    void print()
    {
       f_print(root);
    }
    //1.
    int count (ANode<T> *p)
    {
        int c = 0;
        if (p == nullptr) return c;
        p = p->down;
        while (p != nullptr){

            c++;
            p = p->right;
        }
    return c;
    }
    int count_grandchild(){
        if(!root) return 0;
        int res = 0;
        ANode<T> current = root->down;
        while(current){
            res+=count(current);
            current = current->right;
        }
        return res;

    }
    //2.
    ANode<T>* first_that_isd1d2( T d1, T d2){
        if(!root) return nullptr;
        ANode<T> *child, *grandchild;
        child = root->down;
        while(child){
            if (child->data == d1){
                grandchild=child->down;
                while(grandchild){
                    if(grandchild->data == d2) return child;
                    grandchild=grandchild->right;
                }
            }
            child=child->right;
        }
        cout << "no such node" << endl;
        return child;
    }
    //3.
    ANode<T> *find_seq(ANode<T> *p, T *seq, int size, int i)
    {
        ANode<T> *temp, *t1;
        temp = p->down;
        while(temp != nullptr)
        {
            if (temp->data == seq[i])
            {
                if (size  > i + 1)
                {
                    t1 = find_seq(temp, seq, size, i + 1);
                    if (t1 != nullptr) return t1;
                } else return temp;
            }
            temp = temp->right;
        }
        return nullptr;
    }

    ANode<T> *find_sequence(T *seq, int size)
    {
        ANode<T> *t, *temp;
        t = root->down;
        while (t != nullptr)
        {
            if (t->data == seq[0])
            {
                if (size > 1)
                {
                    temp = find_seq(t, seq, size, 1);
                    if (temp != nullptr)
                        return temp;
                } else return t;                
            }
            t = t->right;
        }
        return nullptr;
    }
    //4
    void del_children()
    {   
        if(!root ) return;
        ANode<T> *child,*lastChild,*temp ;
        child=root->down;
        root->down=nullptr;
        while(child){
            if(child->down){        
              
                if(!root->down){
                    lastChild= child->down;
                    root->down = lastChild;
                }else{
                    lastChild->right=child->down;
                    lastChild=lastChild->right;
                }
                while(lastChild->right){
                    lastChild=lastChild->right;
                }
            }
            temp = child;
            child = child->right;
            delete temp;
        }
    }   

};
int main()
{
    ANode <int> * p10 = new ANode <int>(10),
    *p9 = new ANode <int>(9, nullptr, p10),
    *p8 = new ANode <int>(8),
    *p7 = new ANode <int>(7),
    *p11= new ANode <int>(11),
    *p6 = new ANode <int>(6, nullptr, p7),
    *p5 = new ANode <int>(5, p11, p6),
    *p4 = new ANode <int>(4, p9),
    *p3 = new ANode <int>(3, p8, p4),
    *p2 = new ANode <int>(2, p5, p3),
    *p1 = new ANode <int>(1, p2);
    ATree<int> t(p1);
    t.print();
    t.del_children();
    t.print();
    return EXIT_SUCCESS;
}
template<class T>
void f_print(ANode<T> *r, int d = 0) // d - смещение
{
if (r == nullptr) return;

for(int i = 0; i<d; i++) cout << ' ';

cout <<r->data << endl;

f_print(r->down,d + 3);
f_print(r->right,d);
}
