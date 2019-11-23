#include <iostream>

using namespace std;

int binSearchLeft(int array[], int length, int element) {
    int l = -1, r = length;
    while (r - l > 1) {
        int mid = (l + r) / 2;

        if (array[mid] < element) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (array[r] == element) {
        return r + 1;
    } else {
        return -1;
    }
}

int binSearchRight(int array[], int length, int element) {
    int l = -1, r = length;
    while (r - l > 1) {
        int mid = (l + r) / 2;

        if(array[mid] > element) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if (array[l] == element) {
        return l + 1;
    } else {
        return -1;
    }

}


int main() {
    freopen("binsearch.in", "r", stdin);
    freopen("binsearch.out", "w", stdout);

    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int k;
    cin >> k;
    for (int t, i = 0; i < k; i++) {
        cin >> t;
        cout << binSearchLeft(a,n,t) << ' ' << binSearchRight(a,n,t)<< endl;
    }


    return 0;
}
//5
//1 1 2 2 2
//3 1 2 3