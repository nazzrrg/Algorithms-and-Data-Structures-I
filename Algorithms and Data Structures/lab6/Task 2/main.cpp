#include <iostream>
#include <vector>

using namespace std;

bool dfs(vector<vector<int>>& v, int i, int lb, int rb) {
    if (i < 0) return true;

//    cout << "DFS from " << v[i][0] << " with lb = " << lb << " rb = " << rb << endl;

    if (v[i][0] <= lb || v[i][0] >= rb) return false;

    return (dfs(v, v[i][1], lb, v[i][0]) && dfs(v, v[i][2], v[i][0], rb));
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);

    vector<vector<int>> v;

    int n;
    cin >> n;

    if (n == 0) {
        cout << "YES";
        return 0;
    }
    v.resize(n);

    for (int i = 0; i < n; ++i) {
        int t,l,r;
        cin >> t >> l >> r;
        v[i].push_back(t);
        v[i].push_back(l-1);
        v[i].push_back(r-1);
    }

    if (dfs(v, 0, INT32_MIN, INT32_MAX)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}