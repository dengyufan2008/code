#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 5e5 + 2;
struct V {
  int mn, t;
} v[kMaxN << 2];
int t, n, m, ans, a[kMaxN], d[kMaxN], s[kMaxN], l[kMaxN];
bool b[kMaxN];
vector<int> p[kMaxN];

void Pushdown(int p) {
  if (v[p].t) {
    v[p << 1].mn += v[p].t, v[p << 1].t += v[p].t;
    v[p << 1 | 1].mn += v[p].t, v[p << 1 | 1].t += v[p].t;
    v[p].t = 0;
  }
}

void Set(int p, int l, int r, int x, int k) {
  if (l == r) {
    v[p].mn = k;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= x) {
    Set(p << 1, l, mid, x, k);
  } else {
    Set(p << 1 | 1, mid + 1, r, x, k);
  }
  v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
}

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    v[p].mn += k, v[p].t += k;
    return;
  }
  Pushdown(p);
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    m = 0, ans = kMaxN;
    fill(&b[1], &b[n] + 1, 0);
    fill(&d[1], &d[n] + 1, 0);
    p[0].clear(), fill(&p[1], &p[n] + 1, p[0]);
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i], s[i] = s[i - 1];
      if (!a[i]) {
        s[i]++, l[++m] = i;
      }
    }
    l[m + 1] = n + 1;
    for (int i = l[m >> 1]; i >= 1; i--) {
      if (a[i] && !d[a[i]]) {
        d[a[i]] = i;
      }
    }
    for (int i = l[m >> 1] + 1; i <= n; i++) {
      if (a[i] && !b[a[i]]) {
        b[a[i]] = 1, p[d[a[i]]].push_back(i);
      }
    }
    for (int i = l[m >> 1]; i >= 1; i--) {
      if (d[a[i]] && !b[a[i]]) {
        b[a[i]] = 1, p[d[a[i]]].push_back(n + 1);
      }
    }
    for (int i = 1; i <= l[m >> 1]; i++) {
      Set(1, 1, n + 1, i, kMaxN);
    }
    for (int i = l[m >> 1] + 1; i <= n + 1; i++) {
      Set(1, 1, n + 1, i, m - s[i - 1]);
    }
    for (int i = l[m >> 1]; i >= 0; i--) {
      for (int j : p[i]) {
        Add(1, 1, n + 1, l[m >> 1] + 1, n + 1, 1);
      }
    }
    for (int i = 0; i <= l[m >> 1]; i++) {
      for (int j : p[i]) {
        if (l[m >> 1] < l[s[j - 1] + 1]) {
          Add(1, 1, n + 1, l[m >> 1] + 1, l[s[j - 1] + 1], -1);
        }
      }
      ans = min(ans, v[1].mn + s[i]);
    }
    cout << min(ans, m >> 1) << '\n';
  }
  return 0;
}
