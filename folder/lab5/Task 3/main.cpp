#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

constexpr auto ALPHABET_SIZE = 26*2;
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

class LinkedHashMap {
private:
    struct map_node {
        map_node* next = nullptr;
        map_node* prev_added = nullptr;
        map_node* next_added = nullptr;
        string val;
        string key;
    };

    unsigned int heads_size = 10;
    struct map_node** heads = nullptr;
    struct map_node* last_added = nullptr;

public:
    LinkedHashMap(unsigned int heads_size) {
        this->heads_size = heads_size;
        heads = new struct map_node*[heads_size];
        for (int i = 0; i < heads_size; i++) {
            heads[i] = nullptr;
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

        if (heads[h] != nullptr) {
            struct map_node* ptr = heads[h];
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

                if (last_added != nullptr)
                    last_added->next_added = m;
                m->prev_added = last_added;
                last_added = m;

                ptr_prev->next = m;
            }
        } else {
            struct map_node* m = new map_node;
            m->val = val;
            m->key = key;

            if (last_added != nullptr)
                last_added->next_added = m;
            m->prev_added = last_added;
            last_added = m;

            heads[h] = m;
        }

    }

    string get(string key) {
        unsigned int h = index(hash(key));

        if (heads[h] != nullptr) {
            struct map_node* ptr = heads[h];

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

    string prev(string key) {
        unsigned int h = index(hash(key));

        if (heads[h] != nullptr) {
            struct map_node* ptr = heads[h];

            while (ptr != nullptr) {
                if (ptr->key == key && ptr->prev_added != nullptr) {
                    return ptr->prev_added->val;
                }
                ptr = ptr->next;
            }
            return "none";
        }
        return "none";
    }

    string next(string key) {
        unsigned int h = index(hash(key));

        if (heads[h] != nullptr) {
            struct map_node* ptr = heads[h];

            while (ptr != nullptr) {
                if (ptr->key == key && ptr->next_added != nullptr) {
                    return ptr->next_added->val;
                }
                ptr = ptr->next;
            }
            return "none";
        }
        return "none";
    }

    void del(string key) {
        unsigned int h = index(hash(key)); // get heads index

        if (heads[h] == nullptr) return; // if list empty return

        if (last_added->key == key) {
            last_added = last_added->prev_added;
        }

        if (heads[h]->key == key) { // if 1st elements key matches
            if (heads[h]->prev_added != nullptr) heads[h]->prev_added->next_added = heads[h]->next_added;
            if (heads[h]->next_added != nullptr) heads[h]->next_added->prev_added = heads[h]->prev_added;

            struct map_node* t = heads[h];
            heads[h] = heads[h]->next; // move next to heads
            delete t;
        } else { // not 1st elements key matches
            struct map_node *ptr_prev = heads[h];
            struct map_node *ptr_cur = ptr_prev->next;

            while (ptr_cur != nullptr) { // and go down the list and check values of elements starting from 2nd
                if (ptr_cur->key == key) { // if found matching key then
                    ptr_prev->next = ptr_cur->next; // drop element from list

                    if (ptr_cur->prev_added != nullptr) ptr_cur->prev_added->next_added = ptr_cur->next_added;
                    if (ptr_cur->next_added != nullptr) ptr_cur->next_added->prev_added = ptr_cur->prev_added;

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
            if (heads[i] != nullptr) {
                cout << i << ": ";

                struct map_node *ptr = heads[i];

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
    ifstream fin("linkedmap.in");
    freopen("linkedmap.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string s;
    LinkedHashMap map(1000000 + 33);

    while (getline(fin, s)) {
        istringstream ss(s);
        string command, key, val;
        ss >> command >> key;
//        cout << command << ' ' << key << '\n';
        if (command == "put") {
            ss >> val;
            map.put(key, val);
            //cout << command << ' ' << key << ' ' << val << endl;
        }
        else if (command == "get") {
            cout << map.get(key) << '\n';
            //cout << command << ' ' << key << endl;
        }
        else if (command == "prev") {
            cout << map.prev(key) << '\n';
            //cout << command << ' ' << key << endl;
        }
        else if (command == "next") {
            cout << map.next(key) << '\n';
//            cout << command << ' ' << key << endl;
        }
        else if (command == "delete") {
            map.del(key);
//            cout << command << ' ' << key << endl;
        }
    }

    //map.show();

    return 0;
}