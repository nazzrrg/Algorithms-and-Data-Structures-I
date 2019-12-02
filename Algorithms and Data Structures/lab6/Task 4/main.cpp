#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

class Quack {
private:
    uint16_t registers[26]{};
    queue<uint16_t> q;
    vector<pair<string, int>> labels;

public:
    Quack() {
        for (auto item : registers) {
            item = 0;
        }
    }

    void add() {
        uint16_t x = q.front();
        q.pop();
        uint16_t y = q.front();
        q.pop();
        uint16_t result = x + y;
        q.push(result);
    }

    void sub() {
        uint16_t x = q.front();
        q.pop();
        uint16_t y = q.front();
        q.pop();
        uint16_t result = x - y;
        q.push(result);
    }

    void mul() {
        uint16_t x = q.front();
        q.pop();
        uint16_t y = q.front();
        q.pop();
        uint16_t result = x * y;
        q.push(result);
    }

    void div() {
        uint16_t x = q.front();
        q.pop();
        uint16_t y = q.front();
        q.pop();
        if (y == 0) {
            q.push(0);
            return;
        }

        uint16_t result = x / y;
        q.push(result);
    }

    void mod() {
        uint16_t x = q.front();
        q.pop();
        uint16_t y = q.front();
        q.pop();

        if (y == 0) {
            q.push(0);
            return;
        }

        uint16_t result = x % y;
        q.push(result);
    }

    void set_register(char r) {
        uint16_t x = q.front();
        q.pop();
        registers[r - 'a'] = x;
    }

    void get_register(char r) {
        uint16_t res = registers[r - 'a'];
        q.push(res);
    }

    uint16_t print() {
        uint16_t x = q.front();
        q.pop();
        return x;
    }

    uint16_t print_register(char r) {
        return registers[r - 'a'];
    }

    char print_char() {
        uint16_t x = q.front() % 256;
        q.pop();
        return (char)x;
    }

    char print_register_char(char r) {
        return (char)registers[r - 'a'];
    }

    void add_label(string s, int i) {
//        string s1 = s;
        labels.emplace_back(s, i);
    }

    int jump_label(const string& s){
        for (const auto& item : labels) {
            if (item.first == s) {
                return item.second;
            }
        }
        cout << "label not found" << endl;
        return INT32_MAX;
    }

    void put(uint16_t x){
        q.push(x);
    }

};

vector<string> v;

int main() {
    freopen("quack.in", "r", stdin);
    freopen("quack.out", "w", stdout);

    string s;
    while (cin >> s) {
        v.push_back(s);
    }

    Quack quack;



    int i = 0;
    while (i < v.size()) {
        s = v[i];
//        cout << s << endl;
        if (s[0] == ':') {
            s = s.erase(0, 1);
            quack.add_label(s, i);
        }
        i++;
    }

    i = 0;

    while (i < v.size()) {
        s = v[i];
//        cout << s << endl;
        switch (s[0]) {
            case '+':
                quack.add();
                break;

            case '-':
                quack.sub();
                break;

            case '*':
                quack.mul();
                break;

            case '/':
                quack.div();
                break;

            case '%':
                quack.mod();
                break;

            case '>':
                quack.set_register(s[1]);
                break;

            case '<':
                quack.get_register(s[1]);
                break;

            case 'P':
                if (s.length() > 1) {
                    cout << quack.print_register(s[1]) << endl;
                } else {
                    cout << quack.print() << endl;
                }
                break;

            case 'C':
                if (s.length() > 1) {
                    cout << quack.print_register_char(s[1]);
                } else {
                    cout << quack.print_char();
                }
                break;

            case ':':
                s = s.erase(0, 1);
                quack.add_label(s, i);
                break;

            case 'J':
                s = s.erase(0, 1);
                i = quack.jump_label(s);
                break;

            case 'Z':
                if (quack.print_register(s[1]) == 0) {
                    s = s.erase(0, 2);
                    i = quack.jump_label(s);
                }
                break;

            case 'E':
                if (quack.print_register(s[1]) == quack.print_register(s[2])) {
                    s = s.erase(0, 3);
                    i = quack.jump_label(s);
                }
                break;

            case 'G':
                if (quack.print_register(s[1]) > quack.print_register(s[2])) {
                    s = s.erase(0, 3);
                    i = quack.jump_label(s);
                }
                break;

            case 'Q':
                i = v.size();
                break;

            default:
//                istringstream iss(s);
//                uint16_t x;
//                iss >> x;
                quack.put(stoi(s));
        }

        i++;
    }

    return 0;
}