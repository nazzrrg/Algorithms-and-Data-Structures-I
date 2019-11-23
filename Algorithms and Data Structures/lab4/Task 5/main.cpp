
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class priorityqueue {
private:

public:
    vector<pair<int, long>> heap;

    priorityqueue() {
        heap.resize(0);
    }

    void siftDown(int i) {
        int left = 2 * i + 1, right = 2 * i + 2;
        int smallest = i;
        int heapSize = heap.size();

        if ((left < heapSize) && (heap[left].second < heap[smallest].second)) {
            smallest = left;
        }

        if ((right < heapSize) && (heap[right].second < heap[smallest].second)) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            siftDown(smallest);
        }
    }

    void siftUp(int i) {
        while (heap[i].second < heap[(i - 1) / 2].second) {     // i  0 — мы в корне
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void push(int number, long element) {
        heap.emplace_back(number, element);
        //cout << "pushed "<< element << "   heap size " << heap.size()<<'\n';
        siftUp(heap.size() - 1);
    }

    string extract_min() {
        if (heap.size() == 0) {
            return "*";
        }

        swap(heap[0], heap[heap.size() - 1]);

        string s = to_string(heap[heap.size()-1].second);
        heap.pop_back();

        siftDown(0);

        return s;
    }

    void decrease_key(int index, long to) {
        for(int i = 0; i < heap.size(); i++) {
            if (heap[i].first == index) {
                heap[i].second = to;
                siftUp(i);
                break;
            }
        }
    }
};

int main() {
    freopen("priorityqueue.out", "w", stdout);
    ifstream fin("priorityqueue.in");

    string s;
    priorityqueue q;

    int count = 0;
    while (getline(fin, s)) {
        switch (s[0]) {
            case 'p': {
                s = s.erase(0, 5);
                long a = stoi(s);
                q.push(count, a);
                break;
            }
            case 'e': {
                string tmp = q.extract_min();
                cout << tmp <<'\n';
                break;
            }
            case 'd': {
                s.erase(0,13);
                int i = stoi(s.substr(0, s.find(" ")));
                s.erase(0,s.find(" ")+1);
                long a = stoi(s);
                q.decrease_key(i - 1, a);
                break;
            }
        }
        count++;
    }

    return 0;
}
