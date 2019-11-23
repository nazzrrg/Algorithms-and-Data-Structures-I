#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

constexpr double pow(int x, int y) {
    double p = 1;
    for (int i = 0; i < y; i++) p*=x;
    return p;
}

constexpr double P_ARRAY[20] = {pow(37,0),pow(37,1), pow(37,2),
                                pow(37,3), pow(37,4), pow(37,5),
                                pow(37,6),pow(37,7),pow(37,8),
                                pow(37,9),pow(37,10),pow(37,11),
                                pow(37,12),pow(37,13),pow(37,14),
                                pow(37,15),pow(37,16),pow(37,17),
                                pow(37,18),pow(37,19)};

using namespace std;

unsigned int _hash(const string& key) {
    unsigned int hash = 0;
    unsigned int i = 0;

    while (key[i] != '\0') {
        hash += (unsigned int)((tolower(key[i]) - 'a' + 1) * P_ARRAY[i]);
        hash %= 107;
        i++;
    }

    return hash;
}

class LinkedHashSet {
private:
    struct list_node {
//        list_node* next = nullptr;
        list_node* prev_added = nullptr;
        list_node* next_added = nullptr;
        string val;
    };

    unsigned int heads_size = 107;
//    struct list_node** heads;
    list<list_node>* heads;
    list_node* last_added = nullptr;
    unsigned int size = 0;

public:
    LinkedHashSet() {
        heads = new list<list_node>[heads_size];
/*        heads = new struct list_node*[heads_size];
        for (int i = 0; i < heads_size; i++) {
            heads[i] = nullptr;
        }*/
    }

    unsigned int index(unsigned int hash) {
        return hash % heads_size;
    }

    void ins(const string& val) {
        unsigned int h = index(_hash(val)); // get heads index

        for(const auto& i : heads[h]){
            if (i.val == val) return;
        }

        list_node p;
        p.val = val;
        p.next_added = nullptr;
        p.prev_added = last_added;

        heads[h].push_back(p);

        if (last_added != nullptr) last_added->next_added = &heads[h].back();
//        p.prev_added = last_added;
        last_added = &heads[h].back();
//        cout << "added pair "<< last_added->val << endl;
        size++;
     /*   if (heads[h] == nullptr) {
            list_node* p = new list_node; // create new list node
            size++;
            p->val = val; // assign its value to x
            heads[h] = p; //assign heads element this node

            if (last_added != nullptr) last_added->next_added = p;
            p->prev_added = last_added;
            last_added = p;

            return;
        }

        struct list_node *ptr = heads[h];

        while (ptr->next != nullptr) {
            if (ptr->val == val) {
                return;
            }
            ptr = ptr->next;
        }

        if (ptr->val == val) {
            return;
        }

        list_node *p = new list_node;
        size++;
        p->val = val;

        if (last_added != nullptr) last_added->next = p;
        p->prev_added = last_added;
        last_added = p;

        ptr->next = p;*/
    }

    void del(const string& val) {
        unsigned int h = index(_hash(val));

        for (auto i = heads[h].begin(); i != heads[h].end(); i++){
            if (i->val == val) {
                if (i->prev_added != nullptr) i->prev_added->next_added = i->next_added;
                if (i->next_added != nullptr) i->next_added->prev_added = i->prev_added;
                if (i->val == last_added->val) last_added = i->prev_added;

                heads[h].erase(i);

                size--;

                return;
            }
        }
        /*struct list_node *ptr_prev = nullptr;
        struct list_node *ptr_cur = heads[h];

        if (last_added->val == x) last_added = last_added->prev_added;

        while (ptr_cur != nullptr) { // and go down the list and check values of elements in list
            if (ptr_cur->val == x) { // if found then
                if (ptr_prev != nullptr) ptr_prev->next = ptr_cur->next; // drop element from list
                if (heads[h] == ptr_cur) heads[h] = ptr_cur->next;

                if (ptr_cur->prev_added != nullptr) ptr_cur->prev_added->next_added = ptr_cur->next_added;
                if (ptr_cur->next_added != nullptr) ptr_cur->next_added->prev_added = ptr_cur->prev_added;

                delete ptr_cur; // delete it
                size--;
                return;
            }

            ptr_prev = ptr_cur;// move pointers
            ptr_cur = ptr_cur->next;
        }*/
    }

    void delall() {
        last_added = nullptr;
        delete[] heads;
        heads = new list<list_node>[heads_size];
        size = 0;
    }

