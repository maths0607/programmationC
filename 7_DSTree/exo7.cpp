#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;
class Node {
public:
    int key;
    int count;
    Node* left;
    Node* right;

    Node(int value) : key(value), count(1), left(nullptr), right(nullptr) {}
};
int digit(int x, int n)
{
    return (x >> n) & 1;
}

class DSTree {
public:
    Node* root;

    DSTree() : root(nullptr) {}

    void insert(int key) {
        root = insertRec(root, key,0);
    }

    void printCounts() {
        printCountsRec(root);
    }

private:
    Node* insertRec(Node* node, int key,int pos) {
        if (node == nullptr) {
            return new Node(key);
        }
        if (key == node->key) {
            node->count++; 
        } else if (digit(key,pos)) {
            node->right = insertRec(node->right, key,pos+1);
        } else {
            node->left = insertRec(node->left, key,pos+1);
        }
        return node;
    }

    void printCountsRec(Node* node) {
        if (node != nullptr) {
            printCountsRec(node->left);
            cout << "nombre " << node->key << ", recontre : " << node->count << " fois" << std::endl;
            printCountsRec(node->right);
        }
    }
};

int main() {
    string filename;
    cout << "Вnom du fichier ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "fichier non trouver" << endl;
        return 1;
    }

    DSTree tree;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        int number;
        while (iss >> number) {
            tree.insert(number);
        }
    }

    file.close();

    cout << "Tableau " << endl;
    tree.printCounts();

    return 0;
}
