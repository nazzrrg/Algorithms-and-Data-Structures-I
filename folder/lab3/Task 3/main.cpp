#include <iostream>

using namespace std;

int main() {
    freopen("isheap.in", "r", stdin);
    freopen("isheap.out", "w", stdout);

    int n;
    cin >> n;

    int array[n + 1];

    for(int i = 1; i <= n; i++) {
        cin >> array[i];
    }

    bool isHeap = true;

    for (int i = 1; i <= n; i++) {
        if (i * 2 <= n) {
            isHeap &= (array[i] <= array[2 * i]);
        }
        if (i * 2 + 1 <= n) {
            isHeap &= (array[i] <= array[2 * i + 1]);
        }
    }

    if (isHeap) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }


    return 0;
}