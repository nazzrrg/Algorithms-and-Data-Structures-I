#include <iostream>

using namespace std;

void siftDown(int a[], int i, int heapSize) {
    int left = 2 * i + 1, right = 2 * i + 2;
    int largest = i;

    if ((left < heapSize) && (a[left] > a[largest])) {
        largest = left;
    }

    if ((right < heapSize) && (a[right] > a[largest])) {
        largest = right;
    }
    if (largest != i) {
        swap(a[i], a[largest]);
        siftDown(a, largest, heapSize);
    }
}

void heapSort(int a[], int n) {
    for (int i = n /  2 - 1; i >= 0; i--) {
        siftDown(a, i, n);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(a[0], a[i]);
        siftDown(a, 0, i);
    }

}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);

    int n;
    cin >> n;

    int array[n];
    for(int i = 0; i < n; i++) {
        cin >> array[i];
    }

    heapSort(array, n);

    for(int i = 0; i < n; i++) {
        cout << array[i] << ' ';
    }

    return 0;
}