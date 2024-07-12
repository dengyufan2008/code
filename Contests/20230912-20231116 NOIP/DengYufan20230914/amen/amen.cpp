#include <algorithm>
#include <fstream>
#include <vector>
#define LL long long
#define PLL pair<LL, LL>

using namespace std;

ifstream cin("amen.in");
ofstream cout("amen.out");

const LL kMaxN = 2e5 + 2, kInf = 1e9;
struct T {
  LL c, s, mn, mx;
} t[kMaxN];
struct V {
  LL c, l, r;
} v[kMaxN << 6];
LL o, n, m, k, ans, a[kMaxN], l[kMaxN], b[kMaxN], s[kMaxN];
PLL d[kMaxN << 2];
vector<PLL> w, h;

void Pushdown(LL p, LL l, LL r) {
  if (d[p].second) {
    d[p << 1].first = d[p << 1].second = d[p].second;
    d[p << 1 | 1].first = d[p << 1 | 1].second = d[p].second;
    d[p].second = 0;
  }
}

void ChangeMax(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].first = d[p].second = k;
    return;
  }
  Pushdown(p, l, r);
  LL mid = l + r >> 1;
  if (mid >= _l) {
    ChangeMax(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    ChangeMax(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  d[p].first = max(d[p << 1].first, d[p << 1 | 1].first);
}

LL AskMax(LL p, LL l, LL r, LL _l, LL _r) {
  if (l >= _l && r <= _r) {
    return d[p].first;
  }
  Pushdown(p, l, r);
  LL mid = l + r >> 1, ans = -kInf;
  if (mid >= _l) {
    ans = max(ans, AskMax(p << 1, l, mid, _l, _r));
  }
  if (mid < _r) {
    ans = max(ans, AskMax(p << 1 | 1, mid + 1, r, _l, _r));
  }
  return ans;
}

void ChangeVal(LL &p, LL l, LL r, LL x, LL k) {
  v[++::k] = v[p], p = ::k;
  if (l == r) {
    v[p].c = k;
    return;
  }
  LL mid = l + r >> 1;
  mid >= x ? ChangeVal(v[p].l, l, mid, x, k) : ChangeVal(v[p].r, mid + 1, r, x, k);
  v[p].c = min(v[v[p].l].c, v[v[p].r].c);
}

LL FindMin(LL p, LL l, LL r) {
  if (!p || v[p].c == kInf) {
    return 0;
  } else if (l == r) {
    return l;
  }
  LL mid = l + r >> 1;
  return v[p].l && (!v[p].r || v[v[p].l].c < v[v[p].r].c) ? FindMin(v[p].l, l, mid) : FindMin(v[p].r, mid + 1, r);
}

LL FindRange(LL p, LL l, LL r, LL _l, LL _r) {
  if (!p) {
    return 0;
  } else if (l >= _l && r <= _r) {
    return FindMin(p, l, r);
  }
  LL mid = l + r >> 1, ans = 0;
  if (mid >= _l) {
    LL _ans = FindRange(v[p].l, l, mid, _l, _r);
    if (_ans && (!ans || b[ans] > b[_ans])) {
      ans = _ans;
    }
  }
  if (mid < _r) {
    LL _ans = FindRange(v[p].r, mid + 1, r, _l, _r);
    if (_ans && (!ans || b[ans] > b[_ans])) {
      ans = _ans;
    }
  }
  return ans;
}

LL Find(LL c) {
  LL x = 1, y = n;
  while (x <= y) {
    LL mid = x + y >> 1;
    if (b[l[mid]] <= c) {
      x = mid + 1;
    } else {
      y = mid - 1;
    }
  }
  return y;
}

void Init() {
  w.clear(), h.clear(), m = k = 0;
  fill(&s[1], &s[n] + 1, 0), fill(&b[1], &b[n] + 1, 0);
  ChangeMax(1, 1, n, 1, n, -kInf);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  v[0].c = kInf;
  cin >> o;
  while (o--) {
    Init();
    cin >> n;
    for (LL i = 1; i <= n; i++) {
      cin >> a[i];
      l[i] = i;
    }
    sort(l + 1, l + n + 1, [](LL i, LL j) { return a[i] < a[j] || a[i] == a[j] && i < j; });
    for (LL i = 1, j = 1; i <= n && j <= n; i = j) {
      for (; j <= n && a[l[i]] == a[l[j]]; j++) {
      }
      w.push_back({l[i], l[j - 1]});
    }
    sort(w.begin(), w.end(), [](PLL i, PLL j) { return i.first > j.first || i.first == j.first && i.second < j.second; });
    for (auto i : w) {
      if (AskMax(1, 1, n, 1, i.second) <= a[i.second]) {
        h.push_back(i), m += a[i.first] + (i.first != i.second) * a[i.second], b[i.first] = b[i.second] = -kInf;
      }
      ChangeMax(1, 1, n, i.second, i.second, a[i.second]);
    }
    ChangeMax(1, 1, n, 1, n, -1);
    sort(h.begin(), h.end());
    for (LL i = 1, j = 0; i <= n; i++) {
      l[i] = i;
      for (; j < h.size() && h[j].first < i; j++) {
        ChangeMax(1, 1, n, h[j].second, h[j].second, a[h[j].second]);
      }
      if (b[i] != -kInf) {
        b[i] = AskMax(1, 1, n, i, n);
        if (b[i] == -1) {
          ans = -1;
        }
      }
    }
    sort(l + 1, l + n + 1, [](LL i, LL j) { return b[i] < b[j]; });
    t[1] = b[l[1]] == -kInf ? (T){0, 0, kInf, -kInf} : (T){1, b[l[1]], l[1], l[1]};
    for (LL i = 2; i <= n; i++) {
      t[i] = t[i - 1];
      if (b[l[i]] != -kInf) {
        t[i].c++, t[i].s += b[l[i]], t[i].mn = min(t[i].mn, l[i]), t[i].mx = max(t[i].mx, l[i]);
      }
    }
    for (LL i = n; i >= 1; i--) {
      ChangeVal(s[i] = s[i + 1], 1, n, l[i], b[l[i]]);
    }
    ans = ~ans ? m + t[n].s : 0;
    sort(h.begin(), h.end(), [](PLL i, PLL j) { return a[i.first] < a[j.first]; });
    for (LL o = 0, i, p; o < h.size(); o++) {
      if (!o || a[h[o].first] != a[h[o - 1].first] + 1) {
        i = a[h[o].first] - 1, p = Find(i);
      }
      LL l = t[p].mn, r = t[p].mx, c = m + t[n].s - t[p].s + t[p].c * i;
      if (l > h[o].first) {
        LL _l = FindRange(s[p + 1], 1, n, 1, h[o].first - 1);
        if (_l) {
          l = _l, c += i - b[_l];
        }
      }
      if (r < h[o].second) {
        LL _r = FindRange(s[p + 1], 1, n, h[o].second + 1, n);
        if (_r) {
          r = _r, c += i - b[_r];
        }
      }
      if (l < h[o].first && r > h[o].second) {
        ans = max(ans, c);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
