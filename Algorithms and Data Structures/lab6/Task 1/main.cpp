#include <iostream>

using namespace std;

class BinaryTree {
private:
    struct Node {
        long long key = 0;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root;
public:
    void insert(long long key) {
        auto z = new Node;
        z->key = key;

        while (root != nullptr) {
            if (z->key > root->key) {
                if (root->right != nullptr) {
                    root = root->right;
                } else {
                    z->parent = root;
                    root->right = z;
                    break;
                }
            } else if (z->key < root->key) {
                if (root->left != nullptr) {
                    root = root->left;
                } else {
                    z->parent = root;
                    root->left = z;
                    break;
                }
            }
        }
    }
};

int main() {
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);



    return 0;
}