#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 2e5, kMaxM = kMaxN + 1 << 1, kB = 300;
struct Q {
  int l, r, x, o;
  unsigned ans;
} q[kMaxN];
int n, m, c[kMaxN], lcp[kMaxN], lcs[kMaxN];
unsigned a[kMaxN];
string s;

class Sam {
  struct V {
    int f, l, e[2];
  } v[kMaxM];
  int m;

 public:
  void Build() {
    int r = m = 1;
    for (int i = 0; i < n; i++) {
      int x = s[i] - '0', p = r;
      v[++m].l = v[p].l + 1;
      for (; p && !v[p].e[x]; p = v[p].f) {
        v[p].e[x] = m;
      }
      if (p) {
        int q = v[p].e[x];
        if (v[p].l + 1 == v[q].l) {
          v[m].f = q, r = m;
        } else {
          v[++m] = v[q], v[m].l = v[p].l + 1;
          for (; p && v[p].e[x] == q; p = v[p].f) {
            v[p].e[x] = m;
          }
          v[m - 1].f = v[q].f = m, r = m - 1;
        }
      } else {
        v[m].f = 1, r = m;
      }
    }
  }

  int Trans(int x, char c) { return v[x].e[c - '0']; }
} sam;

unsigned Force(int l, int r) {  // 暴力计算一个区间的答案
  static int nt[kMaxN];
  unsigned ans = 0;
  nt[l] = l - 1;
  for (int i = l + 1, j; i <= r; i++) {
    for (j = nt[i - 1]; j >= l && s[j + 1] != s[i]; j = nt[j]) {
    }
    nt[i] = s[j + 1] == s[i] ? j + 1 : l - 1;
  }
  c[l - 1] = 0;
  for (int i = l; i <= r; i++) {
    c[i] = c[nt[i]] + 1;
    ans += a[i] * c[i];
  }
  return ans;
}

void Calc1() {  // 没跨过块边界的前缀的贡献
  static int p[kMaxN];
  static unsigned w[kMaxM];
  static vector<int> v[kMaxN];
  sam.Build();
  for (int l = 0; l < kB; l++) {  // 统计长度为 l+1 的前缀的答案
    if (l) {
      for (int i = n - 1; i >= l; i--) {
        p[i] = sam.Trans(p[i - 1], s[i]);
      }
    } else {
      for (int i = 0; i < n; i++) {
        p[i] = sam.Trans(1, s[i]);
      }
    }
    for (int i = 0; i < m; i++) {
      if (q[i].x && q[i].x - q[i].l >= l) {
        q[i].l || l ? v[q[i].l + l - 1].push_back(i) : void();
        v[q[i].r].push_back(i);
      }
    }
    for (int i = l; i < n; i++) {
      w[p[i]] += a[i];
      for (int j : v[i]) {
        i < q[j].x ? q[j].ans -= w[p[q[j].l + l]] : q[j].ans += w[p[q[j].l + l]];
      }
      v[i].clear();
    }
    for (int i = l; i < n; i++) {  // 清空
      w[p[i]] -= a[i];
    }
  }
}

void Calc2() {  // 跨过了块边界的前缀的贡献的前半部分
  static unsigned w[kMaxN];
  sort(q, q + m, [](Q i, Q j) {
    return i.x < j.x;
  });
  for (int l = 0, r = 0; l < m; l = r) {  // 先套用直接截去块边界以前的字符串的答案
    int x = q[l].x;
    for (; r < m && q[l].x == q[r].x; r++) {
    }
    if (x) {
      Force(x + 1, n - 1), w[x] = 0;
      for (int i = x + 1; i < n; i++) {
        w[i] = w[i - 1] + a[i] * c[i];
      }
      for (int i = l; i < r; i++) {
        q[i].ans += w[q[i].r];
      }
    }
  }
}

void Kmp(int *w, int *l, int n, int _n, int m, string s, string t, bool u) {
  for (int i = u, j, k = 0; i < _n; i++) {
    if (i < k) {
      int o = w[i - j];
      if (i + o < k) {
        l[i] = o;
        continue;
      }
    } else {
      k = i;
    }
    for (j = i; k < n && k < m + i && s[k] == t[k - i]; k++) {
    }
    l[i] = k - j;
  }
}

void CalcLcp(int x) {  // 计算 >=x 的位置与 x 的 LCP
  string t = s.substr(x);
  lcp[x] = n - x, Kmp(lcp + x, lcp + x, n - x, n - x, n - x, t, t, 1);
}

void CalcLcs(int x) {  // 计算 >=x 的位置与 x 的 LCS
  static int w[kMaxN];
  reverse(s.begin(), s.end());
  string t = s.substr(n - x - 1);
  lcs[0] = x + 1, Kmp(w, w, x + 1, x + 1, x + 1, t, t, 1);
  Kmp(w, lcs, n, n - x, x + 1, s, t, 0);
  reverse(lcs, lcs + n);
  reverse(s.begin(), s.end());
}

void Calc3() {  // 跨过了块边界的前缀的贡献的后半部分
  static unsigned b[kMaxN], d[kB], w[kB];
  static vector<int> e[kMaxN], v[kMaxN];
  b[0] = a[0];
  for (int i = 1; i < n; i++) {
    b[i] = b[i - 1] + a[i];
  }
  for (int l = 0, r = 0; l < m; l = r) {  // 再减去不合法的位置的贡献
    int x = q[l].x;
    for (; r < m && q[l].x == q[r].x; r++) {
    }
    if (x) {
      CalcLcp(x + 1), CalcLcs(x);
      for (int i = l; i < r; i++) {
        v[q[i].r].push_back(i);
      }
      fill(d, d + kB, 0), fill(w, w + kB, 0);
      for (int i = x + 1; i < n; i++) {
        if (lcs[i - 1] < kB) {
          d[lcs[i - 1]]++, w[lcs[i - 1]] -= b[i - 1];
          if (i + lcp[i] < n) {
            e[i + lcp[i]].push_back(i);
          }
        }
        for (int j : e[i]) {
          d[lcs[j - 1]]--, w[lcs[j - 1]] += b[i - 1];
        }
        for (int j : v[i]) {
          for (int k = 0; k <= q[j].x - q[j].l; k++) {
            q[j].ans -= d[k] * b[i] + w[k];
          }
        }
        e[i].clear(), v[i].clear();
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    cin >> q[i].l >> q[i].r;
    q[i].l--, q[i].r--, q[i].o = i;
    if (q[i].l / kB < q[i].r / kB) {
      q[i].x = q[i].l / kB * kB + kB - 1;
    } else {
      q[i].ans = Force(q[i].l, q[i].r);
    }
  }
  Calc1(), Calc2(), Calc3();
  sort(q, q + m, [](Q i, Q j) {
    return i.o < j.o;
  });
  for (int i = 0; i < m; i++) {
    cout << q[i].ans << '\n';
  }
  return 0;
}
