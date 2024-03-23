#include <algorithm>
#include <fstream>
#include <unordered_map>
#define LL long long

using namespace std;

ifstream cin("magic.in");
ofstream cout("magic.out");

const int kMaxN = 5e5 + 2;
int n, a[kMaxN], b[kMaxN], f[kMaxN];
LL ans;
unordered_map<int, int> s[kMaxN];

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    b[i] = f[i] = i;
  }
  sort(b + 1, b + n + 1, [](int i, int j) { return a[i] < a[j] || a[i] == a[j] && i < j; });
  for (int o = 1; o <= n; o++) {
    int i = b[o], l = GetRoot(f[i - 1]) + 1, r = i + 1;
    if (s[l].size() < s[r].size()) {
      s[r].swap(s[l]);
    }
    for (auto j : s[r]) {
      if (s[l].count(a[i] - j.first)) {
        ans += 1LL * j.second * s[l][a[i] - j.first];
      }
    }
    for (auto j : s[r]) {
      s[l][j.first] += j.second;
    }
    s[l][a[i]]++, s[r].clear(), f[i] = GetRoot(i - 1);
  }
  cout << ans << '\n';
  return 0;
}
