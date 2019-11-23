#include <iostream>

using namespace std;

int main() {
    freopen("sortland.in", "r", stdin);
    freopen("sortland.out", "w", stdout);

    unsigned int n;
    cin >> n;

    double array[n][2];
    for (int i = 0; i < n; i++) {
        cin >> array[i][0];
        array[i][1] = i + 1;
    }

    int operation_counter=1;

    while (operation_counter != 0) {
        operation_counter = 0;

        for (int i = 0;i < n - 1; i++) {
            if (array[i][0] > array [i + 1][0]) {
                swap(array[i][0], array[i + 1][0]);
                swap(array[i][1], array[i + 1][1]);
                operation_counter++;
            }
        }
    }

    /*for (int i = 0; i < n; i++) {
        cout << array[i] << ' ';
    }*/


    cout.setf(ios::fixed);
    cout.precision(0);
    cout << array[0][1] << ' ' << array[n/2][1] << ' ' << array[n-1][1];

    return 0;
}