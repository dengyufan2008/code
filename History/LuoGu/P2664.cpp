#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  LL c, s, w, t;
  bool b;
  vector<LL> e;
} v[100001];
LL n, s, r, t, b[100001], c[100001];

void GetRoot(LL f, LL x) {
  v[x].s = 1, v[x].w = b[v[x].c] = c[v[x].c] = 0;
  for (LL i : v[x].e) {
    if (i != f && !v[i].b) {
      GetRoot(x, i);
      v[x].s += v[i].s, v[x].w = max(v[x].w, v[i].s);
    }
  }
  if ((v[x].w = max(v[x].w, s - v[x].s)) <= s / 2) {
    r = x;
  }
}

void CalcCol(LL f, LL x, LL p) {
  bool o = 0;
  if (!b[v[x].c]) {
    o = b[v[x].c] = 1, c[v[x].c] += p * v[x].s, t += p * v[x].s;
  }
  for (LL i : v[x].e) {
    if (i != f && !v[i].b) {
      CalcCol(x, i, p);
    }
  }
  if (o) {
    b[v[x].c] = 0;
  }
}

void CalcAns(LL f, LL x, LL s) {
  bool o = 0;
  if (!b[v[x].c]) {
    o = b[v[x].c] = 1, t -= c[v[x].c] - s;
  }
  v[x].t += t;
  for (LL i : v[x].e) {
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
  for (LL i : v[r].e) {
    if (!v[i].b) {
      t += s - v[i].s;
      CalcCol(r, i, -1);
      CalcAns(r, i, s - v[i].s);
      CalcCol(r, i, 1);
      t -= s - v[i].s;
    }
  }
  for (LL i : v[r].e) {
    if (!v[i].b) {
      s = v[i].s, GetRoot(r, i), GetRoot(0, r), Divide();
    }
  }
}

int main() {
  cin >> n;
  for (LL i = 1; i <= n; i++) {
    cin >> v[i].c;
  }
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  s = n, GetRoot(0, 1), GetRoot(0, r), Divide();
  for (LL i = 1; i <= n; i++) {
    cout << v[i].t << '\n';
  }
  return 0;
}
