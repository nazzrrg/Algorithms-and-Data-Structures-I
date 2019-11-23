#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class hash_set {
private:
    struct list_node {
        list_node* next = nullptr;
        int val;
        bool exists = true;
    };

    unsigned int heads_size = 10;
    struct list_node* heads;



public:
    hash_set(unsigned int heads_size) {
        this->heads_size = heads_size;
        heads = new struct list_node[heads_size];
        for (int i = 0; i < heads_size; i++) {
            heads[i].exists = false;
        }
    }

    int hash(int x) {
        return x;
    }

    int index(int hash) {
        return hash % heads_size;
    }

    bool exists(int x) {
        int h = index(hash(x)); // get heads index
        if (heads[h].exists) { // if there is an element with such hash check for element with such hash AND value
            struct list_node *ptr = &heads[h]; // set ptr to point at heads "initial" element

            while (ptr != nullptr) { // go down the list and check values of elements in list
                if (ptr->val == x) { // if match then found and return true
                    return true;
                }

                ptr = ptr->next; // go to next element
            }
        }
        return false;
    }

    void ins(int x) {
        int h = index(hash(x)); // get heads index
        if (!heads[h].exists) { // if no element with such hash exists
            struct list_node* p = new list_node; // create new list node
            p->val = x; // assign its value to x
            heads[h] = *p; //assign heads element this node (copy)
            delete p;//??????????????????????????????????? delete copy
        } else {// if there is an element with such hash
            if (!exists(x)) { // check for element with such hash AND value. If none exist
                struct list_node* p = new list_node; // create new list node
                p->val = x; // assign its value to x

                struct list_node* ptr = &heads[h]; // set ptr to point at heads "initial" element

                while (ptr->next != nullptr) {
                    ptr = ptr->next; // go down the list to the last element
                }

                // ptr now points to the last element of list at heads[h]
                ptr->next = p; // add element to list
            }
        }
    }

    void del(int x) {
        int h = index(hash(x)); // get heads index
        if (exists(x)) { // if element x exists in set delete it

            if (heads[h].next == nullptr && heads[h].val == x) { // if there is only 1 element in list and its value is x
                heads[h].exists = false; // mark it non existent and return
            } else if (heads[h].next != nullptr && heads[h].val == x) { // if there is > 1 elements and heads value is x
                heads[h] = *heads[h].next; //
            } else {
                // if there is more than 1 elements in list and its 1st element is not being sought then
                struct list_node *ptr_prev = &heads[h]; // get pointers of 2 elements in that list - 0
                struct list_node *ptr_cur = ptr_prev->next; // - 1
                while (ptr_cur != nullptr) { // and go down the list and check values of elements in list
                    if (ptr_cur->val == x) { // if found then
                        ptr_prev->next = ptr_cur->next; // drop element from list
                        delete ptr_cur; // delete it
                        return;
                    }

                    ptr_prev = ptr_cur;// move pointers
                    ptr_cur = ptr_cur->next;
                }
            }
        }
    }

    void show() {
        for (int i = 0; i < heads_size; i++) {
            if (heads[i].exists) {
                cout << i << ": ";

                struct list_node *ptr = &heads[i];

                while (ptr != nullptr) { // go down the list and check values of elements in list
                    cout << ptr->val << ", ";
                    ptr = ptr->next; // go to next element
                }
                cout << "\n";
            }
        }
    }
};

int main() {
    ifstream fin("set.in");
    freopen("set.out", "w", stdout);

    string s;
    hash_set set(100000);

    while (getline(fin, s)) {
        switch (s[0]) {
            case 'i': {
                s = s.erase(0, 7);
                int x = stoi(s);
//                cout << "insert " << x << endl;
                set.ins(x);
//                cout << '\n';
                break;
            }
            case 'e': {
                s = s.erase(0, 7);
                int x = stoi(s);
//                cout << "exists " << x <<": ";
                if (set.exists(x)){
                    cout << "true" << "\n";
                } else {
                    cout << "false" << "\n";
                }
//                cout << '\n';
                break;
            }
            case 'd': {
                s = s.erase(0, 7);
                int x = stoi(s);
                //cout << "delete " << x << endl;
                set.del(x);
                //cout << '\n';
                break;
            }
        }
    }

    //set.show();

    return 0;
}