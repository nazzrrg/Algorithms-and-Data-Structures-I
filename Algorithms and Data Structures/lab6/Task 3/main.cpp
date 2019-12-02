#include <iostream>
//#include <cmath>
//#include <vector>
#include <string>

using namespace std;

class BinarySearchTree {
public:
    typedef struct Node {
        long long key = 0;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    Node* root;

    BinarySearchTree () {
        root = nullptr;
    }

    Node* search(Node* ptr, const long long& key) {
        if (ptr == nullptr || ptr->key == key) {
            return ptr;
        }
        if (key < ptr->key) {
            return search(ptr->left, key);
        } else {
            return search(ptr->right, key);
        }
    }

    Node* find(const long long& key) {
        return search(root, key);
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

    Node* prev(long long key) {
        Node* current = root;
        Node* predecessor = nullptr;

        while (current != nullptr) {
            if (current->key >= key) {
                current = current->left;
            } else {
                predecessor = current;
                current = current->right;
            }
        }

        return predecessor;
    }

    void insert(long long key) {
        auto z = new Node;
        z->key = key;
        Node* ptr = root;

        while (ptr != nullptr) {
            if (key == ptr->key) {
                return;
            }
            if (key > ptr->key) {
                if (ptr->right != nullptr) {
                    ptr = ptr->right;
                } else {
                    z->parent = ptr;
                    ptr->right = z;
                    return;
                }
            } else if (key < ptr->key) {
                if (ptr->left != nullptr) {
                    ptr = ptr->left;
                } else {
                    z->parent = ptr;
                    ptr->left = z;
                    return;
                }
            }
        }

        root = z;
   }

    void remove(long long key) {
        Node* ptr = find(key);

        if (ptr == nullptr) {
            return;
        }

        if (ptr == root) {
            if (ptr->left == nullptr && ptr->right == nullptr) {
                root = nullptr;
                delete ptr;
                return;
            }

            if (ptr->left == nullptr || ptr->right == nullptr) {
                if (ptr->left == nullptr) {
                    root = ptr->right;
                } else {
                    root = ptr->left;
                }
                delete ptr;
                return;
            }
        }

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

int main () {
    freopen("bstsimple.in", "r", stdin);
    freopen("bstsimple.out", "w", stdout);

    string s;
    int val;

    BinarySearchTree tree{};

    while (cin >> s >> val) {
        if (s == "insert") {
            tree.insert(val);
        }
        if (s == "delete") {
            tree.remove(val);
        }
        if (s == "exists") {
            auto result = tree.find(val);
            if (result == nullptr) {
                cout << "false";
            } else {
                cout << "true";
            }
            cout << '\n';
        }
        if (s == "next") {
            auto result = tree.next(val);
            if (result == nullptr) {
                cout << "none";
            } else {
                cout << result->key;
            }
            cout << '\n';
        }
        if (s == "prev") {
            auto result = tree.prev(val);
            if (result == nullptr) {
                cout << "none";
            } else {
                cout << result->key;
            }
            cout << '\n';
        }
    }

    return 0;
}
/*
insert -3
insert 7
insert 2
delete -5
delete -3
next -6

insert 2
insert 5
insert 3
exists 2
exists 4
next 4
prev 4
delete 5
next 4
prev 4
 */