#include <iostream>

using namespace std;

void merge(int a[], int left, int mid, int right) {
    int it1 = left, it2 = mid + 1, counter = 0;

    int tmp[right - left + 1];

    while ((it1 <= mid) && (it2 <= right)) {
        if (a[it1] <= a[it2]) {
            tmp[counter] = a[it1];
            it1++;
        } else {
            tmp[counter] = a[it2];
            it2++;
        }

        counter++;
    }

    while (it1 <= mid) {
        tmp[counter] = a[it1];
        counter++;
        it1++;
    }

    while (it2 <= right) {
        tmp[counter] = a[it2];
        counter++;
        it2++;
    }

    for(int i = left; i <= right; i++) {
        a[i] = tmp[i - left];
    }
}

void mergesort(int a[], int left, int right) {
    if (left < right) {
        int mid = (right + left) / 2;
        mergesort(a, left, mid);
        mergesort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

int main() {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    int length;
    cin >> length;
    int array[length];

    for (int i = 0; i < length; i++) {
        cin >> array[i];
    }

    mergesort(array, 0, length - 1);

    for (int i = 0; i < length; i++)
    {
        cout << array[i] << ' ';
    }

    return 0;
}
//10
//1 8 2 1 4 7 3 2 3 6