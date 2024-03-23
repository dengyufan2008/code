#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const int kMaxN = 1e6 + 1;
LL n, m, p, ans, f[kMaxN], fact[kMaxN], _fact[kMaxN];
vector<int> l;

LL Pow(LL x, int y) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

LL C(int x, int y) {
  if (x < y) {
    return 0;
  }
  return fact[x] * _fact[y] % p * _fact[x - y] % p;
}

void Calc(LL x) {
  x = (m - x) / x, l.clear();
  for (int i = 1; i * i <= x; i++) {
    if (!(x % i)) {
      l.push_back(i);
      if (i * i < x) {
        l.push_back(x / i);
      }
    }
  }
  sort(l.begin(), l.end());
  for (int i = 0, k; i < l.size(); i++) {
    f[i] = 1, k = l[i];
    for (int j = 2; j * j <= k; j++) {
      if (!(k % j)) {
        int c = 0;
        while (!(k % j)) {
          k /= j, c++;
        }
        f[i] = f[i] * (c + 1) % p;
      }
    }
    if (k > 1) {
      f[i] = f[i] * 2 % p;
    }
    f[i] = C(f[i], n);
  }
  for (int o = 0; o < 2; o++) {
    for (int i = 0; i < l.size(); i++) {
      for (int j = 0; j < i; j++) {
        if (!(l[i] % l[j])) {
          f[i] = (f[i] - f[j] + p) % p;
        }
      }
    }
  }
  ans = (ans + f[l.size() - 1]) % p;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> p;
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1], p - 2);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % p;
  }
  Calc(1);
  for (int i = 2; i * i <= m; i++) {
    if (!(m % i)) {
      Calc(i);
      if (i * i < m) {
        Calc(m / i);
      }
    }
  }
  cout << ans;
  return 0;
}
