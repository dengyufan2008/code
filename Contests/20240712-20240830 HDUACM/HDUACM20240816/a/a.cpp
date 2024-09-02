#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("a.in");
ofstream cout("a.out");

const int kMaxN = 2e5 + 1, kMod = 998244353;
struct V {
  int s;
  LL w;
  vector<int> e;
} v[kMaxN];
int t, n, k;
LL fact[kMaxN], _fact[kMaxN], pw[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void T(int x) {
  int c = 0;
  v[x].s = v[x].w = 1;
  for (int i : v[x].e) {
    T(i);
    v[x].s += v[i].s, c += v[i].s & 1;
    v[x].w = v[x].w * v[i].w % kMod;
  }
  v[x].w = v[x].w * pw[v[x].e.size() - c] % kMod;
  if (c & 1) {
    v[x].w = v[x].w * C(c, c / 2) % kMod;
  } else {
    v[x].w = v[x].w * (C(c, c / 2) + C(c, c / 2 - 1)) % kMod;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * 2 % kMod;
  }
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> t;
  while (t--) {
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    cin >> n >> k;
    for (int i = 2, x; i <= n; i++) {
      cin >> x, v[x].e.push_back(i);
    }
    T(1);
    cout << Pow(v[1].w * 2 % kMod, k) % kMod << '\n';
  }
  return 0;
}
