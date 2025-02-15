#include <iostream>
using namespace std;


class Node {
public:
    int key;
    int data;
    Node* parent;
    Node* left;
    Node* right;
    int height;

    Node(int k,int d,Node* p=nullptr,Node * l=nullptr,Node * r=nullptr,int h=0) {
        key=k;
        data = d;
        parent=p;
        left=l;
        right = r;
        height = h; 
        correct_h();
    }
    void correct_h(){
        height = max(left?left->height:0,right?right->height:0);
    }
    int defect_h(){
        return left->height-right->height;
    }
    void print() {
    cout << "Node: " << this << ", Key: " << key << ", Data: " << key 
            << ", Height: " << height << ", Parent: " << parent << endl;
    }
};
void f_print(Node* r, int indent = 1) 
{
    if (r == nullptr) return;
    f_print(r->left, indent + 3);
    for (int i = 0; i < indent; ++i)
        cout << ' ';
    cout << "(" << r->key << ", " << r->data << ")" << endl;
    f_print(r->right, indent + 3);
}


class AVLTree {
public:
    Node* root;
    AVLTree(Node * r=nullptr) {
        root = r;
    }
    Node* copy(Node* node){
        if(!node) return nullptr;
        Node* newroot = new Node(node->key,node->data);
        newroot->left = copy(node->left);
        newroot->right = copy(node->right);
        if(newroot->left) newroot->left->parent = newroot;
        if(newroot->right) newroot->right->parent = newroot;
        newroot->correct_h();
        return newroot;

    }
    void destroy(Node* node){
        if(node){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    AVLTree& operator=(const AVLTree& other){
        if(this != &other){
            destroy(root);
            root = copy(other.root);
        }
        return *this;
    }
    ~AVLTree(){
        destroy(root);
    }
    //2
    void print(){
        f_print(root);
    }
    //3
    void rotateLeft(Node* node){
        Node *rightchild = node-> right;
        if (rightchild ==nullptr) return ;
        node->right = rightchild->left;
        rightchild->left = node;
        node = rightchild;
        node->correct_h();
        rightchild->correct_h();
    }
    void rotateRight(Node* node){
        Node *leftchild = node->left;
        if (leftchild ==nullptr) return ;
        node->left = leftchild->right;
        leftchild->right = node;
        node = leftchild;
        node->correct_h();
        leftchild->correct_h();
    }





    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Fonction pour obtenir le facteur d'équilibre d'un nœud
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Rotation à droite
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Effectuer la rotation
        x->right = y;
        y->left = T2;

        // Mettre à jour les hauteurs
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        // Retourner le nouveau racine
        return x;
    }

    // Rotation à gauche
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Effectuer la rotation
        y->left = x;
        x->right = T2;

        // Mettre à jour les hauteurs
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        // Retourner le nouveau racine
        return y;
    }

    // Fonction d'insertion
    Node* insert(Node* node, int key) {
        // 1. Effectuer l'insertion normale d'un BST
        if (node == nullptr) {
            return new Node(key);
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            // Les clés dupliquées ne sont pas autorisées
            return node;
        }

        // 2. Mettre à jour la hauteur de l'ancêtre nœud
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // 3. Obtenir le facteur d'équilibre
        int balance = getBalance(node);

        // 4. Si le nœud devient déséquilibré, alors il y a 4 cas

        // Cas gauche gauche
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }

        // Cas droit droit
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }

        // Cas gauche droit
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Cas droit gauche
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Retourner le nœud (inchangé)
        return node;
    }

    // Fonction pour afficher l'arbre en ordre
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->key << " ";
            inOrder(node->right);
        }
    }

    // Fonction publique pour insérer une clé
    void insert(int key) {
        root = insert(root, key);
    }

    // Fonction publique pour afficher l'arbre
    void inOrder() {
        inOrder(root);
    }
};

// Exemple d'utilisation
int main() {
    AVLTree tree;

    // Insertion de clés
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert( 50);
    tree.insert(25);

    // Affichage de l'arbre en ordre
    cout << "Affichage de l'arbre en ordre: ";
    tree.inOrder();
    cout << endl;

    return 0;
}