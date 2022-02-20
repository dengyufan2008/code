#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int v, f, h, s = 1;
  vector<int> e;
} v[100001];
int n, m, s, p;
vector<int> l;
pair<int, int> d[401];

void T(int f, int x) {
  for (int i = 0; i < v[x].e.size(); i++) {
    if (f != v[x].e[i]) {
      T(x, v[x].e[i]);
      v[v[x].e[i]].f = x, v[x].s += v[v[x].e[i]].s;
      if (v[v[x].e[i]].s > v[v[x].e[v[x].e[0] == f]].s) {
        swap(v[x].e[v[x].e[0] == f], v[x].e[i]);
      }
    }
  }
}

void R(int f, int x) {
  if (!v[x].h) {
    v[x].h = x;
  }
  if (v[x].e.size() > 1) {
    v[v[x].e[v[x].e[0] == f]].h = v[x].h, l.push_back(x);
  }
  for (int i : v[x].e) {
    if (f != i) {
      R(x, i);
    }
  }
}

void Pushdown(int p, int l, int r) {
  int mid = l + r >> 1;
  if (d[p].second) {
    d[p * 2].first += d[p].second * (mid - l + 1);
    d[p * 2 + 1].first += d[p].second * (r - mid);
    d[p * 2].second += d[p].second;
    d[p * 2 + 1].second += d[p].second;
    d[p].second = 0;
  }
}

void Add(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    d[p].first += (r - l + 1) * k, d[p].second += k;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= _l) {
    Add(p * 2, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    Add(p * 2 + 1, mid + 1, r, _l, _r, k);
  }
  d[p].first = d[p * 2].first + d[p * 2 + 1].first + d[p].second;
}

int Ask(int p, int l, int r, int _l, int _r) {
  if (l >= _l && r <= _r) {
    return d[p].first;
  }
  int mid = l + r >> 1, ans = 0;
  Pushdown(p, l, r);
  if (mid >= _l) {
    ans += Ask(p * 2, l, mid, _l, _r);
  }
  if (mid < _r) {
    ans += Ask(p * 2 + 1, mid + 1, r, _l, _r);
  }
  return ans;
}

int main() {
  cin >> n >> m >> s >> p;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].v;
    v[i].v %= p;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, s), R(0, s);
  for (int i = 1, o, x, y, z; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y >> z;
    } else if (o == 2) {
      cin >> y;
    } else if (o == 3) {
      cin >> z;
    } else {
      ;
    }
  }
  return 0;
}
