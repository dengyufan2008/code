#include <fstream>
#define LL long long

using namespace std;

ifstream cin("timeline.in");
ofstream cout("timeline.out");

const int kMaxN = 17, kMaxM = kMaxN * (kMaxN - 1) / 2, kMod = 1e9 + 7;
int n, m, k, r;
LL fact[kMaxN << 1], _fact[kMaxN << 1];
pair<int, int> e[kMaxM];

bool IsFlower() {
  for (int i = 1; i <= m; i++) {
    if (e[i].first != 1) {
      return 0;
    }
  }
  return 1;
}

bool IsTree() {
  bool b[kMaxN] = {};
  for (int i = 1; i <= m; i++) {
    if (b[e[i].second]) {
      return 0;
    }
    b[e[i].second] = 1;
  }
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      r = i;
    }
  }
  return 1;
}

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
  if (y < 0 || x < y) {
    return 0;
  }
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

namespace Sub1 {
int ans, a[kMaxN], d[kMaxN];
bool b[kMaxN], g[kMaxN][kMaxN], t[kMaxN];

bool R(int x, int y) {
  if (x == y) {
    return 1;
  } else if (t[x]) {
    return 0;
  }
  t[x] = 1;
  for (int i = 1; i <= k + 1; i++) {
    if (g[x][i] && R(i, y)) {
      return 1;
    }
  }
  return 0;
}

bool W() {
  fill(&g[0][0], &g[kMaxN][0], 0);
  for (int i = 1; i <= m; i++) {
    if (d[a[e[i].first]] != d[a[e[i].second]]) {
      g[d[a[e[i].first]]][d[a[e[i].second]]] = 1;
    } else if (a[e[i].first] > a[e[i].second]) {
      return 0;
    }
  }
  // for (int i = 1; i <= k + 1; i++) {
  //   for (int j = 1; j <= k + 1; j++) {
  //     cout << g[i][j] << " \n"[j == k + 1];
  //   }
  // }
  for (int i = 1; i <= k + 1; i++) {
    for (int j = 1; j <= k + 1; j++) {
      if (g[i][j]) {
        fill(&t[0], &t[kMaxN], 0);
        if (R(j, i)) {
          return 0;
        }
      }
    }
  }
  return 1;
}

void T(int x, int y) {
  if (y > k) {
    for (int i = x; i <= n; i++) {
      d[i] = y;
    }
    ans += W();
    // int shit[kMaxN];
    // for (int i = 1; i <= n; i++) {
    //   shit[a[i]] = i;
    // }
    // for (int i = 1; i <= n; i++) {
    //   cout << a[i] << " \n"[i == n];
    // }
    // for (int i = 1; i <= n; i++) {
    //   cout << d[i] << " \n"[i == n];
    // }
    // cout << W() << '\n' << '\n';
    return;
  }
  for (int i = x;; i++) {
    T(i, y + 1);
    if (i <= n) {
      d[i] = y;
    } else {
      break;
    }
  }
}

void S(int x) {
  if (x > n) {
    T(1, 1);
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (!b[i]) {
      b[i] = 1, a[x] = i;
      S(x + 1);
      b[i] = 0;
    }
  }
}

int main() {
  S(1);
  ans = ans * Pow(fact[n] * C(n + k, k) % kMod) % kMod;
  cout << ans << '\n';
  // a[1] = 1, a[2] = 3, a[3] = 4, a[4] = 2, d[1] = 4, d[2] = 4, d[3] = 5, d[4] = 5;
  // cout << W() << '\n';  // 1 4 2 3
  return 0;
}
}

namespace Sub2 {
int main() {
  cout << (C(n + k - 2, k - 1) * (n + k - 1) + C(n + k - 1, k)) % kMod * Pow(C(n + k, k) * n % kMod) % kMod << '\n';
  return 0;
}
}

namespace Sub3 {
int s[kMaxN];
LL ans;
bool g[kMaxN][kMaxN];

void T(int x) {
  s[x] = 1;
  for (int i = 1; i <= n; i++) {
    if (g[x][i]) {
      T(i), s[x] += s[i];
    }
  }
  ans = ans * Pow(s[x]) % kMod;
}

int main() {
  for (int i = 1; i <= m; i++) {
    g[e[i].first][e[i].second] = 1;
  }
  ans = 1, T(r);
  cout << ans << '\n';
  return 0;
}
}

namespace Sub4 {
int main() {
  cout << 1 << '\n';
  return 0;
}
}

namespace Sub5 {
int main() {
  cout << fact[k + 1] * _fact[n] % kMod << '\n';
  return 0;
}
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < (kMaxN << 1); i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[(kMaxN << 1) - 1] = Pow(fact[(kMaxN << 1) - 1]);
  for (int i = (kMaxN << 1) - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n >> m >> k;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].first >> e[i].second;
  }
  if (m == n - 1 && IsFlower()) {
    return Sub2::main();
  } else if (m == n - 1 && k == 0 && IsTree()) {
    return Sub3::main();
  } else if (m == 0) {
    return Sub4::main();
  } else if (m == n * (n - 1) / 2) {
    return Sub5::main();
  } else {
    return Sub1::main();
  }
  return 0;
}
