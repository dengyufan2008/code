#include <algorithm>
#include <ctime>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 301, kMaxM = kMaxN * kMaxN, kMod = 998244353;
struct PII {
  int s, t;
};
struct V {
  int s, t, a[kMaxN];
} v[kMaxM];
struct L {
  int s, t, p;
} l[kMaxM * kMaxN];
int s, t, n, m, w, lc, lt[kMaxM * 4], c[kMaxM * 4], r[kMaxM], _r[kMaxM];
LL ans1, ans2, f[kMaxN] = {1};
PII a[kMaxN];

LL Pow(LL x, LL y = kMod - 2) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

int Dis(PII x, PII y) {
  int p = max(abs(x.s - y.s), abs(x.t - y.t)) - 1;
  if (y.s == x.s + p + 1 && y.t != x.t - p - 1) {
    return p * p * 4 + p * 5 + 2 + y.t - x.t;
  } else if (y.t == x.t + p + 1) {
    return p * p * 4 + p * 7 + 4 + x.s - y.s;
  } else if (y.s == x.s - p - 1) {
    return p * p * 4 + p * 9 + 6 + x.t - y.t;
  } else {
    return p * p * 4 + p * 11 + 8 + y.s - x.s;
  }
}

void Insert(int x) {
  for (int i = m; i >= 1; i--) {
    f[i] = (f[i] + f[i - 1] * x % kMod) % kMod;
  }
}

void Delete(int x) {
  for (int i = 1; i <= m; i++) {
    f[i] = (f[i] - f[i - 1] * x % kMod + kMod) % kMod;
  }
}

void Split(int x) {
  if (x < s * t && v[x].s == v[x + 1].s) {
    int y = v[x].t;
    Delete(v[x].t - v[x].s + 1);
    Insert(x - v[x].s + 1), Insert(v[x].t - x);
    for (int i = x; i >= 1 && v[i].s == v[x].s; i--) {
      v[i].t = x;
    }
    for (int i = x + 1; i <= s * t && v[i].t == y; i++) {
      v[i].s = x + 1;
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s >> t >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].s >> a[i].t;
  }
  if (m == 1) {
    cout << 0;
    return 0;
  }
  for (int i = 1; i <= s; i++) {
    for (int j = 1; j <= t; j++) {
      int p = (i - 1) * t + j;
      for (int k = 1; k <= n; k++) {
        v[p].a[k] = Dis({i, j}, a[k]);
      }
      v[p].s = 1, v[p].t = s * t;
      sort(v[p].a + 1, v[p].a + n + 1);
      w = max(w, v[p].a[n]), _r[p] = p;
    }
  }
  for (int i = n; i >= 1; i--) {
    fill(&c[1], &c[w] + 1, 0);
    for (int j = 1; j <= s * t; j++) {
      c[v[j].a[i]]++;
    }
    for (int j = w; j >= 1; j--) {
      c[j] += c[j + 1];
    }
    for (int j = s * t; j >= 1; j--) {
      r[_r[j]] = c[v[_r[j]].a[i]]--;
    }
    for (int j = 1; j <= s * t; j++) {
      _r[r[j]] = j;
    }
  }
  for (int i = 1; i <= s * t; i++) {
    while (r[i] != i) {
      swap(v[i], v[r[i]]), swap(r[i], r[r[i]]);
    }
  }
  for (int i = 1; i <= s * t; i++) {
    for (int j = 1; j <= n; j++) {
      if (lt[v[i].a[j]] && l[lt[v[i].a[j]]].t == i - 1) {
        l[lt[v[i].a[j]]].t = i;
      } else {
        l[++lc] = {i, i, lt[v[i].a[j]]}, lt[v[i].a[j]] = lc;
      }
    }
  }
  Insert(s * t);
  for (int i = 1, p = 0; i <= w; i++) {
    for (int j = lt[i]; j; j = l[j].p) {
      Split(l[j].s - 1), Split(l[j].t);
    }
    ans1 = (ans1 + f[m] - p + kMod) % kMod;
    ans2 = (ans2 + (f[m] - p + kMod) % kMod * i % kMod) % kMod;
    p = f[m];
  }
  cout << ans2 * Pow(ans1) % kMod;
  cout << '\n' << clock();
  return 0;
}
