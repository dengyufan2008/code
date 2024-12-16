#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("h.in");
ofstream cout("h.out");

const LL kMaxN = 2.5e5 + 2, kInf = 1e18;
struct E {
  int l, r, w;
};
struct V {
  int l, r, c;
  LL s;
} v[kMaxN * 20];
int n, m, b[kMaxN], c[kMaxN], s[kMaxN], p[kMaxN], o[kMaxN], f[kMaxN];
LL ans, a[kMaxN];
bool u[kMaxN];
vector<E> e;

void Add(int &p, int l, int r, int x) {
  static int k = 0;
  v[++k] = v[p], p = k;
  if (l == r) {
    v[p].c = 1, v[p].s = b[o[x]];
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Add(v[p].l, l, mid, x);
  } else {
    Add(v[p].r, mid + 1, r, x);
  }
  v[p].c = v[v[p].l].c + v[v[p].r].c;
  v[p].s = v[v[p].l].s + v[v[p].r].s;
}

LL AskSum(int p, int q, int l, int r, int x) {
  if (x == v[q].c - v[p].c) {
    return v[q].s - v[p].s;
  }
  int mid = l + r >> 1, y = v[v[q].r].c - v[v[p].r].c;
  if (x <= y) {
    return AskSum(v[p].r, v[q].r, mid + 1, r, x);
  } else {
    return AskSum(v[p].l, v[q].l, l, mid, x - y) + v[v[q].r].s - v[v[p].r].s;
  }
}

int AskVal(int p, int q, int l, int r, int x) {
  if (l == r) {
    return b[o[l]];
  }
  int mid = l + r >> 1, y = v[v[q].r].c - v[v[p].r].c;
  if (x <= y) {
    return AskVal(v[p].r, v[q].r, mid + 1, r, x);
  } else {
    return AskVal(v[p].l, v[q].l, l, mid, x - y);
  }
}

int AskVal(int l, int r) { return AskVal(s[l - 1], s[r], 1, n, m); }

LL CalcW(int l, int r) { return AskSum(s[l - 1], s[r], 1, n, m) - a[r] + a[l - 1]; }

void CalcP(int l, int r, int pl, int pr) {
  if (l > r || pl == pr) {
    for (int i = l; i <= r; i++) {
      p[i] = pl, ans = max(ans, CalcW(pl, i));
    }
    return;
  }
  int mid = l + r >> 1;
  LL mx = -kInf;
  for (int i = pl; i <= pr && i <= mid - m + 1; i++) {
    LL w = CalcW(i, mid);
    if (w >= mx) {
      mx = w, p[mid] = i;
    }
  }
  ans = max(ans, mx);
  CalcP(l, mid - 1, pl, p[mid]), CalcP(mid + 1, r, p[mid], pr);
}

int GetRoot(int x) { return f[x] == x ? x : f[x] = GetRoot(f[x]); }

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], a[i] += a[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    cin >> b[i], o[i] = f[i] = i;
  }
  f[n + 1] = n + 1;
  sort(o + 1, o + n + 1, [](int i, int j) {
    return b[i] < b[j];
  });
  for (int i = 1; i <= n; i++) {
    c[o[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    Add(s[i] = s[i - 1], 1, n, c[i]);
  }
  ans = -kInf, CalcP(m, n, 1, n - m + 1), cout << ans << '\n';
  for (int i = m, j = 1; i <= n; i++) {
    if (CalcW(p[i], i) == ans) {
      for (; j < p[i]; j++) {
        if (CalcW(j, i) == ans) {
          e.push_back({j, i, AskVal(j, i)});
        }
      }
      e.push_back({j, i, AskVal(j, i)});
    }
  }
  sort(e.begin(), e.end(), [](E i, E j) {
    return i.w < j.w;
  });
  for (int i = 0, j = 1; i < e.size(); i++) {
    for (; j <= n && b[o[j]] < e[i].w; j++) {
      if (GetRoot(o[j]) == o[j]) {
        f[o[j]] = GetRoot(o[j] + 1);
      }
    }
    for (int t = GetRoot(e[i].l); t <= e[i].r; t = GetRoot(t)) {
      f[t] = GetRoot(t + 1), u[t] = 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << u[i];
  }
  cout << '\n';
  return 0;
}