    void show() {
//        string result = to_string(size) + " ";
        cout << size << ' ';

        list_node *ptr = last_added;

        while (ptr != nullptr) {
//            result = result + ptr->val + " ";
            cout << ptr->val << ' ';
            ptr = ptr->prev_added;
        }
//        for (auto i = 0; i < heads_size; i++) {
//            for (auto j : heads[i]) {
//                result = result + j.val + ' ';
//            }
//        }

        cout << "\n";
//        return result;
    }

};


class MultiHashMap {
private:
    struct map_node {
//        map_node* next = nullptr;
//        map_node* prev = nullptr;
        string key;
        LinkedHashSet* values{};
    };

    unsigned int heads_size = 10007;
//    struct map_node** heads;
    list<map_node>* heads;
public:
    MultiHashMap() {
        heads = new list<map_node>[heads_size];
//        heads = new struct map_node*[heads_size];
//        for (int i = 0; i < heads_size; i++) {
//            heads[i] = nullptr;
//        }
    }

    unsigned int index(unsigned int hash) {
        return hash % heads_size;
    }

    void put(const string& key, const string& val) {
        unsigned int h = index(_hash(key));

        for (auto i : heads[h]) {
            if (i.key == key) {
                i.values->ins(val);
                return;
            }
        }

        map_node m;
        m.key = key;
        m.values = new LinkedHashSet();
        m.values->ins(val);

        heads[h].push_back(m);
        /*if (heads[h] == nullptr) {
            auto *m = new map_node;
            m->values = new LinkedHashSet;
            m->values->ins(val);
            m->key = key;
            heads[h] = m;
            return;
        }

        struct map_node *ptr = heads[h];
        struct map_node *ptr_prev = nullptr;

        while (ptr != nullptr) {
            if (ptr->key == key) {
                ptr->values->ins(val);
                return;
            }

            ptr_prev = ptr;
            ptr = ptr->next;
        }

        auto *m = new map_node;
        m->values = new LinkedHashSet();
        m->values->ins(val);
        m->key = key;
        m->prev = ptr_prev;
        ptr_prev->next = m;*/
    }

    void get(const string& key) {
        unsigned int h = index(_hash(key));

        for (auto i : heads[h]) {
            if (i.key == key) {
                i.values->show();
                return;
            }
        }

        cout << "0" << '\n';

        /*struct map_node *ptr = heads[h];

        while (ptr != nullptr) {
            if (ptr->key == key) {
                ptr->values->show();
                return;
            }
            ptr = ptr->next;
        }
        cout << 0 << '\n';*/
    }

    void del(const string& key, const string& val) {
        unsigned int h = index(_hash(key)); // get heads index

        for (auto &i : heads[h]) {
            if (i.key == key) {
                i.values->del(val);
            }
        }
    /*
        struct map_node *ptr = heads[h];

        while (ptr != nullptr) {
            if (ptr->key == key) {
                ptr->values->del(val);
//                if (ptr->values->size == 0) {
//                    if (ptr->prev != nullptr) ptr->prev->next = ptr->next;
//                    if (ptr->next != nullptr) ptr->next->prev = ptr->prev;
//                    if (ptr == heads[h]) heads[h] = ptr->next;
//                    delete ptr;
//                }
                return;
            }
            ptr = ptr->next;
        }*/
    }

    void delall(const string& key) {
        unsigned int h = index(_hash(key)); // get heads index

        for (auto i : heads[h]) {
            if (i.key == key) {
                i.values->delall();
            }
        }
        /*struct map_node *ptr = heads[h];

        while (ptr != nullptr) {
            if (ptr->key == key) {
                if (ptr->prev != nullptr) ptr->prev->next = ptr->next;
                if (ptr->next != nullptr) ptr->next->prev = ptr->prev;
                if (ptr == heads[h]) heads[h] = ptr->next;
//                ptr->values->cleanup();
                delete ptr;
            }
            ptr = ptr->next;
        }*/
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ifstream fin("multimap.in");
    freopen("multimap.out", "w", stdout);

    string s;
    MultiHashMap map;

    while (getline(fin, s)) {
        istringstream ss(s);
        string command, key, val;
        ss >> command >> key;

        if (command == "put") {
            ss >> val;
            map.put(key, val);
        }
        else if (command == "get") {
            map.get(key);
        }
        else if (command == "deleteall") {
            map.delall(key);
        }
        else if (command == "delete") {
            ss >> val;
            map.del(key, val);
        }
    }

    //map.show();

    return 0;
}