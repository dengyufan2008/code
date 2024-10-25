#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("path.in");
ofstream cout("path.out");

const int kMaxN = 5e5 + 1;
struct A {
  int x, y;
} a[kMaxN];
struct Q {
  int x, y, o;
} q[kMaxN];
int n, m, k, p[kMaxN];
unsigned ans[kMaxN];

namespace Sub1 {
const int kMaxN = 5e5 + 1;
int d[kMaxN];

void Add(int x, int y) {
  for (int i = x; i <= n; i += i & -i) {
    d[i] += y;
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

int main() {
  sort(a + 1, a + m + 1, [](A i, A j) {
    return i.x < j.x;
  });
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    return i.x < j.x;
  });
  for (int i = 1; i <= m; i++) {
    Add(a[i].y, 1);
  }
  for (int i = 1, j = 1; i <= k; i++) {
    for (; j <= m && a[j].x < q[i].x; j++) {
      Add(a[j].y, -1);
    }
    ans[q[i].o] = Ask(q[i].y) * 2;
  }
  for (int i = 1; i <= k; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
}  // namespace Sub1

namespace Sub2 {
const int kMaxN = 2e5 + 1, kB = 900;
int b[kMaxN], c[kMaxN];
unsigned s[kMaxN];
vector<int> e[kMaxN];

int main() {
  for (int i = 1; i <= m; i++) {
    e[a[i].x].push_back(a[i].y);
    e[a[i].y].push_back(a[i].x);
  }
  for (int i = 1, j = 1; i <= n; i++) {
    s[i] = s[i - 1] + e[i].size();
    if (e[i].size() >= kB) {
      j++, b[i] = j, j++;
    } else if (s[i] / kB > s[i - 1] / kB) {
      j++, b[i] = j;
    } else {
      b[i] = j;
    }
  }
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    return b[i.x] == b[j.x] ? i.y < j.y : i.x < j.x;
  });
  for (int i = 1; i <= k; i++) {
    static int l, r;
    static unsigned w;
    if (i == 1 || b[q[i].x] > b[q[i - 1].x]) {
      l = q[i].x, r = l - 1, w = 0;
      for (int j = 1; j <= n; j++) {
        c[j] = 0;
      }
    }
    for (; r < q[i].y;) {
      r++;
      for (int j : e[r]) {
        w += c[j], c[j]++;
      }
    }
    for (; l < q[i].x;) {
      for (int j : e[l]) {
        c[j]--, w -= c[j];
      }
      l++;
    }
    for (; l > q[i].x;) {
      l--;
      for (int j : e[l]) {
        w += c[j], c[j]++;
      }
    }
    ans[q[i].o] = w * 2 + s[q[i].y] - s[q[i].x - 1];
  }
  for (int i = 1; i <= k; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
}  // namespace Sub2

namespace Sub3 {
const int kMaxN = 1e5 + 1, kB = 350, kP = 3000;
struct D {
  int l, r, o;
};
int u, b[kMaxN], c[kMaxN], g[kMaxN];
unsigned h[kMaxN], h0[kMaxN], h1[kMaxN], res[kMaxN * 4], ans[kMaxN];
vector<int> e[kMaxN], p[kMaxN];
vector<D> d[kMaxN];

void Add(int x, int w) {
  if (e[x].size() <= kP) {
    for (int i : e[x]) {
      c[i] += w;
    }
  } else {
    g[x] += w;
  }
}

unsigned Ask(int x) {
  unsigned ans = c[x];
  for (int i : p[x]) {
    ans += g[i];
  }
  return ans;
}

void Init() {
  for (int i = 1; i <= m; i++) {
    e[a[i].x].push_back(a[i].y);
    e[a[i].y].push_back(a[i].x);
  }
  for (int i = 1; i <= n; i++) {
    if (e[i].size() > kP) {
      for (int j : e[i]) {
        p[j].push_back(i);
      }
    }
  }
  for (int i = 1, j = 1, s = 0; i <= n; i++) {
    if (e[i].size() > kB) {
      j++, b[i] = j, j++, s = 0;
    } else if (s + (int)e[i].size() > kB) {
      b[i] = j, j++, s = 0;
    } else {
      b[i] = j, s += e[i].size();
    }
  }
  sort(q + 1, q + k + 1, [](Q i, Q j) {
    if (b[i.x] == b[j.x]) {
      return b[i.x] & 1 ? i.y < j.y : i.y > j.y;
    } else {
      return i.x < j.x;
    }
  });
}

void CalcQuery() {
  for (int i = 1; i <= k; i++) {
    static int l = 1, r = 0;
    if (r < q[i].y) {
      l > 1 ? d[l - 1].push_back({r + 1, q[i].y, ++u}) : void();
      r = q[i].y;
    }
    if (l > q[i].x) {
      d[r].push_back({q[i].x, l - 1, ++u});
      l = q[i].x;
    }
    if (l < q[i].x) {
      d[r].push_back({l, q[i].x - 1, ++u});
      l = q[i].x;
    }
    if (r > q[i].y) {
      l > 1 ? d[l - 1].push_back({q[i].y + 1, r, ++u}) : void();
      r = q[i].y;
    }
  }
}

void CalcResult() {
  for (int i = 1; i <= n; i++) {
    for (int j : e[i]) {
      Add(j, 1), h[i] += Ask(j);
    }
    for (int j : e[i]) {
      Add(j, -1);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j : e[i]) {
      Add(j, 1);
    }
    for (int j : e[i]) {
      h0[i] += Ask(j);
    }
    if (i < n) {
      for (int j : e[i + 1]) {
        h1[i] += Ask(j);
      }
    }
    for (D j : d[i]) {
      for (int k = j.l; k <= j.r; k++) {
        for (int x : e[k]) {
          res[j.o] += Ask(x);
        }
      }
    }
  }
}

void CalcAns() {
  for (int i = 1; i <= k; i++) {
    static int l = 1, r = 0, o = 0;
    static unsigned w = 0;
    if (r < q[i].y) {
      l > 1 ? w -= res[++o] : 0;
      for (; r < q[i].y;) {
        r++, w += h[r] + h1[r - 1];
      }
    }
    if (l > q[i].x) {
      w += res[++o];
      for (; l > q[i].x;) {
        l--, w += h[l] - h0[l];
      }
    }
    if (l < q[i].x) {
      w -= res[++o];
      for (; l < q[i].x;) {
        w += h[l] + h1[l - 1], l++;
      }
    }
    if (r > q[i].y) {
      l > 1 ? w += res[++o] : 0;
      for (; r > q[i].y;) {
        w += h[r] - h0[r], r--;
      }
    }
    ans[q[i].o] = w * 2;
  }
}

int main() {
  Init(), CalcQuery(), CalcResult(), CalcAns();
  for (int i = 1; i <= k; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
}  // namespace Sub3

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  int u;
  cin >> n >> m >> k >> u;
  for (int i = 1; i <= m; i++) {
    cin >> a[i].x >> a[i].y;
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, p[x] = i;
  }
  for (int i = 1; i <= k; i++) {
    cin >> q[i].x >> q[i].y, q[i].o = i;
  }
  for (int i = 1; i <= m; i++) {
    a[i].x = p[a[i].x], a[i].y = p[a[i].y];
    a[i].x > a[i].y ? swap(a[i].x, a[i].y) : void();
  }
  if (u == 2) {
    return Sub1::main();
  } else if (u == 3) {
    return Sub2::main();
  } else {
    return Sub3::main();
  }
}
