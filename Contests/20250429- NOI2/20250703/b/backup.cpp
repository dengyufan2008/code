#include <fstream>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 5e4 + 1, kMaxL = 30;
struct V {
  int c, s[2];
} v[kMaxN * kMaxL];
int t, n, m, k, ans[kMaxN];

void Insert(int x) {
  v[1].c++;
  for (int i = kMaxL - 1, p = 1; i >= 0; i--) {
    bool o = x >> i & 1;
    !v[p].s[o] && (v[p].s[o] = ++m);
    p = v[p].s[o], v[p].c++;
  }
}

// 将 p 子树和 q 子树内的数匹配, 使得匹配的数对异或大于等于 x 的后 d 位, 求最大匹配
int Calc2(int p, int q, int x, int d) {
  if (!p || !q) {
    return 0;
  } else if (d < 0) {
    return min(v[p].c, v[q].c);
  } else if (x >> d & 1) {
    return Calc2(v[p].s[0], v[q].s[1], x, d - 1) + Calc2(v[p].s[1], v[q].s[0], x, d - 1);
  }
  int pl = v[v[p].s[0]].c, pr = v[v[p].s[1]].c;
  int ql = v[v[q].s[0]].c, qr = v[v[q].s[1]].c;
  int w1 = min(pl, qr), w2 = min(pr, ql), w = w1 + w2;
  pl -= w1, qr -= w1, pr -= w2, ql -= w2;
  if (pl && ql) {
    return w + min(Calc2(v[p].s[0], v[q].s[0], x, d - 1), min(pl, ql));
  } else if (pr && qr) {
    return w + min(Calc2(v[p].s[1], v[q].s[1], x, d - 1), min(pr, qr));
  } else {
    return w;
  }
}

// 将 p 子树内的数染色, 至少染成 ans 种颜色才能让同色组内两两异或大于等于 x 的后 d 位
int Calc(int p, int x, int d) {
  if (!p || d < 0) {
    return 1;
  } else if (x >> d & 1) {
    return v[v[p].s[0]].c + v[v[p].s[1]].c - Calc2(v[p].s[0], v[p].s[1], x, d - 1);
  } else {
    return max(Calc(v[p].s[0], x, d - 1), Calc(v[p].s[1], x, d - 1));
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n >> k, m = 1;
    for (int i = 1, x; i <= n; i++) {
      cin >> x, Insert(x);
    }
    int l = 1, r = (1 << kMaxL) - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Calc(1, mid, kMaxL - 1) <= k) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << r << '\n';
    fill(&v[1], &v[m] + 1, v[0]);
  }
  return 0;
}
