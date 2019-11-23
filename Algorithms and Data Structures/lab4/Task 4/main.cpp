#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    freopen("postfix.in", "r", stdin);
    freopen("postfix.out", "w", stdout);

    string input;
    stack<long long> s;
    getline(cin, input);

    for (int i = 0; i < input.length(); i++) {
        if (input[i] >= '0' && input[i] <= '9'){
            s.push((input[i]) - 48);
        }

        long long a,b;

        switch (input[i]){
            case '+':
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a+b);
                break;
            case '-':
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b - a);
                break;
            case '*':
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a * b);
                break;
        }
    }

    cout << s.top();

    return 0;
}