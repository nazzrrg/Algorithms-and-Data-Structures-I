#include <iostream>
#include <stdio.h>

using namespace std;

typedef struct stackNode{
    long long data = 0;
    stackNode* next = nullptr;
};

class stack{
public:
    stack() {
        top = nullptr;
    }

//    ~stack() {
//        while (top != nullptr) {
//            pop();
//        }
//    }

    void push(long long element) {
        stackNode* el = new stackNode;
        el->next = top;
        el->data = element;
        top = el;
    }

    long long pop() {
        if (top != nullptr) {
            stackNode *tmp = top;
            long long val = tmp->data;
            top = tmp->next;
            delete tmp;
            return val;
        }
    }

private:
    stackNode* top;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("stack.in", "r", stdin);
    freopen("stack.out", "w", stdout);

    int n;
    cin >> n;

    stack s;

    for (int i = 0; i < n; i++) {
        char action;
        cin >> action;

        if (action == '+') {
            long long el;
            cin >> el;
            s.push(el);
        } else if(action == '-') {
            cout << s.pop() << '\n';
        }
    }

    return 0;
}