#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const LL kMaxN = 2e5 + 1, kMaxV = 1e6, kInf = 1e18;
struct D {
  int l, r, k;
  LL b;
  LL Calc(LL x) { return k * x + b; }
} d[kMaxN * 20];
struct V {
  int w, c, s;
  LL t;
  vector<int> e;
} v[kMaxN];
int n;
LL w[kMaxN];

void CalcC(int x) {
  v[x].c = 1;
  for (int &i : v[x].e) {
    CalcC(i), v[x].c += v[i].c;
    if (v[v[x].e[0]].c < v[i].c) {
      swap(v[x].e[0], i);
    }
  }
}

LL Ask(int p, int l, int r, int x) {
  if (!p) {
    return kInf;
  } else if (l == r) {
    return d[p].Calc(x);
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    return min(Ask(d[p].l, l, mid, x), d[p].Calc(x));
  } else {
    return min(Ask(d[p].r, mid + 1, r, x), d[p].Calc(x));
  }
}

void Add(int &p, int l, int r, int k, LL b) {
  static int m = 0;
  !p && (p = ++m);
  if (!d[p].k || l == r) {
    if (!d[p].k || d[p].Calc(l) > 1LL * k * l + b) {
      d[p].k = k, d[p].b = b;
    }
    return;
  }
  int mid = l + r >> 1;
  if (d[p].Calc(mid) > 1LL * k * mid + b) {
    swap(d[p].k, k), swap(d[p].b, b);
  }
  if (d[p].Calc(l) > 1LL * k * l + b) {
    Add(d[p].l, l, mid, k, b);
  } else if (d[p].Calc(r) > 1LL * k * l + b) {
    Add(d[p].r, mid + 1, r, k, b);
  }
}

void Merge(int p, int q, int l, int r, LL t) {
  if (!d[q].k) {
    return;
  }
  Add(p, 1, kMaxV, d[q].k, d[q].b + t);
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Merge(p, d[q].l, l, mid, t);
  Merge(p, d[q].r, mid + 1, r, t);
}

void Dp(int x) {
  if (v[x].e.empty()) {
    Add(v[x].s, 1, kMaxV, v[x].w, 0);
    return;
  }
  for (int i : v[x].e) {
    Dp(i);
  }
  LL s = 0;
  for (int i = 0; i < v[x].e.size(); i++) {
    s += w[i] = Ask(v[v[x].e[i]].s, 1, kMaxV, v[x].w) + v[v[x].e[i]].t;
  }
  v[x].s = v[v[x].e[0]].s, v[x].t = v[v[x].e[0]].t + s - w[0];
  s -= v[x].t;
  for (int i = 1; i < v[x].e.size(); i++) {
    Merge(v[x].s, v[v[x].e[i]].s, 1, kMaxV, v[v[x].e[i]].t + s - w[i]);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2, x; i <= n; i++) {
    cin >> x, v[x].e.push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i].w;
  }
  CalcC(1), Dp(1);
  cout << Ask(v[1].s, 1, kMaxV, v[1].w) + v[1].t << '\n';
  return 0;
}
