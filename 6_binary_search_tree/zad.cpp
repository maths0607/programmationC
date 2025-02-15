#include <iostream>
#include <vector>
using namespace std;

template<class K, class T>
struct SNode
{
    K key;
    T data;
    string color = "blue";
    SNode<K, T>* left, * right; // указатели на сыновей
    SNode(K k, T d, SNode<K, T>* l = nullptr, SNode<K, T>* r = nullptr) :
    key(k), data(d), left(l), right(r) {} // конструктор

};
template<class K>
bool operation(K a, K b){
    return a<b;
}
template<class K>
bool operation2(K a, K b){
    return a>50;
}
template<class K, class T>
void f_print(SNode<K, T>* r, int d = 0) // d - смещение
{
    if (r == nullptr) return;
    f_print(r->right, d + 3);
    for (int i = 0; i < d; i++)
    cout << ' ';
    cout << r->key << "(" << r->data << ")" << endl;
    f_print(r->left, d + 3);
}
template<class K, class T>
struct STree
{
    SNode<K, T>* root; // корень дерева

    STree<K, T> (SNode<K, T>* p=nullptr) : root(p) {}
    // конструктор по указателю на узел
    void print() // метод печати
    {
        f_print(root); // вызывает рекурсивную функцию
        cout<<"--------------"<<endl;
    }

    //2
        //a
   static SNode<K,T>* findRecursive(SNode<K,T>* node, K key)  {
        if (!node || node->key == key) {
            return node;
        }
        if (operation(key,node->key) ) {
            return findRecursive(node->left, key);
        } else {
            return findRecursive(node->right, key);
        }
    }
    SNode<K,T>* find(K key)const{
        return findRecursive(root,key);
    }
        //b

