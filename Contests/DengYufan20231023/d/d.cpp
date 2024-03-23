#include <iostream>
#include <unordered_map>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMod = 1e9 + 7;
int n, m, lg[1 << 25];
LL ans;
vector<int> p;
vector<pair<int, int>> l[114];
unordered_map<int, int> q[114];

bool P(int x) {
  for (int i = 2; i * i <= x; i++) {
    if (!(x % i)) {
      return 0;
    }
  }
  return 1;
}

int PopCount(int x) {
  int c = 0;
  for (; x; x >>= 1) {
    c += x & 1;
  }
  return c;
}

int Gcd(int x, int y) {
  for (; y; swap(x, y), y %= x) {
  }
  return x;
}

LL Lcm(int x, int y) { return 1LL * x * y / Gcd(x, y); }

void W(int i) {
  int j = i, k = 2;
  p.clear();
  for (; k * k <= j; k++) {
    if (!(j % k)) {
      p.push_back(k);
      while (!(j % k)) {
        j /= k;
      }
    }
  }
  if (j > 1) {
    p.push_back(j);
  }
}

LL S(int x, int y) {
  if (x < 0) {
    x = (m - 1) / y;
    return 1LL * (x + 1) * x / 2 % kMod * y % kMod;
  } else if (q[x].count(y)) {
    return q[x][y];
  }
  LL s = 0;
  for (auto i : l[x]) {
    LL z = Lcm(y, i.first);
    if (z < m) {
      s = (s + i.second * S(x - 1, z) + kMod) % kMod;
    }
  }
  return q[x][y] = s;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < 25; i++) {
    lg[1 << i] = i;
  }
  cin >> n;
  for (m = n; !P(m); m--) {
  }
  ans = 1LL * m * (m - 1) / 2 % kMod * n % kMod;
  for (int i = m; i < n; i++) {
    for (int j = n;; j--) {
      if (Gcd(j, i) == 1) {
        ans = (ans + 1LL * i * j % kMod) % kMod;
        break;
      }
    }
  }
  for (int i = n; i >= m; i--) {
    W(i);
    for (int j = 1; j < (1 << p.size()); j++) {
      int s = 1;
      for (int k = j; k; k ^= k & -k) {
        s *= p[lg[k & -k]];
      }
      l[n - i].push_back({s, PopCount(j) & 1 ? 1 : -1});
    }
    ans = (ans - S(n - i, 1) + kMod) % kMod;
  }
  cout << ans;
  return 0;
}
