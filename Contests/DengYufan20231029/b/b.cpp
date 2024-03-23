#include <iostream>

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e6 + 1, kMod = 1e9 + 7;
int n, ans, h[3], a[kMaxN * 3], b[kMaxN * 3], w[kMaxN], s[kMaxN * 3], p[kMaxN][3], f[kMaxN * 3];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, j = 0; i <= n * 3; i++) {
    cin >> b[i];
    if (b[i] == 1) {
      h[j++] = i;
    }
  }
  f[0] = 1;
  for (int o = 0; o < 3; o++) {
    copy(&b[h[o]], &b[n * 3] + 1, &a[1]);
    copy(&b[1], &b[h[o]], &a[n * 3 - h[o] + 2]);
    fill(&w[1], &w[n] + 1, 0);
    for (int i = 1; i <= n * 3; i++) {
      p[a[i]][w[a[i]]++] = i;
      if (w[a[i]] == 1 || a[i] == 1 && w[a[i]] == 3) {
        f[i] = f[i - 1], s[i] = s[i - 1];
      } else if (w[a[i]] == 2) {
        f[i] = f[p[a[i]][0] - 1] * (s[p[a[i]][0]] == s[i - 1]), s[i] = s[i - 1] + 1;
      } else {
        f[i] = (f[i - 1] + f[p[a[i]][1] - 1] * (s[p[a[i]][1]] == s[i - 1])) % kMod, s[i] = s[i - 1];
      }
    }
    ans = (ans + f[n * 3]) % kMod;
  }
  cout << ans;
  return 0;
}
