#include <iostream>
#include <stack>
#include <fstream>
#include <string>

using namespace std;

int main() {
    freopen("brackets.out", "w", stdout);
    ifstream fin("brackets.in");

    string str;
    stack<char> s;

    while (getline(fin, str)){
        for (int i = 0; i < str.length(); i++) {
            switch (str[i]) {
                case '(':
                    s.push('(');
                    break;
                case '[':
                    s.push('[');
                    break;
                case ')':
                    if (s.empty()) {
                        s.push('-');
                        break;
                    }
                    if (s.top() == '(') {
                        s.pop();
                    } else {
                        s.push('-');
                    }
                    break;
                case ']':
                    if (s.empty()) {
                        s.push('-');
                        break;
                    }
                    if (s.top() == '[') {
                        s.pop();
                    } else {
                        s.push('-');
                    }
                    break;
            }
        }

        if (s.empty()) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }

        str = "";
        while (!s.empty()) s.pop();
    }

    return 0;
}