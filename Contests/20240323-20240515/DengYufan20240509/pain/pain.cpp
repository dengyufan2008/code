#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#define LL long long
#define Num vector<pair<int, int>>

using namespace std;

ifstream cin("pain.in");
ofstream cout("pain.out");

const int kMaxN = 100;
const int kPrime[25] = {2, 3, 5, 7, 11, 13, 17,
                        19, 23, 29, 31, 37, 41,
                        43, 47, 53, 59, 61, 67,
                        71, 73, 79, 83, 89, 97};
int t;
LL n, p, fact[kMaxN], _fact[kMaxN];
Num a[2], b[2];
map<Num, LL> f;
map<Num, LL> g;

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
  return fact[x] * _fact[y] % p * _fact[x - y] % p;
}

int PopCount(int s) {
  int c = 0;
  for (; s; s ^= s & -s) {
  }
  return c;
}

void R(Num &x) {
  static Num y;
  sort(x.begin(), x.end()), y.clear();
  for (int i = 0, j = 0; i < x.size(); i = j) {
    int s = 0;
    for (; j < x.size() && x[i].first == x[j].first; j++) {
      s += x[j].second;
    }
    if (x[i].first && s) {
      y.push_back({x[i].first, s});
    }
  }
  x = y;
}

LL H(Num x) {
  int w = 1;
  for (auto i : x) {
    w *= Pow(i.first + 1, i.second);
  }
  return (Pow(2, w) - 1 + p) % p;
}

LL G(Num x);

LL S(int o, int w, bool u) {
  static Num x;
  if (o == a[u].size()) {
    x = b[u], R(x);
    return (u ? G(x) : H(x)) * w % p;
  }
  LL ans = 0;
  for (int i = 0; i <= a[u][o].second; i++) {
    b[u].push_back({a[u][o].first - 1, i});
    b[u].push_back({a[u][o].first, a[u][o].second - i});
    LL s = S(o + 1, i & 1 ? p - w : w, u);
    ans = (ans + s * C(a[u][o].second, i)) % p;
    b[u].pop_back(), b[u].pop_back();
  }
  return ans;
}

LL G(Num x) {
  if (g.count(x)) {
    return g[x];
  }
  return a[0] = x, g[x] = S(0, 1, 0);
}

LL F(Num x) {
  if (f.count(x)) {
    return f[x];
  }
  return a[1] = x, f[x] = S(0, 1, 1);
}

void Calc() {
  static Num x;
  x.clear();
  for (int i : kPrime) {
    int c = 0;
    for (; !(n % i); n /= i) {
      c++;
    }
    if (c) {
      x.push_back({c, 1});
    }
  }
  R(x), cout << F(x) << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> p;
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1], p - 2);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % p;
  }
  while (t--) {
    cin >> n, Calc();
  }
  return 0;
}
