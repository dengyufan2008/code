#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int c, s, w, t;
  bool b;
  vector<int> e;
} v[100001];
int n, s, r, t, b[100001], c[100001];

void GetRoot(int f, int x) {
  v[x].s = 1, v[x].w = 0, c[v[x].c] = 0;
  for (int i : v[x].e) {
    if (i != f && !v[i].b) {
      GetRoot(x, i);
      v[x].s += v[i].s, v[x].w = max(v[x].w, v[i].s);
    }
  }
  if ((v[x].w = max(v[x].w, s - v[x].s)) <= s / 2) {
    r = x;
  }
}

void CalcCol(int f, int x, int p) {
  bool o = 0;
  if (!b[v[x].c]) {
    o = b[v[x].c] = 1, c[v[x].c] += p * v[x].s, t += p * v[x].s;
  }
  for (int i : v[x].e) {
    if (i != f && !v[i].b) {
      CalcCol(x, i, p);
    }
  }
  if (o) {
    b[v[x].c] = 0;
  }
}

void CalcAns(int f, int x, int s) {
  bool o = 0;
  if (!b[v[x].c]) {
    o = b[v[x].c] = 1, t -= c[v[x].c] - s;
  }
  v[x].t += t;
  for (int i : v[x].e) {
    if (i != f && !v[i].b) {
      CalcAns(x, i, s);
    }
  }
  if (o) {
    b[v[x].c] = 0, t += c[v[x].c] - s;
  }
}

void Divide() {
  v[r].b = 1, t = 0;
  CalcCol(0, r, 1);
  v[r].t += t, b[v[r].c] = 1, t -= c[v[r].c];
  for (int i : v[r].e) {
    if (!v[i].b) {
      t += s - v[i].s;
      CalcCol(r, i, -1);
      CalcAns(r, i, s - v[i].s);
      CalcCol(r, i, 1);
      t -= s - v[i].s;
    }
  }
  for (int i : v[r].e) {
    if (!v[i].b) {
      s = v[i].s, GetRoot(r, i), GetRoot(0, r), Divide();
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].c;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  s = n, GetRoot(0, 1), GetRoot(0, r), Divide();
  for (int i = 1; i <= n; i++) {
    cout << v[i].t << '\n';
  }
  return 0;
}
