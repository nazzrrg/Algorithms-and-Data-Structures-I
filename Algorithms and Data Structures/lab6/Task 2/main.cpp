#include <iostream>
#include <vector>

using namespace std;

bool dfs(vector<vector<int>>& v, int i, int lb, int rb, bool right) {
    if (i < 0) return true;

    if (right) {
        if (v[i][0] >= rb) {
            rb = v[i][0];
            return dfs(v, v[i][1], lb, rb, false) && dfs(v, v[i][2], lb, rb, true);
        } else {
            return false;
        }
    } else {
        if (v[i][0] < lb) {
            lb = v[i][0];
            return dfs(v, v[i][1], lb, rb, false) && dfs(v, v[i][2], lb, rb, true);
        } else {
            return false;
        }
    }
}

int main() {
    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);

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
        v[i].push_back(t);
        v[i].push_back(l-1);
        v[i].push_back(r-1);
    }

    if (dfs(v, 0, v[0][0], v[0][0], true)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}