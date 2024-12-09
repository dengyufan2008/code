// O(n^2)
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("calm.in");
ofstream cout("calm.out");

const int kMaxN = 3e5 + 1;
struct V {
  int fa, r, s, f, g, h;
  vector<int> e, p;
} v[kMaxN];
int n, r, a, b;

void S(int f, int x) {
  static int k;
  static vector<int> l;
  l.size() >= a ? v[l[l.size() - a]].p.push_back(x) : void();
  l.push_back(x), v[x].fa = f, v[x].r = ++k, v[x].s = 1;
  for (int i : v[x].e) {
    if (i != f) {
      S(x, i), v[x].s += v[i].s;
    }
  }
  l.pop_back();
}

bool Subtree(int x, int y) {
  return v[x].r <= v[y].r && v[x].r + v[x].s > v[y].r;
}

int MinO(int x, int d) {
  if (!d) {
    return x;
  }
  int ans = x;
  for (int i : v[x].e) {
    if (i != v[x].fa) {
      ans = min(ans, MinO(i, d - 1));
    }
  }
  return ans;
}

void CalcF(int x) {
  for (int i : v[x].p) {
    v[x].f = max(v[x].f, v[i].h);
  }
  if (!v[x].f) {
    v[x].f = MinO(x, b);  // O(n)
  }
}

void CalcG(int x) {
  static int s[kMaxN], t[kMaxN];
  static bool o[kMaxN];
  for (int i = 0, j = 0; i < v[x].e.size(); i++) {
    s[i] = 0, t[i] = n;
    if (v[x].e[i] != v[x].fa) {
      t[i] = MinO(v[x].e[i], b - 1);  // O(n)
      for (; j < v[x].p.size() && Subtree(v[x].e[i], v[x].p[j]); j++) {
        s[i] = max(s[i], v[v[x].p[j]].h);
      }
    }
  }
  for (int i = 0, j = 0; i < v[x].e.size(); i++) {
    if (v[x].e[i] != v[x].fa) {
      v[v[x].e[i]].g = max(v[v[x].e[i]].g, j), j = max(j, s[i]);
    }
  }
  for (int i = v[x].e.size() - 1, j = 0; i >= 0; i--) {
    if (v[x].e[i] != v[x].fa) {
      v[v[x].e[i]].g = max(v[v[x].e[i]].g, j), j = max(j, s[i]);
    }
  }
  for (int i = 0; i < v[x].e.size(); i++) {
    o[i] = v[v[x].e[i]].g;
    if (!o[i] && v[x].e[i] != v[x].fa) {
      v[v[x].e[i]].g = x;
    }
  }
  for (int i = 0, j = n; i < v[x].e.size(); i++) {
    if (!o[i] && v[x].e[i] != v[x].fa) {
      v[v[x].e[i]].g = min(v[v[x].e[i]].g, j);
    }
    j = min(j, t[i]);
  }
  for (int i = v[x].e.size() - 1, j = n; i >= 0; i--) {
    if (!o[i] && v[x].e[i] != v[x].fa) {
      v[v[x].e[i]].g = min(v[v[x].e[i]].g, j);
    }
    j = min(j, t[i]);
  }
}

int MinF(int x, int d) {
  if (!d) {
    return v[x].f;
  }
  int ans = v[x].f;
  for (int i : v[x].e) {
    if (i != v[x].fa) {
      ans = min(ans, MinF(i, d - 1));
    }
  }
  return ans;
}

void CalcH(int x) {  // O(n)
  v[x].h = v[x].f;
  for (int i = 0, y = x; i < b; i++) {
    for (int j : v[y].e) {
      if (j != v[y].fa) {
        v[x].h = min(v[x].h, MinF(j, b - i - 1));
      }
    }
    v[x].h = min(v[x].h, v[y].g), y = v[y].fa;
  }
}

void T(int x) {
  for (int i : v[x].e) {
    if (i != v[x].fa) {
      T(i);
    }
  }
  for (int i : v[x].p) {
    CalcH(i);
  }
  CalcF(x), CalcG(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> r >> a >> b;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (a <= b) {
    cout << 1 << '\n';
    return 0;
  }
  S(0, r), T(r), cout << v[r].f << '\n';
  return 0;
}
