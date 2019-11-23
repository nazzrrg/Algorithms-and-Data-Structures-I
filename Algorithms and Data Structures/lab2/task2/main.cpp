#include <iostream>
#include <string>

using namespace std;

struct participant
{
    string country;
    string surname;
};

void merge(participant arr[], int left, int mid, int right)
{
    int it1 = left, it2 = mid + 1, counter = 0;

    participant tmp[right - left + 1];

    while ((it1 <= mid) && (it2 <= right)) {
        if (arr[it1].country.compare(arr[it2].country) <= 0) {
            tmp[counter] = arr[it1];
            it1++;
        } else {
            tmp[counter] = arr[it2];
            it2++;
        }

        counter++;
    }

    while (it1 <= mid) {
        tmp[counter] = arr[it1];
        counter++;
        it1++;
    }

    while (it2 <= right) {
        tmp[counter] = arr[it2];
        counter++;
        it2++;
    }

    for(int i = left; i <= right; i++) {
        arr[i] = tmp[i - left];
    }
}

void mergesort(participant arr[], int left, int right) {
    if (left < right) {
        int mid = (right + left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


int main() {
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);
    int n;
    cin >> n;

    participant participants[n];

    for(int i = 0; i < n; i++) {
        cin >> participants[i].country >> participants[i].surname;
    }

    mergesort(participants, 0, n - 1);

    string country_change = "";

    for (int i = 0; i < n; i++) {
        if (country_change != participants[i].country) {
            cout << "=== " << participants[i].country << " ===" << '\n';
            country_change = participants[i].country;
        }

        cout << participants[i].surname << '\n';
    }


    return 0;
}