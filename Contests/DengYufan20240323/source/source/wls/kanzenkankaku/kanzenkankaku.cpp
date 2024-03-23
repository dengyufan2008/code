#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N = 3e2 + 10;
const ull b = 1e9 + 7;
int n, c, s[N];
ull hsa[N][N], hsb[N][N], hssa[N][N][N], hssb[N][N][N];
bool dp[N][N], isd[N][N];
int main() {
    // freopen("ex_kanzenkankaku1.in", "r", stdin);
    freopen("kanzenkankaku.in", "r", stdin);
    freopen("kanzenkankaku.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> c;
    for (int i = 1; i <= n; i++) cin >> s[i], dp[i][i] = dp[i][i - 1] = 1;
    for (int i = 1; i <= n; i++) {
        vector<int> v;
        v.push_back(s[i]);
        isd[i][i] = 1;
        hsa[i][i] = hssa[i][i][1] = s[i];
        for (int j = i + 1; j <= n; j++) {
            isd[i][j] = isd[i][j - 1] & (s[j - 1] >= s[j]);
            hsa[i][j] = hsa[i][j - 1] * b + s[j];
            v.insert(lower_bound(v.begin(), v.end(), s[j]), s[j]);
            for (int k = 0; k < v.size(); k++) hssa[i][j][k + 1] = hssa[i][j][k] * b + v[k];
            for (int k = v.size() - 1; k >= 0; k--) hssb[i][j][(int)v.size() - k] = hssb[i][j][(int)v.size() - k - 1] * b + v[k];
        }
    }
    for (int i = 1; i <= n; i++) {
        hsb[i][i] = s[i];
        for (int j = i - 1; j >= 1; j--) hsb[j][i] = hsb[j + 1][i] * b + s[j];
    }
    for (int len = 2; len <= n; len++) {
        for (int l = 1, r = len; r <= n; l++, r++) {
            for (int k = 1; k * 2 <= len; k++) {
                // for (int p = 1; p <= l; p++) {
                //     if (hssb[p][l + k - 1][k] == hsa[r - k + 1][r]) {
                //         dp[l][r] |= dp[l + k][r - k];
                //     }
                // }
                // for (int p = r; p <= n; p++) {
                //     if (hsb[l][l + k - 1] == hssa[r - k + 1][p][k]) {
                //         dp[l][r] |= dp[l + k][r - k];
                //     }
                // }
                if (hssa[l][l + k - 1][k] != hssa[r - k + 1][r][k]) continue;
                if (isd[l][l + k - 1] || isd[r - k + 1][r] || (hsa[l][l + k - 1] == hsb[r - k + 1][r])) dp[l][r] |= dp[l + k][r - k];
                if (dp[l][r]) break;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (dp[i][j]) ans = max(ans, j - i + 1);
        }
    }
    cout << ans << '\n';
    return 0;
}
