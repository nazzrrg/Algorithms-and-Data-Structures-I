#include <iostream>

using namespace std;

typedef struct queueNode {
    long long data = 0;
    queueNode* next = nullptr;
};

class queue {
public:
    queue() {
        top = nullptr;
        bottom = nullptr;
    }

    ~queue() {
        while (bottom != nullptr) {
            pop();
        }
    }

    void push(long long element) {
        queueNode* el = new queueNode;
        el->data = element;

        if (bottom == nullptr) {
            bottom = el;
        }
        if (top != nullptr) {
            top->next = el;
        }
        top = el;
    }

    long long pop() {
        if (bottom != nullptr) {
            queueNode* tmp = bottom;
            long long val = tmp->data;
            bottom = tmp->next;
            delete tmp;

            if(bottom==nullptr)
            {
                top = nullptr;
            }

            return val;
        }
    }

private:
    queueNode* top;
    queueNode* bottom;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);

    int n;
    cin >> n;

    queue q;

    for (int i = 0; i < n; i++) {
        char action;
        cin >> action;

        if (action == '+') {
            long long el;
            cin >> el;
            q.push(el);
        }
        else if (action == '-') {
            cout << q.pop() << '\n';
        }
    }

    return 0;
}