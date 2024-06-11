#include <algorithm>
#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("o.in");
ofstream cout("o.out");

const int kMaxN = 1e5 + 1, kMaxM = 2001, kInf = 1e9;
struct E {
  int s, w;
  LL lz, rz;
  vector<int> l;
  vector<int> t;
  void Rev() {
    swap(lz, rz);
    reverse(l.begin(), l.end());
    reverse(t.begin(), t.end());
  }
} e[kMaxN];
struct V {
  int d, w, o;
  bool b;
  vector<pair<int, int>> e;
} v[kMaxN];
int n, m, k, a[kMaxM];
LL ans, d[kMaxM][kMaxM];

void Init() {
  int m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    v[i].w = 1;
  }
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z, v[x].d++, v[y].d++;
    v[x].e.push_back({y, z}), v[y].e.push_back({x, z});
  }
}

void Del1() {
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (v[i].d == 1) {
      q.push(i);
    }
  }
  for (; !q.empty(); q.pop()) {
    int x = q.front(), y, z;
    for (auto i : v[x].e) {
      if (v[i.first].w) {
        y = i.first, z = i.second;
        break;
      }
    }
    ans += 1LL * v[x].w * (n - v[x].w) * z;
    v[y].w += v[x].w, v[x].w = 0, v[y].d--;
    if (v[y].d == 1) {
      q.push(y);
    }
  }
}

void ReBuild() {
  vector<pair<int, int>> e;
  for (int i = 1; i <= n; i++) {
    if (v[i].d == 1) {
      v[i].e.clear();
    } else {
      for (auto j : v[i].e) {
        if (v[j.first].d > 1) {
          e.push_back(j);
        }
      }
      v[i].e = e, e.clear();
    }
  }
}

void Spfa(int s) {
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    v[i].d = kInf;
  }
  for (v[s].d = 0, q.push(s); !q.empty(); q.pop()) {
    int x = q.front();
    v[x].b = 0;
    for (auto i : v[x].e) {
      int y = i.first, z = i.second;
      if (v[y].d > v[x].d + z) {
        v[y].d = v[x].d + z;
        if (!v[y].b) {
          v[y].b = 1, q.push(y);
        }
      }
    }
  }
}

void Calc3() {
  for (int i = 1; i <= n; i++) {
    if (v[i].d > 2) {
      a[++k] = i, v[i].o = k;
    }
  }
  for (int i = 1; i <= k; i++) {
    Spfa(a[i]);
    for (int j = 1; j <= k; j++) {
      d[i][j] = v[a[j]].d;
    }
    LL s = 0;
    for (int j = 1; j <= n; j++) {
      s += 1LL * v[j].w * v[j].d;
    }
    ans += v[a[i]].w * s;
  }
  for (int i = 1; i <= k; i++) {
    for (int j = i + 1; j <= k; j++) {
      ans -= d[i][j] * v[a[i]].w * v[a[j]].w;
    }
  }
}

void Find(int j, int p) {
  for (; v[p].e.size() == 2 && (k || !v[j].b);) {  // considering 基环树
    v[j].b = 1, e[m].l.push_back(j);
    if (v[p].e.front().first == j) {
      e[m].t.push_back(v[p].e.front().second);
    } else {
      e[m].t.push_back(v[p].e.back().second);
    }
    if (v[j].e.front().first == p) {
      p = j, j = v[j].e.back().first;
    } else {
      p = j, j = v[j].e.front().first;
    }
  }
}

