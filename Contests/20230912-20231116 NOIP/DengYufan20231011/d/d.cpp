#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kMaxN = 12001, kMaxL = 30;
const LL kInf = 1e9;
class V {
 public:
  int o, x, y;
} v[kMaxN];
class A {
 public:
  short w[16];
  int R(int x, int o) { return (w[x] >> o) & 1; }
  void W(int x, int o, int b) { w[x] = (w[x] ^ ((w[x] >> o & 1) << o)) | b << o; }
  void AddBack(A d) {
    for (int i = 0; i < 16; i++) {
      w[i] = d.w[w[i]];
    }
  }
  void Or(int x, int y) {
    for (int i = 0; i < 16; i++) {
      W(i, x, R(i, x) | R(i, y));
    }
  }
  void And(int x, int y) {
    for (int i = 0; i < 16; i++) {
      W(i, x, R(i, x) & R(i, y));
    }
  }
  void Xor(int x, int y) {
    for (int i = 0; i < 16; i++) {
      W(i, x, R(i, x) ^ R(i, y));
    }
  }
  void Ori(int x, int y) {
    for (int i = 0; i < 16; i++) {
      W(i, x, R(i, x) | y);
    }
  }
  void Andi(int x, int y) {
    for (int i = 0; i < 16; i++) {
      W(i, x, R(i, x) & y);
    }
  }
  void Xori(int x, int y) {
    for (int i = 0; i < 16; i++) {
      W(i, x, R(i, x) ^ y);
    }
  }
} oa = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
class D {
 public:
  LL t;
  int r;
  A w[8];
  void AddBack(D d) {
    for (int i = 0; i < 8; i++) {
      w[i].AddBack(d.w[i]);
    }
  }
  void Mul(int x) {
    D o = *this;
    *this = {this->t, this->r, {oa, oa, oa, oa, oa, oa, oa, oa}};
    for (int i = 1; i <= x; i <<= 1) {
      if (i & x) {
        AddBack(o);
      }
      o.AddBack(o);
    }
  }
  void Or(int x, int y) {
    for (int i = 0; i < 8; i++) {
      w[i].Or(x, y);
    }
  }
  void And(int x, int y) {
    for (int i = 0; i < 8; i++) {
      w[i].And(x, y);
    }
  }
  void Xor(int x, int y) {
    for (int i = 0; i < 8; i++) {
      w[i].Xor(x, y);
    }
  }
  void Ori(int x, int y) {
    for (int i = 0; i < 8; i++) {
      w[i].Ori(x, y >> i & 1);
    }
  }
  void Andi(int x, int y) {
    for (int i = 0; i < 8; i++) {
      w[i].Andi(x, y >> i & 1);
    }
  }
  void Xori(int x, int y) {
    for (int i = 0; i < 8; i++) {
      w[i].Xori(x, y >> i & 1);
    }
  }
  void Reflect(int a[4]) {
    for (int i = 0; i < 8; i++) {
      int _w = 0;
      for (int j = 0; j < 4; j++) {
        _w |= (a[j] >> i & 1) << j;
      }
      _w = w[i].w[_w];
      for (int j = 0; j < 4; j++) {
        a[j] = (a[j] ^ ((a[j] >> i & 1) << i)) | ((_w >> j & 1) << i);
      }
    }
  }
} od = {0, 0, {oa, oa, oa, oa, oa, oa, oa, oa}}, d[kMaxL][kMaxN];
int n, m;

int R(string s) { return (s == "dx") * 3 + (s == "cx") * 2 + (s == "bx"); }

void Input() {
  string s, t;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> s;
    if (s == "or") {
      cin >> s >> t;
      v[i].o = 0, v[i].x = R(s), v[i].y = R(t);
    } else if (s == "and") {
      cin >> s >> t;
      v[i].o = 1, v[i].x = R(s), v[i].y = R(t);
    } else if (s == "xor") {
      cin >> s >> t;
      v[i].o = 2, v[i].x = R(s), v[i].y = R(t);
    } else if (s == "ori") {
      cin >> s >> v[i].y;
      v[i].o = 3, v[i].x = R(s);
    } else if (s == "andi") {
      cin >> s >> v[i].y;
      v[i].o = 4, v[i].x = R(s);
    } else if (s == "xori") {
      cin >> s >> v[i].y;
      v[i].o = 5, v[i].x = R(s);
    } else if (s == "repeat") {
      cin >> v[i].x;
      v[i].o = 6;
    } else {
      v[i].o = 7;
    }
  }
}

void CalcPair() {
  LL j = 0;
  vector<pair<int, LL>> w;
  for (int i = 1; i <= n; i++) {
    if (v[i].o == 6) {
      w.push_back({i, j});
    } else if (v[i].o == 7) {
      auto t = w.back();
      if (j != t.second && j <= kInf) {
        v[i].x = v[t.first].x;
        v[t.first].y = i, v[i].y = t.first;
        j += (j - t.second) * (LL)(v[i].x - 1);
      } else {
        v[i].o = v[t.first].o = -1;
      }
      w.pop_back();
    } else {
      j++;
    }
  }
}

void CalcReflect(int l, int r, int k) {
  for (int i = l; i < r; i++) {
    d[k][i] = d[k][i - 1];
    if (v[i].o == 0) {
      d[k][i].t++, d[k][i].Or(v[i].x, v[i].y);
    } else if (v[i].o == 1) {
      d[k][i].t++, d[k][i].And(v[i].x, v[i].y);
    } else if (v[i].o == 2) {
      d[k][i].t++, d[k][i].Xor(v[i].x, v[i].y);
    } else if (v[i].o == 3) {
      d[k][i].t++, d[k][i].Ori(v[i].x, v[i].y);
    } else if (v[i].o == 4) {
      d[k][i].t++, d[k][i].Andi(v[i].x, v[i].y);
    } else if (v[i].o == 5) {
      d[k][i].t++, d[k][i].Xori(v[i].x, v[i].y);
    } else if (v[i].o == 6) {
      int j = v[i].y;
      CalcReflect(i + 1, j, k + 1);
      d[k][i].t += d[k + 1][j - 1].t * v[i].x, d[k][i].r = i;
      for (; i < j; i++) {
        d[k][i + 1] = d[k][i];
      }
      D t = d[k + 1][j - 1];
      t.Mul(v[j].x), d[k][j].AddBack(t);
    }
  }
}

void CalcReflect() {
  fill(&d[0][0], &d[kMaxL][0], od);
  CalcReflect(1, n + 1, 0);
}

D CalcAns(int l, int r, int k, int x) {
  D ans = od;
  while (l < r) {
    int mid = l + r >> 1;
    if (d[k][mid].t <= x) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  ans.AddBack(d[k][l - 1]);
  if (d[k][l - 1].t < x && d[k][l].r) {
    D w = d[k + 1][v[d[k][l].r].y - 1];
    x -= d[k][l - 1].t, w.Mul(x / w.t), ans.AddBack(w), x %= w.t;
    if (x) {
      ans.AddBack(CalcAns(d[k][l].r, v[d[k][l].r].y, k + 1, x % w.t));
    }
  }
  return ans;
}

void CalcAns() {
  for (int i = 1, x, a[4]; i <= m; i++) {
    cin >> x >> a[0] >> a[1] >> a[2] >> a[3];
    D ans = CalcAns(1, n + 1, 0, x);
    ans.Reflect(a);
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << ' ' << a[3] << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), CalcPair(), CalcReflect(), CalcAns();
  return 0;
}
