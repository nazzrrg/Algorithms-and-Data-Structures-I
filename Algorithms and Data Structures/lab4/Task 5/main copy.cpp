#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int binSearchRight(vector<long> array, long element) {
    int l = -1, r = array.size();
    while (r - l > 1) {
        int mid = (l + r) / 2;

        if(array[mid] > element) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if (array[l] == element) {
        return l;
    } else {
        return -1;
    }

}


class priorityqueue {
private:

public:
    vector<long> heap;

    priorityqueue() {
        heap.resize(0);
    }

    void siftDown(int i, int heapSize) {
        int left = 2 * i + 1, right = 2 * i + 2;
        int smallest = i;

        if ((left < heapSize) && (heap[left] < heap[smallest])) {
            smallest = left;
        }

        if ((right < heapSize) && (heap[right] < heap[smallest])) {
            smallest = right;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            siftDown(smallest, heapSize);
        }
    }

    void siftUp(int i) {
        while (heap[i] < heap[(i - 1) / 2]) {     // i  0 — мы в корне
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void push(long element) {
        heap.push_back(element);
        //cout << "pushed "<< element << "   heap size " << heap.size()<<'\n';
        siftUp(heap.size() - 1);
    }

    string extract_min() {
        //cout <<"extracting"<<'\n';
        if (heap.size() == 0) {
            return "*";
        }

        //for(int i = 0; i < heap.size();i++) cout << heap[i] << ' '; cout <<'\n';
        swap(heap[0], heap[heap.size() - 1]);
        //for(int i = 0; i < heap.size();i++) cout << heap[i] << ' '; cout <<'\n';
        string s = to_string(heap[heap.size()-1]);
        heap.pop_back();
        //for(int i = 0; i < heap.size();i++) cout << heap[i] << ' '; cout <<'\n';
        //cout << "**extracting** "<<heap.size() << s << "*\n";

        siftDown(0, heap.size());
        //for(int i = 0; i < heap.size();i++) cout << heap[i] << ' '; cout <<'\n';

        return s;
    }

    void decrease_key(long from, long to) {
        int i = binSearchRight(heap, from);
        heap[i] = to;
        siftDown(0, heap.size());
    }
};

int main() {
    freopen("priorityqueue.out", "w", stdout);
    ifstream fin("priorityqueue.in");

    string s;
    vector<long> kostyl;
    priorityqueue q;

    while (getline(fin, s)) {
        //cout << s << '\n';
        switch (s[0]) {
            case 'p': {
                s = s.erase(0, 5);
                long a = stoi(s);

//                cout << "a:" << s <<'\n';
                kostyl.push_back(a);
                q.push(a);

//                for(int i = 0; i<kostyl.size();i++) cout << kostyl[i] << ' '; cout <<'\n';
//                for(int i = 0; i<q.heap.size();i++) cout << q.heap[i] << ' '; cout <<'\n';
                break;
            }
            case 'e': {
                string tmp = q.extract_min();
//                cout <<"e: "<< s << ":  ";
                cout << tmp <<'\n';
//                for(int i = 0; i<q.heap.size();i++) cout << q.heap[i] << ' '; cout <<'\n';
                break;
            }
            case 'd': {
                s.erase(0,13);
                //cout <<"for parse in d:"<<s<<'\n';
                int i = stoi(s.substr(0, s.find(" ")));
//                cout << "i="<<i<<'\n';
                s.erase(0,s.find(" ")+1);
                long a = stoi(s);
//                cout << "a="<<a<<'\n';
//                cout << "kostyl["<<i<<"]="<<kostyl[i]<<'\n';
                q.decrease_key(kostyl[i - 1],a);
//              getline(fin, s);
                break;
            }
        }
    }

//    long a,b,c;
//    cin >> a >> b >> c;
//    priorityqueue q;
//    q.push(a);
//    q.push(b);
//    q.push(c);
//
//    cout << q.extract_min() << '\n';
//    long d;
//    cin >> d;
//    q.decrease_key(b, d);
//    cout << q.extract_min() << '\n';
//    cout << q.extract_min() << '\n';
//    cout << q.extract_min() << '\n';

    return 0;
}