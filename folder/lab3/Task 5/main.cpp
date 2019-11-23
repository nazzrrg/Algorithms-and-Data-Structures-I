#include <iostream>
#include <string>

using namespace std;

void countingSort(string a[], int n, int j) {
    unsigned int p[128];
    for (int i = 0; i < 128; i++) {
        p[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        p[(int)a[i][j]]++;
    }

    for (int i = 1; i < 128; i++) {
        p[i] += p[i - 1];
    }

    for (int i = 127; i >= 0; i--) {
        p[i] = p[i - 1];
    }

    string b[n];

    for (int i = 0; i < n; i++) {
        b[p[(int)a[i][j]]] = a[i];
        p[(int)a[i][j]]++;
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

void radixSort(string a[], int n, int m, int k) {
    for (int i = 1; i <= k && k <= m; i++) {
        countingSort(a, n, m - i);
    }
}

int main() {
    freopen("radixsort.in", "r", stdin);
    freopen("radixsort.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;
    string array[n];

    for (int i = 0; i < n; i++){
        cin >> array[i];
    }

    radixSort(array, n, m, k);

    for (int i = 0; i < n; i++){
        cout << array[i] << endl;
    }

    return 0;
}