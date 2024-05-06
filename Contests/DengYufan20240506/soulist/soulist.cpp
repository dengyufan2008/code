#include <fstream>
#define LL long long

using namespace std;

ifstream cin("soulist.in");
ofstream cout("soulist.out");

const int kMod = 998244353;
int n, m;

namespace Sub1 {
const int kMaxN = 20, kMaxM = 20;
struct V {
  int o, x, y, p;
} v[kMaxM];
int a[kMaxN], b[kMaxN];

int main() {
  for (int i = 1, x; i <= n; i++) {
    cin >> x, a[x] = b[x] = i;
  }
  for (int i = 1, t = 0, o, l, r; i <= m; i++) {
    cin >> o;
    if (o <= 2) {
      cin >> v[t].x >> v[t].p;
      v[t++].o = o;
    } else if (o == 3) {
      cin >> v[t].x >> v[t].y >> v[t].p;
      v[t++].o = o;
    } else {
      LL ans = 0;
      cin >> l >> r;
      for (int s = 0; s < 1 << t; s++) {
        LL w = 1;
        for (int j = 1; j <= n; j++) {
          a[j] = b[j];
        }
        for (int j = 0; j < t; j++) {
          if (s >> j & 1) {
            if (v[j].o == 1) {
              for (int k = 1, p = v[j].x; k == 1 || p != v[j].x; k++) {
                swap(a[k], p);
              }
            } else if (v[j].o == 2) {
              for (int k = n, p = v[j].x; k == n || p != v[j].x; k--) {
                swap(a[k], p);
              }
            } else if (v[j].o == 3) {
              for (int k = 1; k <= n; k++) {
                if (a[k] == v[j].x || a[k] == v[j].y) {
                  a[k] ^= v[j].x ^ v[j].y;
                }
              }
            }
            w = w * v[j].p % kMod;
          } else {
            w = w * (1 - v[j].p + kMod) % kMod;
          }
        }
        for (int j = 1; j <= n; j++) {
          if (a[j] >= l && a[j] <= r) {
            ans = (ans + w * j) % kMod;
          }
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
}

namespace Sub2 {
const int kMaxN = 8, kMaxL = 5040, kFact[8] = {1, 1, 2, 6, 24, 120, 720, 5040};
int t, a[kMaxN];
LL d[kMaxL], _d[kMaxL];

void R() {
  t = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (a[i] > a[j]) {
        t += kFact[n - i];
      }
    }
  }
}

void W() {
  int x = t;
  for (int i = 1; i <= n; i++) {
    a[i] = x / kFact[n - i];
    x %= kFact[n - i];
  }
  for (int i = n; i >= 1; i--) {
    a[i]++;
    for (int j = i + 1; j <= n; j++) {
      if (a[i] <= a[j]) {
        a[j]++;
      }
    }
  }
}

int main() {
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  R(), d[t] = 1;
  for (int i = 1, o, x, y, p; i <= m; i++) {
    cin >> o >> x;
    if (o <= 2) {
      cin >> p;
    } else if (o == 3) {
      cin >> y >> p;
    } else {
      cin >> y;
    }
    LL ans = 0;
    for (int j = 0; j < kFact[n]; j++) {
      if (!d[j]) {
        continue;
      }
      t = j, W();
      if (o == 1) {
        _d[j] = (_d[j] + d[j] * (1 - p + kMod)) % kMod;
        for (int k = 1; k <= n; k++) {
          if (a[k] < a[x]) {
            a[k]++;
          }
        }
        a[x] = 1, R();
        _d[t] = (_d[t] + d[j] * p) % kMod;
      } else if (o == 2) {
        _d[j] = (_d[j] + d[j] * (1 - p + kMod)) % kMod;
        for (int k = 1; k <= n; k++) {
          if (a[k] > a[x]) {
            a[k]--;
          }
        }
        a[x] = n, R();
        _d[t] = (_d[t] + d[j] * p) % kMod;
      } else if (o == 3) {
        _d[j] = (_d[j] + d[j] * (1 - p + kMod)) % kMod;
        swap(a[x], a[y]);
        R(), _d[t] = (_d[t] + d[j] * p) % kMod;
      } else {
        _d[j] = d[j];
        for (int k = x; k <= y; k++) {
          ans = (ans + a[k] * d[j]) % kMod;
        }
      }
    }
    if (o == 4) {
      cout << ans << '\n';
    }
    for (int j = 0; j < kFact[n]; j++) {
      d[j] = _d[j], _d[j] = 0;
    }
  }
  return 0;
}
}

namespace Sub3 {
const int kMaxN = 5e5 + 1;
LL d[kMaxN];

void Add(int x, int y) {
  for (int i = x; i <= n; i += i & -i) {
    d[i] += y;
  }
}

LL Ask(int x) {
  LL ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

LL Ask(int x, int y) { return Ask(y) - Ask(x - 1); }

int main() {
  for (int i = 1, x; i <= n; i++) {
    cin >> x, Add(i, x);
  }
  for (int i = 1, o, x, y; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> o;
      int w = Ask(x, x);
      for (int j = 1; j <= n; j++) {
        if (Ask(j, j) < w) {
          Add(j, 1);
        }
      }
      Add(x, 1 - w);
    } else if (o == 2) {
      cin >> o;
      int w = Ask(x, x);
      for (int j = 1; j <= n; j++) {
        if (Ask(j, j) > w) {
          Add(j, -1);
        }
      }
      Add(x, n - w);
    } else if (o == 3) {
      cin >> y >> o;
      int wx = Ask(x, x), wy = Ask(y, y);
      Add(x, wy - wx), Add(y, wx - wy);
    } else {
      cin >> y;
      cout << Ask(x, y) << '\n';
    }
  }
  return 0;
}
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  if (n <= 19 && m <= 19 && 0) {
    return Sub1::main();
  } else if (n <= 7) {
    return Sub2::main();
  } else {
    return Sub3::main();
  }
  return 0;
}
