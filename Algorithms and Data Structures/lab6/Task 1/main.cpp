#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<int>>& v, int i) {
    int maxn = 0;
    if (i < 0) {
        return 0;
    }
    for (auto it : v[i]) {
        maxn = max(dfs(v, it), maxn);
    }
    return maxn + 1;
}

int main() {
    freopen("height.in", "r", stdin);
    freopen("height.out", "w", stdout);

    vector<vector<int>> v;

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0;
        return 0;
    }
    v.resize(n);

    for (int i = 0; i < n; ++i) {
        int t,l,r;
        cin >> t >> l >> r;

        v[i].push_back(l-1);
        v[i].push_back(r-1);
    }

    cout << dfs(v, 0);

    return 0;
}