#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("mex.in");
ofstream cout("mex.out");

const int kMaxN = 201, kMod = 998244353;
int n, c[kMaxN];
LL fact[kMaxN], _fact[kMaxN];
pair<int, int> e[kMaxN];

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

namespace Sub1 {
const int kMaxN = 201;
LL f[kMaxN];

int main() {
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      LL w = C(i, j) * Pow(n - j + 1, n - 1) % kMod;
      if (j & 1) {
        f[i] = (f[i] - w + kMod) % kMod;
      } else {
        f[i] = (f[i] + w) % kMod;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    f[i] = (f[i] - f[i + 1] + kMod) % kMod;
  }
  for (int i = 0; i <= n; i++) {
    cout << f[i] << '\n';
  }
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
const int kMaxN = 201, kMaxM = 17;
struct V {
  LL f[1 << kMaxM];
  vector<int> e;
} v[kMaxN];
int pop[1 << kMaxM];
LL g[1 << kMaxM];

void T(int f, int x) {
  if (v[x].e.empty() || v[x].e.size() == 1 && v[x].e[0] == f) {
    for (int i = 0; i <= n; i++) {
      v[x].f[1 << min(i, kMaxM - 1)]++;
    }
    for (int i = 0; i < kMaxM; i++) {
      for (int s = 0; s < 1 << kMaxM; s++) {
        if (s >> i & 1) {
          v[x].f[s] += v[x].f[s ^ 1 << i];
        }
      }
    }
    return;
  }
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
  for (int s = 0; s < 1 << kMaxM; s++) {
    g[s] = 1;
  }
  for (int i : v[x].e) {
    if (i != f) {
      for (int s = 0; s < 1 << kMaxM; s++) {
        g[s] = g[s] * v[i].f[s] % kMod;
      }
    }
  }
  for (int i = kMaxM - 1; i >= 0; i--) {
    for (int s = 0; s < 1 << i; s++) {
      LL w = g[~(-1 << kMaxM) ^ s];
      if (pop[s] & 1) {
        v[x].f[1 << i] = (v[x].f[1 << i] - w + kMod) % kMod;
      } else {
        v[x].f[1 << i] = (v[x].f[1 << i] + w) % kMod;
      }
    }
  }
  for (int i = 1; i < kMaxM; i++) {
    v[x].f[1 << i - 1] = (v[x].f[1 << i - 1] - v[x].f[1 << i] + kMod) % kMod;
  }
  for (int i = 0; i < kMaxM; i++) {
    for (int s = 0; s < 1 << kMaxM; s++) {
      if (s >> i & 1) {
        v[x].f[s] = (v[x].f[s] + v[x].f[s ^ 1 << i]) % kMod;
      }
    }
  }
}

int main() {
  for (int s = 1; s < 1 << kMaxM; s++) {
    pop[s] = pop[s ^ (s & -s)] + 1;
  }
  for (int i = 1; i < n; i++) {
    v[e[i].first].e.push_back(e[i].second);
    v[e[i].second].e.push_back(e[i].first);
  }
  T(0, 1);
  if (n < kMaxM) {
    for (int i = 0; i <= n; i++) {
      cout << v[1].f[1 << i] << '\n';
    }
  } else {
    for (int i = 0; i < kMaxM; i++) {
      cout << v[1].f[1 << i] << '\n';
    }
    for (int i = kMaxM; i <= n; i++) {
      cout << 0 << '\n';
    }
  }
  return 0;
}
}  // namespace Sub2

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y, e[i] = {x, y};
    c[x]++, c[y]++;
  }
  if (n == 1) {
    for (int i = 0; i <= n; i++) {
      cout << 1 << '\n';
    }
    return 0;
  } else if (c[1] == n - 1) {
    return Sub1::main();
  } else {
    return Sub2::main();
  }
  return 0;
}
