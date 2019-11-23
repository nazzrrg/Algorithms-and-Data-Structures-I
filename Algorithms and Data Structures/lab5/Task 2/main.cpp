#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

constexpr double pow(int x, int y) {
    double p = 1;
    for (int i = 0; i < y; i++) p*=x;
    return p;
}
constexpr double P_ARRAY[20] = {pow(129,0),pow(129,1), pow(129,2),
                                pow(129,3), pow(129,4), pow(129,5),
                                pow(129,6),pow(129,7),pow(129,8),
                                pow(129,9),pow(129,10),pow(129,11),
                                pow(129,12),pow(129,13),pow(129,14),
                                pow(129,15),pow(129,16),pow(129,17),
                                pow(129,18),pow(129,19)};

using namespace std;

class HashMap {
private:
    struct map_node {
        map_node* next = nullptr;
        string val;
        string key;
        bool exists = true;
    };

    unsigned int heads_size = 10;
    struct map_node* heads;

public:
    HashMap(unsigned int heads_size) {
        this->heads_size = heads_size;
        heads = new struct map_node[heads_size];
        for (int i = 0; i < heads_size; i++) {
            heads[i].exists = false;
        }
    }

    //~hash_set() {}

    unsigned int hash(const string& key) {
        unsigned int hash = 0;
        unsigned int p = 129;
        size_t i = 0;

        while (key[i] != '\0') {
            hash += (unsigned int)((key[i] - 'a') * P_ARRAY[i]);
            i++;
        }

        return hash;
    }

    unsigned int index(unsigned int hash) {
        return hash % heads_size;
    }

    void put(const string& key, const string& val) {
        unsigned int h = index(hash(key));

        if (heads[h].exists) {
            struct map_node* ptr = &heads[h];
            struct map_node* ptr_prev = nullptr;

            while (ptr != nullptr) {
                if (ptr->key == key) {
                    ptr->val = val;
                    break;
                }
                ptr_prev = ptr;
                ptr = ptr->next;
            }

            if (ptr == nullptr) {
                struct map_node* m = new map_node;
                m->val = val;
                m->key = key;
                ptr_prev->next = m;
            }
        } else {
            struct map_node* m = new map_node;
            m->val = val;
            m->key = key;
            heads[h] = *m;
        }

    }

    string get(string key) {
        unsigned int h = index(hash(key));

        if (heads[h].exists) {
            struct map_node* ptr = &heads[h];

            while (ptr != nullptr) {
                if (ptr->key == key) {
                    return ptr->val;
                }
                ptr = ptr->next;
            }

            return "none";
        }

        return "none";
    }

    void del(string key) {
        unsigned int h = index(hash(key)); // get heads index

        if (heads[h].next == nullptr && heads[h].key == key) { // if only 1 element at that hash and its key matches
            heads[h].exists = false; // mark it non-existent
        } else if (heads[h].next != nullptr && heads[h].key == key) { // if theres > 1 element in list and heads key matches
            heads[h] = *heads[h].next; // move next to heads
        } else { // if >1 element in list and sought isnt 1st
            struct map_node *ptr_prev = &heads[h];
            struct map_node *ptr_cur = ptr_prev->next;

            while (ptr_cur != nullptr) { // and go down the list and check values of elements
                    if (ptr_cur->key == key) { // if found matching key then
                        ptr_prev->next = ptr_cur->next; // drop element from list
                        delete ptr_cur; // delete it
                        return;
                    }

                    ptr_prev = ptr_cur;// move pointers
                    ptr_cur = ptr_cur->next;
                }
        }
    }

    void show() {
        for (int i = 0; i < heads_size; i++) {
            if (heads[i].exists) {
                cout << i << ": ";

                struct map_node *ptr = &heads[i];

                while (ptr != nullptr) { // go down the list and check values of elements in list
                    cout <<"(" << ptr->key<<", " << ptr->val << "); ";
                    ptr = ptr->next; // go to next element
                }
                cout << "\n";
            }
        }
    }
};

int main() {
    ifstream fin("map.in");
    freopen("map.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    HashMap map(1000000 + 33);

    while (getline(fin, s)) {
        istringstream ss(s);
        string buf, key, val;
        switch (s[0]) {
            case 'p': {
                ss >> buf >> key >> val;
                map.put(key, val);
                break;
            }
            case 'd': {
                ss >> buf >> key;
                map.del(key);
                break;
            }
            case 'g': {
                ss >> buf >> key;
                cout << map.get(key) << '\n';
                break;
            }
        }
    }

    //map.show();

    return 0;
}