void CalcChain(int _i) {
  E &i = e[_i];
  int x = 1, y = 1;
  int disx = i.t.front(), dism = 0, disy = i.s - disx, wm = 0, wy = i.w;
  LL zm = 0, zy = i.rz, dis = d[v[i.l.front()].o][v[i.l.back()].o];
  if (!k) {  // considering 基环树
    if (v[i.l.front()].e.front().first == i.l.back()) {
      dis = v[i.l.front()].e.front().second;
    } else {
      dis = v[i.l.front()].e.back().second;
    }
    disx = 0, disy = i.s, wy += v[i.l.front()].w + v[i.l.back()].w;
    zy += 1LL * v[i.l.front()].w * disy;
    i.l.insert(i.l.begin(), 0), i.l.push_back(0);
    i.t.insert(i.t.begin(), 0), i.t.push_back(0);
  }
  for (; x <= i.l.size() - 2; x++) {
    while (y <= i.l.size() - 2) {
      if (dism <= disx + dis + disy) {
        zm += 1LL * dism * v[i.l[y]].w;
        zy -= 1LL * disy * v[i.l[y]].w;
        dism += i.t[y], disy -= i.t[y];
        wm += v[i.l[y]].w, wy -= v[i.l[y]].w;
        y++;
      } else {
        break;
      }
    }
    ans += v[i.l[x]].w * (wy * (disx + dis) + zy + zm);
    disx += i.t[x], dism -= i.t[x];
    wm -= v[i.l[x]].w, zm -= wm * i.t[x];
  }
}

void FindChain() {
  for (int i = 1; i <= n; i++) {
    if (!v[i].b && v[i].e.size() == 2) {
      m++, v[i].b = 1;
      Find(v[i].e.front().first, i);
      e[m].Rev(), e[m].l.push_back(i);
      Find(v[i].e.back().first, i);
      for (int j : e[m].t) {
        e[m].s += j;
      }
      for (int j = 1; j <= e[m].l.size() - 2; j++) {
        e[m].w += v[e[m].l[j]].w;
      }
      for (int j = 1, z = 0; j <= e[m].l.size() - 2; j++) {
        z += e[m].t[j - 1], e[m].lz += 1LL * v[e[m].l[j]].w * z;
      }
      for (int j = e[m].l.size() - 2, z = 0; j >= 1; j--) {
        z += e[m].t[j], e[m].rz += 1LL * v[e[m].l[j]].w * z;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    CalcChain(i);
  }
}

void Cross(int _i, int _j, int o00, int o01, int o10, int o11) {
  E &i = e[_i], &j = e[_j];
  int x = 1, y = j.l.size() - 2;
  int x0 = v[i.l.front()].o, x1 = v[i.l.back()].o;
  int y0 = v[j.l.front()].o, y1 = v[j.l.back()].o;
  int xdis0 = i.t.front(), xdis1 = i.s - xdis0;
  int ydis1 = j.t.back(), ydis0 = j.s - ydis1, w = j.w;
  LL z = j.lz;
  for (; x <= i.l.size() - 2 && y >= 1; x++) {
    while (y >= 1) {
      LL dis00 = d[x0][y0] + xdis0 + ydis0 << 2 | o00;
      LL dis01 = d[x0][y1] + xdis0 + ydis1 << 2 | o01;
      LL dis10 = d[x1][y0] + xdis1 + ydis0 << 2 | o10;
      LL dis11 = d[x1][y1] + xdis1 + ydis1 << 2 | o11;
      if (dis00 > min({dis01, dis10, dis11})) {
        z -= 1LL * v[j.l[y]].w * ydis0;
        w -= v[j.l[y]].w, y--;
        ydis0 -= j.t[y], ydis1 += j.t[y];
      } else {
        break;
      }
    }
    ans += v[i.l[x]].w * (w * (xdis0 + d[x0][y0]) + z);
    xdis0 += i.t[x], xdis1 -= i.t[x];
  }
}

void Calc2() {
  for (int i = 1; i <= m; i++) {
    for (int j = i + 1; j <= m; j++) {
      Cross(i, j, 0, 1, 2, 3);  // 00
      e[j].Rev();
      Cross(i, j, 1, 0, 3, 2);  // 01
      e[i].Rev();
      Cross(i, j, 3, 2, 1, 0);  // 11
      e[j].Rev();
      Cross(i, j, 2, 3, 0, 1);  // 10
      e[i].Rev();
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init(), Del1(), ReBuild();
  Calc3(), FindChain(), Calc2();
  cout << ans << '\n';
  return 0;
}
