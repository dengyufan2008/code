#include <chrono>
#include <fstream>
#include <random>
#include <unordered_map>
#define ULL unsigned long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 1 << 20 | 1, kBase = 1e9 + 7;
int o, n, m, ans;
ULL w[26], h[kMaxN], pw[kMaxN];
string s, t;
unordered_map<ULL, int> q, b;
mt19937_64 Rand(chrono::steady_clock().now().time_since_epoch().count());

ULL Calc(int l, int r) {
  return l ? h[r] - h[l - 1] * pw[r - l + 1] : h[r];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o, pw[0] = 1;
  for (int i = 1; i <= kMaxN; i++) {
    pw[i] = pw[i - 1] * kBase;
  }
  while (o--) {
    ans = 0, q.clear(), b.clear();
    cin >> s >> t;
    n = s.size(), m = t.size();
    for (int i = 0; i < 26; i++) {
      w[i] = Rand();
    }
    for (int i = 0; i < m; i++) {
      h[i] = i ? h[i - 1] * kBase + w[t[i] - 'A'] : w[t[i] - 'A'];
    }
    for (int i = n - 1; i < m; i++) {
      q[Calc(i - n + 1, i)]++;
    }
    for (int i = 0; i < n; i++) {
      h[i] = i ? h[i - 1] * kBase + w[s[i] - 'A'] : w[s[i] - 'A'];
    }
    for (int i = 0; i < n; i++) {
      ULL c = i ? Calc(i, n - 1) * pw[i] + h[i - 1] : Calc(i, n - 1) * pw[i];
      if (!b[c]) {
        ans += q[c], b[c] = 1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
