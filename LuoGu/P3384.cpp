#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int v, f, s = 1, d, h, l, r;
  vector<int> e;
} v[100001];
int n, m, s, p;
vector<int> l = {0};
pair<int, int> d[800001];

void T(int f, int x) {
  for (int i = 0; i < v[x].e.size(); i++) {
    if (f != v[x].e[i]) {
      T(x, v[x].e[i]);
      v[v[x].e[i]].f = x, v[x].s += v[v[x].e[i]].s, v[v[x].e[i]].d = v[x].d + 1;
      if (v[v[x].e[i]].s > v[v[x].e[v[x].e[0] == f]].s) {
        swap(v[x].e[v[x].e[0] == f], v[x].e[i]);
      }
    }
  }
}

void R(int f, int x) {
  v[x].l = l.size(), l.push_back(x);
  if (!v[x].h) {
    v[x].h = x;
  }
  if (v[x].e.size() > 1 || v[x].e[0] != f) {
    v[v[x].e[v[x].e[0] == f]].h = v[x].h;
  }
  for (int i : v[x].e) {
    if (f != i) {
      R(x, i);
    }
  }
  v[x].r = l.size(), l.push_back(x);
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
  for (int i = 1; i <= n; i++) {
    Add(1, 1, n * 2, v[i].l, v[i].l, v[i].v);
    Add(1, 1, n * 2, v[i].r, v[i].r, v[i].v);
  }
  for (int i = 1, o, x, y, z; i <= m; i++) {
    cin >> o >> x;
    if (o == 1) {
      cin >> y >> z;
      while (v[x].h != v[y].h) {
        if (v[v[x].h].d < v[v[y].h].d) {
          swap(x, y);
        }
        Add(1, 1, n * 2, v[v[x].h].l, v[x].l, z);
        x = v[v[x].h].f;
      }
      Add(1, 1, n * 2, v[x].l, v[y].l, z);
    } else if (o == 2) {
      cin >> y;
      int ans = 0;
      while (v[x].h != v[y].h) {
        if (v[v[x].h].d < v[v[y].h].d) {
          swap(x, y);
        }
        ans += Ask(1, 1, n * 2, v[v[x].h].l, v[x].l);
        x = v[v[x].h].f;
      }
      cout << ans + Ask(1, 1, n * 2, v[x].l, v[y].l) << '\n';
    } else if (o == 3) {
      cin >> z;
      Add(1, 1, n * 2, v[x].l, v[x].r, z);
    } else {
      cout << Ask(1, 1, n * 2, v[x].l, v[x].r) << '\n';
    }
  }
  return 0;
}
