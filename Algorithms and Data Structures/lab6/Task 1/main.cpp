#include <iostream>
#include <cmath>

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

    Node* find(long long key) {
        Node* ptr = root;

        while (ptr != nullptr) {
            if (key > ptr->key) {
                if (ptr->right != nullptr) {
                    ptr = ptr->right;
                } else {
                    return nullptr;
                }
            } else if (key < ptr->key) {
                if (ptr->left != nullptr) {
                    ptr = ptr->left;
                } else {
                    return nullptr;
                }
            } else if (key == ptr->key){
                return ptr;
            }
        }

        return nullptr;
    }

    Node* next(long long key) {
        Node* current = root;
        Node* successor = nullptr;

        while (current != nullptr) {
            if (current->key > key) {
                successor = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return successor;
    }
public:
    void insert(long long key) {
        auto z = new Node;
        z->key = key;
        Node* ptr = root;

        while (ptr != nullptr) {
            if (z->key > ptr->key) {
                if (ptr->right != nullptr) {
                    ptr = ptr->right;
                } else {
                    z->parent = ptr;
                    ptr->right = z;
                    break;
                }
            } else if (z->key < ptr->key) {
                if (ptr->left != nullptr) {
                    ptr = ptr->left;
                } else {
                    z->parent = ptr;
                    ptr->left = z;
                    break;
                }
            }
        }
    }

    void remove(long long key) {
        Node* ptr = find(key);

        if (ptr->left == nullptr && ptr->right == nullptr) {
            if (ptr->parent->left == ptr) {
                ptr->parent->left = nullptr;
            }
            if (ptr->parent->right == ptr) {
                ptr->parent->right = nullptr;
            }
            delete ptr;
            return;
        }

        if (ptr->left == nullptr || ptr->right == nullptr) {
            if (ptr->left == nullptr) {
                if (ptr->parent->left == ptr) {
                    ptr->parent->left = ptr->right;
                } else {
                    ptr->parent->right = ptr->right;
                }
                ptr->right->parent = ptr->parent;
            } else {
                if (ptr->parent->left == ptr) {
                    ptr->parent->left = ptr->left;
                } else {
                    ptr->parent->right = ptr->left;
                }
                ptr->left->parent = ptr->parent;
            }
            delete ptr;
            return;
        }

        Node* successor = next(key);
        ptr->key = successor->key;
        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
        } else {
            successor->parent->right = successor->right;
            if (successor->right != nullptr) {
                successor->right->parent = successor->parent;
            }
        }
        delete successor;
    }
};

struct array_node{
    long long val;
    int right;
    int left;
};

long long cnt(struct array_node* arr, int t) {
    if (arr[t].left == 0 && arr[t].right == 0) {
        return 1;
    }

    return 1 + max(cnt(arr, arr[t].left), cnt(arr, arr[t].right));
}

int main() {
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);

    int n;
    cin >> n;

    struct array_node array[n + 1];

    array[0].val = 0;
    array[0].left = 0;
    array[0].right = 0;

    for (int i = 1; i <= n; ++i) {
        int v,l,r;
        cin >> v >> l >> r;
        array[i].val = v;
        array[i].left = l;
        array[i].right = r;
    }

    long long height = 0;
    for (int i = 0; i < n; i++) {
        long long tmp = cnt(array, i);
        if (tmp > height) height = tmp;
    }
    cout << height;

    return 0;
}