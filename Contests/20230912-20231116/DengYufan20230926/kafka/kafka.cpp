#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("kafka.in");
ofstream cout("kafka.out");

const LL kMaxN = 5e5 + 1, kV = 998244353, kMod = 1e9 + 7;
struct V {
  LL i, o, l, r, d, w, sw, p;
  bool b;
  vector<pair<LL, LL>> e;
} v[kMaxN];
struct H {
  LL l, r, x, k;
};
LL t, n, m, x, y, k, ans1, ans2, a[kMaxN];
char ch[kMaxN];
bool o;
pair<LL, LL> d[kMaxN << 2];
vector<H> h;
queue<LL> q;

LL R(LL x, LL y) {
  return (x - 1) * m + y;
}

LL Pow(LL x, LL y) {
  LL ans = 1;
  for (LL i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

void Init() {
  o = k = ans1 = ans2 = 0, h.clear();
  fill(&v[1], &v[n * m] + 1, v[0]);
  fill(&d[1], &d[n * m << 2] + 1, d[0]);
  while (!q.empty()) {
    q.pop();
  }
}

void AddEdge(LL x, LL y, LL w) {
  v[x].o++, v[y].i = x, v[x].e.push_back({y, w});
}

void Input() {
  cin >> n >> m >> x >> y;
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      cin >> ch[R(i, j)];
      o |= ch[R(i, j)] == 'X';
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      if (ch[R(i, j)] == 'U' && i > 1 && ch[R(i - 1, j)] != 'X') {
        a[R(i, j)] = 1, AddEdge(R(i - 1, j), R(i + 1, j), y);
      } else if (ch[R(i, j)] == 'D' && i < n && ch[R(i + 1, j)] != 'X') {
        a[R(i, j)] = 2, AddEdge(R(i + 1, j), R(i - 1, j), y);
      } else if (ch[R(i, j)] == 'L' && j > 1 && ch[R(i, j - 1)] != 'X') {
        a[R(i, j)] = 3, AddEdge(R(i, j - 1), R(i, j + 1), x);
      } else if (ch[R(i, j)] == 'R' && j < m && ch[R(i, j + 1)] != 'X') {
        a[R(i, j)] = 4, AddEdge(R(i, j + 1), R(i, j - 1), x);
      }
    }
  }
}

void TopSort() {
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      if (!v[R(i, j)].o) {
        q.push(R(i, j));
      }
    }
  }
  for (; !q.empty(); q.pop()) {
    if (v[q.front()].i && --v[v[q.front()].i].o == 0) {
      q.push(v[q.front()].i);
    }
  }
}

pair<LL, LL> Next(LL x) {
  for (auto i : v[x].e) {
    if (v[i.first].i == 0 || v[i.first].o) {
      return i;
    }
  }
  return {x, 0};
}

void CalcD(LL x) {
  LL s = 0, w = 0;
  vector<pair<LL, LL>> l(1);
  l.push_back({x, 0});
  for (auto i = Next(x);; i = Next(i.first)) {
    l[l.size() - 1].second = i.second, l.push_back(i);
    s += v[i.first].r - v[i.first].l + 1, w += i.second;
    if (i.first == x) {
      break;
    }
  }
  l.pop_back();
  for (int i = 1, j = s; i < l.size(); i++) {
    j -= v[l[i].first].r - v[l[i].first].l + 1;
    v[x].d = (v[x].d + l[i].second * j % kMod) % kMod;
  }
  for (int i = 1; i < l.size() - 1; i++) {
    v[l[i + 1].first].d = (v[l[i].first].d - (s - v[l[i].first].r + v[l[i].first].l - 1) * l[i].second % kMod +
                           (w - l[i].second) * (v[l[i].first].r - v[l[i].first].l + 1) % kMod + kMod) %
                          kMod;
  }
}

void CalcP(LL x, LL p) {
  if (!v[x].p) {
    v[x].p = p;
    for (auto i : v[x].e) {
      CalcP(i.first, p);
    }
  }
}

void T(LL x) {
  if (!v[x].b) {
    v[x].b = 1, v[x].l = v[x].r = ++k;
    for (auto i : v[x].e) {
      if (v[i.first].i && v[i.first].o == 0) {
        T(i.first);
        v[x].l = min(v[x].l, v[i.first].l);
        v[x].r = max(v[x].r, v[i.first].r);
        v[x].w = (v[x].w + v[i.first].w + i.second * (v[i.first].r - v[i.first].l + 1) % kMod) % kMod;
      }
    }
  }
}

void Walk() {
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      if (v[R(i, j)].i == 0 || v[R(i, j)].o) {
        T(R(i, j));
      }
    }
  }
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      if (v[R(i, j)].i == 0 || v[R(i, j)].o) {
        if (!v[R(i, j)].p) {
          CalcD(R(i, j));
        }
        CalcP(R(i, j), R(i, j));
        v[v[R(i, j)].p].sw = (v[v[R(i, j)].p].sw + v[R(i, j)].w) % kMod;
      }
    }
  }
}

void Calc(LL x, LL y) {
  h.push_back({v[x].l, v[x].r, v[y].l, 1});
  h.push_back({v[x].l, v[x].r, v[y].r + 1, -1});
  LL t = (v[x].i == 0 || v[x].o ? v[v[x].p].sw + v[x].d : v[x].w) + (v[y].i == 0 || v[y].o ? v[v[y].p].sw + v[y].d : v[y].w);
  ans2 = (ans2 + t % kMod * Pow(kV, x + y) % kMod) % kMod;
}

void CalcAns2() {
  for (LL i = 1; i <= n; i++) {
    for (LL j = 1; j <= m; j++) {
      if (ch[R(i, j)] == 'U') {
        i + j & 1 ? Calc(R(i, j), R(i + 1, j)) : Calc(R(i + 1, j), R(i, j));
      } else if (ch[R(i, j)] == 'L') {
        i + j & 1 ? Calc(R(i, j), R(i, j + 1)) : Calc(R(i, j + 1), R(i, j));
      }
    }
  }
}

void Update(LL p, LL l, LL r) {
  if (l < r) {
    d[p].first = d[p].second ? r - l + 1 : d[p << 1].first + d[p << 1 | 1].first;
  } else {
    d[p].first = d[p].second > 0;
  }
}

void Add(LL p, LL l, LL r, LL _l, LL _r, LL k) {
  if (l >= _l && r <= _r) {
    d[p].second += k, Update(p, l, r);
    return;
  }
  LL mid = l + r >> 1;
  if (mid >= _l) {
    Add(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  Update(p, l, r);
}

void CalcAns1() {
  sort(h.begin(), h.end(), [](H i, H j) { return i.x < j.x; });
  for (LL i = 0, j; i < h.size(); i = j) {
    ans1 = (ans1 + (h[i].x - h[i - 1].x) * d[1].first % kMod) % kMod;
    for (j = i; j < h.size() && h[i].x == h[j].x; j++) {
      Add(1, 1, n * m, h[j].l, h[j].r, h[j].k);
    }
  }
}

void Print() {
  cout << (o ? ans2 : ans1) << '\n';
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> t;
  while (t--) {
    Init(), Input(), TopSort(), Walk(), CalcAns2(), CalcAns1(), Print();
  }
  return 0;
}
