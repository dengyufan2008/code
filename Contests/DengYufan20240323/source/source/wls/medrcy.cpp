#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10, M = 3e3 + 10;
int n, m, k;
int a[M], b[M];
int main() {
    freopen("medrcy.in", "r", stdin);
    freopen("medrcy.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= m; i++) cin >> a[i] >> b[i];
        if (k <= 3) {
            int minx = 0x3f3f3f3f;
            set<int> ans;
            if (k >= 1) {
                for (int s0 = 1; s0 <= n; s0++) {
                    int c = 1;
                    if (c > minx) continue;
                    bool ok = 1;
                    for (int i = 1; i <= m; i++) {
                        if (s0 != a[i] && s0 != b[i]) {
                            ok = 0;
                            break;
                        }
                    }
                    if (!ok) continue;
                    if (minx == c) ans.insert(s0);
                    else if (minx > c) minx = c, ans.clear(), ans.insert(s0);
                }
            }
            if (ans.empty() && k >= 2) {
                for (int s0 = 1; s0 <= n; s0++) {
                    for (int s1 = 1; s1 <= n; s1++) {
                        int c = 2;
                        if (c > minx) continue;
                        bool ok = 1;
                        for (int i = 1; i <= m; i++) {
                            if (s0 != a[i] && s0 != b[i] && s1 != a[i] && s1 != b[i]) {
                                ok = 0;
                                break;
                            }
                        }
                        if (!ok) continue;
                        if (minx == c) ans.insert(s0), ans.insert(s1);
                        else if (minx > c) minx = c, ans.clear(), ans.insert(s0), ans.insert(s1);
                    }
                }
            }
            if (ans.empty() && k >= 3) {
                for (int s0 = 1; s0 <= n; s0++) {
                    for (int s1 = 1; s1 <= n; s1++) {
                        for (int s2 = 1; s2 <= n; s2++) {
                            int c = 3;
                            if (c > minx) continue;
                            bool ok = 1;
                            for (int i = 1; i <= m; i++) {
                                if (s0 != a[i] && s0 != b[i] && s1 != a[i] && s1 != b[i] && s2 != a[i] && s2 != b[i]) {
                                    ok = 0;
                                    break;
                                }
                            }
                            if (!ok) continue;
                            if (minx == c) ans.insert(s0), ans.insert(s1), ans.insert(s2);
                            else if (minx > c) minx = c, ans.clear(), ans.insert(s0), ans.insert(s1), ans.insert(s2);
                        }
                    }
                }
            }
            if (ans.empty() || minx > k) {
                cout << "-1\n";
                continue;
            }
            cout << minx << ' ' << ans.size() << '\n';
            for (auto x : ans) cout << x << ' ';
            cout << '\n';
        } else {
            int minx = 0x3f3f3f3f, ans = -1;
            for (int s = 1; s < (1 << n); s++) {
                int c = __builtin_popcount(s);
                if (c > minx) continue;
                bool ok = 1;
                for (int i = 1; i <= m; i++) {
                    if ((s >> a[i] - 1 & 1 ^ 1) && (s >> b[i] - 1 & 1 ^ 1)) {
                        ok = 0;
                        break;
                    }
                }
                if (!ok) continue;
                if (minx == c) ans |= s;
                else if (minx > c) minx = c, ans = s;
            }
            if (ans == -1 || minx > k) {
                cout << "-1\n";
                continue;
            }
            cout << minx << ' ' << __builtin_popcount(ans) << '\n';
            for (int i = 1; i <= n; i++)
                if (ans >> i - 1 & 1) cout << i << ' ';
            cout << '\n';
        }
    }
    return 0;
}