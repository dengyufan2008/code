#include <fstream>
#include <queue>
#define PII pair<int, int>
#define LL long long

using namespace std;

ifstream cin("r.in");
ofstream cout("r.out");

const int kMaxN = 1e5 + 1, kV = 131071;
const int kMod1 = 1e9 + 7, kMod2 = 715876003;
struct D {
  int l, r;
  LL h1, h2;
} d[kMaxN * 54];
struct V {
  int p, r;
  bool b;
  vector<PII> e;
} v[kMaxN];
int n, m, k, s;
LL pw1[kMaxN], pw2[kMaxN];

bool Ask(int p, int q, int l, int r) {
  if (!p || !q) {
    return q;
  } else if (l == r) {
    return d[p].h1 < d[q].h1;
  }
  int mid = l + r >> 1;
  if (d[d[p].r].h1 != d[d[q].r].h1 || d[d[p].r].h2 != d[d[q].r].h2) {
    return Ask(d[p].r, d[q].r, mid + 1, r);
  } else {
    return Ask(d[p].l, d[q].l, l, mid);
  }
}

bool Cmp(int p, int q) {
  return (p || q) && Ask(p, q, 0, kV);
}

int Find(int p, int l, int r, int x) {
  if (!p || !d[p].h1 && !d[p].h2) {
    return max(x, l);
  } else if ((d[p].h1 + 1) % kMod1 == pw1[r - l + 1] &&
             (d[p].h2 + 1) % kMod2 == pw2[r - l + 1]) {
    return -1;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    int ans = Find(d[p].l, l, mid, x);
    if (~ans) {
      return ans;
    }
  }
  return Find(d[p].r, mid + 1, r, x);
}

void Pushup(int p, int len) {
  d[p].h1 = (d[d[p].l].h1 + d[d[p].r].h1 * pw1[len]) % kMod1;
  d[p].h2 = (d[d[p].l].h2 + d[d[p].r].h2 * pw2[len]) % kMod2;
}

void Clear(int &p, int l, int r, int _l, int _r) {
  d[++k] = d[p], p = k;
  if (l >= _l && r <= _r) {
    p = 0;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Clear(d[p].l, l, mid, _l, _r);
  }
  if (mid < _r) {
    Clear(d[p].r, mid + 1, r, _l, _r);
  }
  Pushup(p, mid - l + 1);
}

void Set(int &p, int l, int r, int x) {
  d[++k] = d[p], p = k;
  if (l == r) {
    d[p].h1 = d[p].h2 = 1;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Set(d[p].l, l, mid, x);
  } else {
    Set(d[p].r, mid + 1, r, x);
  }
  Pushup(p, mid - l + 1);
}

void Add(int &p, int x) {
  int w = Find(p, 0, kV, x);
  if (x < w) {
    Clear(p, 0, kV, x, w - 1);
  }
  Set(p, 0, kV, w);
}

auto cmp = [](PII p, PII q) { return Cmp(q.second, p.second); };
priority_queue<PII, vector<PII>, decltype(cmp)> q(cmp);

void Dij() {
  int x, p;
  v[s].p = k = 1;
  for (q.push({s, 0}); !q.empty();) {
    x = q.top().first, q.pop();
    if (!v[x].b) {
      v[x].b = 1;
      for (auto i : v[x].e) {
        if (!v[i.first].b) {
          p = v[x].p, Add(p, i.second);
          if (!v[i.first].p || Cmp(p, v[i.first].p)) {
            v[i.first].p = p, v[i.first].r = x;
            q.push({i.first, p});
          }
        }
      }
    }
  }
}

void Print(int x, int t) {
  if (!v[x].r) {
    cout << t << '\n'
         << x << " \n"[x == s];
    return;
  }
  Print(v[x].r, t + 1);
  cout << x << " \n"[x == s];
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw1[0] = pw2[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw1[i] = pw1[i - 1] * 2 % kMod1;
    pw2[i] = pw2[i - 1] * 2 % kMod2;
  }
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
    v[y].e.push_back({x, z});
  }
  cin >> s, Dij(), cin >> s;
  if (v[s].p) {
    cout << d[v[s].p].h1 << '\n';
    Print(s, 1);
  } else {
    cout << -1 << '\n';
  }
  return 0;
}