    static SNode<K,T>* findIterative(SNode<K,T>*node,K key,string color)  {
        SNode<K,T>* current = node;
        while (current) {
            if (current->key == key && current->color == color ) {
                return current;
            }
            if (operation(key,current->key)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr; 
    }
    SNode<K,T>* findI(K key,string color = "blue")const{
        return findIterative(root,key,color);
    }
    //3
        //a
      void insertRecursive(SNode<K,T>* & node, K key, T value) {
        if (node == nullptr) {
            node=new SNode<K,T>(key, value);
            return;
        }
        if (operation(key,node->key)) {
            insertRecursive(node->left, key, value);
        } else if (operation(node->key,key)) {
             insertRecursive(node->right, key, value);
        } else {
            node->data = value;
            return;
        }
        
    }
    void insertR(K key,T value){
        insertRecursive(root, key, value);
    }

        //b
   void insertIterative(SNode<K,T>* node, K key, T & value) {
        if (node == nullptr) {
            
            node = new SNode<K,T>(key, value);
            return;
        }

        SNode<K,T>* current = node;
        SNode<K,T>* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (operation(key, current->key)) {
                current = current->left;
            } else if (operation(current->key,key)) {
                current = current->right;
            } else {
                
                current->data = value;
                return ;
            }
        }

        if (key < parent->key) {
            parent->left = new SNode<K,T>(key, value);
        } else {
            parent->right = new SNode<K,T>(key, value);
        }        

    }
    void insertI(K key,T value){
        insertIterative(root, key, value);
    }

    //DELETE
    //0

    SNode<K,T>* most_left_grand_child(SNode<K,T>* node){
        if(! node || !node->left){
            return node;
        }
        return most_left_grand_child(node->left);
    }
    SNode<K,T>* removeRecurcive(SNode<K,T>* node, K key) {
        if (node == nullptr) {
            return nullptr; 
        }

        if (operation(key , node->key)) {
            node->left = removeRecurcive(node->left, key);
        } else if (operation(node->key,key)) {
            node->right = removeRecurcive(node->right, key);
        } else {
            // Nœud trouvé
            if (node->left == nullptr) {
                SNode<K,T>* temp = node->right;
                delete node; 
                return temp; 
            } else if (node->right == nullptr) {
                SNode<K,T>* temp = node->left;
                delete node; 
                return temp; 
            }

            
            SNode<K,T>* successor = most_left_grand_child(node->right);
            node->key = successor->key; 
            node->data = successor->data; 
            node->right = removeRecurcive(node->right, successor->key); 
        }
        return node;
    }
    void removeR(K key){
        root=removeRecurcive(root,key);
    }
    
    SNode<K,T>* removeI(SNode<K,T>* root, K key) {
        SNode<K,T>* parent = nullptr;
        SNode<K,T>* current = root;

    // Trouver le nœud à supprimer
    while (current != nullptr && current->val != key) {
        parent = current;
        if (key < current->val) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Si le nœud n'existe pas, retourner l'arbre inchangé
    if (current == nullptr) {
        return root;
    }

    // Cas 1 : Nœud sans enfant (feuille)
    if (current->left == nullptr && current->right == nullptr) {
        if (parent == nullptr) {  // Si c'est la racine
            delete current;  // Libérer la mémoire
            return nullptr;
        }
        if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;  // Libérer la mémoire
    }
    // Cas 2 : Nœud avec un enfant
    else if (current->left == nullptr || current->right == nullptr) {
        SNode<K,T>* child = (current->left != nullptr) ? current->left : current->right;
        if (parent == nullptr) {  // Si c'est la racine
            delete current;  // Libérer la mémoire
            return child;
        }
        if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;  // Libérer la mémoire
    }
    // Cas 3 : Nœud avec deux enfants
    else {
        // Trouver le successeur in-order (le plus petit dans le sous-arbre droit)
        SNode<K,T>* successorParent = current;
        SNode<K,T>* successor = current->right;

        while (successor && successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // Copier la valeur du successeur dans le nœud courant
        current->data = successor->data;
        current->key = successor->key;

        // Supprimer le successeur
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        delete successor;  // Libérer la mémoire
    }

    return root;
}
//DOPO
//1
    void findAdjacentKeysRec( K key, SNode<K,T>*& lower, SNode<K,T>*& upper) {
        lower = nullptr;
        upper = nullptr;

        SNode<K,T>* node=root;
        while (node != nullptr) {
            if (key < node->val) {
                upper = node; 
                node = node->left;  
            } else if (key > node->val) {
                lower = node; 
                node = node->right;  
            } else {
                
                lower = node;
                upper = node;
                return;
            }
        }
    }
    void findAdjacentKeys(int key, SNode<K,T>*& lower, SNode<K,T>*& upper) {
        lower = nullptr;
        upper = nullptr;
        findAdjacentKeysRec(root, key, lower, upper);
    }
//2
void toVectorRec(SNode<K,T>* node, vector<SNode<K,T>*>& vec) 
    {
        if (node == nullptr) return;

        // Parcours infixe : gauche -> racine -> droite
        toVectorRec(node->left, vec);
        vec.push_back(node->val);
        toVectorRec(node->right, vec);
    }
    void fix(){
        vector<SNode<K,T>*> allN;
        toVectorRec(root,allN);
        bool change =false;
        for(auto n : allN){
            if(!n->left){
            vector<SNode<K,T>*> nleft;
            toVectorRec(n->left,nleft);
            for(auto el : nleft){
                if (el.key >= n.key){
                    change = true;
                    removeI(el.key);
                    insertI(el.key);
                    break;
                }
            }
            }
            if(!n->right){
            vector<SNode<K,T>*> nright;
            toVectorRec(n->right,nright);
            for(auto el : nright){
                if (el.key <= n.key){
                    change = true;
                    removeI(el.key);
                    insertI(el.key);
                    break;
                }
            }
            }
            if(change) break;
            
        }
        if(change) fix();

    }
    //3
    SNode<K,T>* parent(SNode<K,T>* node, K key) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return nullptr;  
        }

        if ((node->left != nullptr && node->left->val == key) || 
            (node->right != nullptr && node->right->val == key)) {
            return node;          }

        
        if (key < node->val) {
            return findParentRec(node->left, key);
        } else {
            return findParentRec(node->right, key);
        }
    }
    SNode<K,T>* nextNode(SNode<K,T>* node) {
        if (node->right != nullptr) {
            return most_left_grand_child(node->right);
        }

        SNode<K,T>* parent = parent(node);
        while (parent != nullptr && node == parent->right) {
            node = parent;
            parent = parent(parent);
        }
        return parent;
    }
    //4
    void removegreat50(){
        SNode<K,T>* up, down,toDel;
        findAdjacentKeys(50,down,toDel);
        
        while(toDel)
            removeI(toDel->key);
            
            toDel = nextNode(toDel);
        }
    //5
    bool isValidBSTRec(SNode<K,T>* node, K minVal, K maxVal) {
        if (node == nullptr) {
            return true; 
        }
        if (node->key<= minVal ||node->key >= maxVal) {
            return false;  
        }

        return isValidBSTRec(node->left, minVal, node->val) &&
               isValidBSTRec(node->right, node->val, maxVal);
    }
    bool isValidBST() {
        return isValidBSTRec(root,numeric_limits<K>::min(),numeric_limits<K>::max());
    }

    
    
};



int main()
{
    SNode<int, int>* p9 = new SNode<int, int>(13, 130),
    * p8 = new SNode<int, int>(7, 70),
    * p7 = new SNode<int, int>(4, 40),
    * p6 = new SNode<int, int>(14, 140, p9),
    * p5 = new SNode<int, int>(6, 60, p7, p8),
    * p4 = new SNode<int, int>(1, 10),
    * p3 = new SNode<int, int>(10, 100, nullptr, p6),
    * p2 = new SNode<int, int>(3, 30, p4, p5),
    * p1 = new SNode<int, int>(8, 80, p2, p3);
    STree<int, int> t(p1);
    t.print();

    t.insertR(2,7);
    t.insertI(25,78);
    t.print();

    t.removeR(6);
    t.print();
    return EXIT_SUCCESS;
}