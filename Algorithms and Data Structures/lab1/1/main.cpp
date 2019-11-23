#include <iostream>

using namespace std;

int main() {
    //freopen("turtle.in", "r", stdin);
    //freopen("turtle.out", "w", stdout);

    int h, w;
    cin >> h >> w;

    int field[h+1][w+1];
    for (int i = 0; i <= h; i++) {
        for(int j = 0; j <= w; j++) {
            field[i][j] = 0;
        }
    }

    for (int i = 0; i < h; i++) {
        for(int j = 1; j <= w; j++) {
            cin >> field[i][j];
        }
    }

    for (int i = 0; i <= h; i++) {
        for(int j = 0; j <= w; j++) {
            cout << field[i][j] << ' ';
        }
        cout << endl;
    }

    for (int i = h-1; i >= 0; i--) {
        for (int j = 1; j <= w; j++) {
            field[i][j] += max(field[i+1][j], field[i][j-1]);
        }
    }

    cout << field[0][w] << '\n';

    return 0;
}