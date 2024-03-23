#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

constexpr int kMaxN = 5001, kMaxM = 1e6 + 1, kMod = 998244353;
struct V {
  int x, y;
} v[kMaxM];
int n, m, q, k, ans, a[kMaxN], b[kMaxN], c[kMaxN * kMaxN], d[kMaxN][kMaxN], p17[kMaxN] = {1}, p19[kMaxN] = {1};
char ch;
uint64_t seed;

uint64_t Next() {
  seed ^= seed << 13;
  seed ^= seed >> 7;
  seed ^= seed << 17;
  return seed;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q >> seed;
  for (int i = 0; i < n; i++) {
    a[i] = i, p17[i + 1] = (LL)p17[i] * 17LL % kMod;
  }
  for (int i = 0; i < m; i++) {
    b[i] = i, p19[i + 1] = (LL)p19[i] * 19LL % kMod;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      c[i * m + j] = i * m + j;
    }
  }
  for (int i = 1; i <= q; i++) {
    cin >> ch;
    if (ch == 'r') {
      swap(a[Next() % n], a[Next() % n]);
    } else if (ch == 'c') {
      swap(b[Next() % m], b[Next() % m]);
    } else {
      swap(c[a[Next() % n] * m + b[Next() % m]], c[a[Next() % n] * m + b[Next() % m]]);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans = ((LL)ans + (LL)p17[i] * (LL)p19[j] % (LL)kMod * (LL)c[a[i] * m + b[j]] % (LL)kMod) % (LL)kMod;
    }
  }
  cout << ans;
  return 0;
}
