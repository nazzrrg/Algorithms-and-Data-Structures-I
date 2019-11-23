#include <iostream>

using namespace std;

int main() {
    freopen("antiqs.in", "r", stdin);
    freopen("antiqs.out", "w", stdout);

    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {
        swap(arr[i], arr[i/2]);
    }

    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }

    return 0;
}