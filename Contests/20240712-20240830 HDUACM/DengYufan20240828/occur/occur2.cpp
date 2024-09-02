// O(n \sqrt q)
#include <algorithm>
#include <fstream>
#define LL long long

using namespace std;

ifstream cin("occur.in");
ofstream cout("occur.out");

const int kB = 333, kMaxN = 2e5 + kB;
struct E {
  int l, r, x;
  LL ans;
} e[2][kMaxN / kB][kMaxN / kB];
struct V {
  int f, l, e[27];
  LL c, w;
} v[2][kMaxN << 1];
int n, m;
string s[2];

void CalcSam(const bool o) {
  int k = 1, r = 1, p, l[kMaxN << 1];
  for (char c : s[o]) {
    int x = c - 'a';
    p = r, v[o][++k].l = v[o][p].l + 1;
    for (; p && !v[o][p].e[x]; p = v[o][p].f) {
      v[o][p].e[x] = k;
    }
    if (p) {
      int q = v[o][p].e[x];
      if (v[o][p].l + 1 == v[o][q].l) {
        v[o][k].f = q, r = k;
      } else {
        v[o][++k] = v[o][q], v[o][k].l = v[o][p].l + 1;
        for (; p && v[o][p].e[x] == q; p = v[o][p].f) {
          v[o][p].e[x] = k;
        }
        v[o][k - 1].f = v[o][q].f = k, r = k - 1;
      }
    } else {
      v[o][k].f = 1, r = k;
    }
  }
  p = 1;
  for (char c : s[o]) {
    p = v[o][p].e[c - 'a'], v[o][p].c++;
  }
  for (int i = 1; i <= k; i++) {
    l[i] = i;
  }
  sort(l + 1, l + k + 1, [&](int i, int j) {
    return v[o][i].l < v[o][j].l;
  });
  for (int i = k; i >= 2; i--) {
    int x = l[i];
    v[o][v[o][x].f].c += v[o][x].c;
  }
  for (int i = 2; i <= k; i++) {
    int x = l[i];
    v[o][x].w = v[o][v[o][x].f].w;
    v[o][x].w += v[o][x].c * (v[o][x].l - v[o][v[o][x].f].l);
  }
}

void Left(E &e, bool o) {  // 破坏 ans
  e.l++;
  if (v[o][v[o][e.x].f].l == e.r - e.l + 1) {
    e.x = v[o][e.x].f;
  }
}

void Right(E &e, bool o) {  // 维护 ans
  e.r++, e.x = v[o][e.x].e[s[o][e.r] - 'a'];
  e.ans += v[o][e.x].w;
  e.ans -= v[o][e.x].c * (v[o][e.x].l - e.r + e.l - 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> s[0] >> m;
  for (; n % kB; n++, s[0] += '{') {
  }
  s[1] = s[0], reverse(s[1].begin(), s[1].end());
  CalcSam(0), CalcSam(1);
  for (int i = 0; i < n; i += kB) {
    E t0 = {i, i - 1, 1, 0}, t1 = t0;
    for (int j = i; j < n; j++) {
      Right(t0, 0), Right(t1, 1);
      if (j % kB == kB - 1) {
        e[0][i / kB][j / kB] = t0;
        e[1][i / kB][j / kB] = t1;
      }
    }
  }
  for (int i = 1, l, r; i <= m; i++) {
    cin >> l >> r, l--, r--;
    if (l % kB == 0 && r % kB == kB - 1) {
      cout << e[0][l / kB][r / kB].ans << '\n';
    } else if (l / kB == r / kB) {
      E t = {l, l - 1, 1, 0};
      for (int j = l; j <= r; j++) {
        Right(t, 0);
      }
      cout << t.ans << '\n';
    } else {
      int x = l / kB + 1, y = r / kB - 1;
      int _x = (n - r - 1) / kB, _y = (n - l - 1) / kB - 1;
      y += r - y * kB - kB + 1 == kB;
      _x += n - _x * kB - r - 1 == kB;
      E t0 = x > y ? E{x * kB, x * kB - 1, 1, 0} : e[0][x][y];
      for (int j = y * kB + kB - 1; j < r; j++) {
        Right(t0, 0);
      }
      E t1 = e[1][_x][_y];
      for (int j = _x * kB + r + 1; j < n; j++) {
        Left(t1, 1);
      }
      t1.ans = t0.ans;
      for (int j = _y * kB + kB + l; j < n; j++) {
        Right(t1, 1);
      }
      cout << t1.ans << '\n';
    }
  }
  return 0;
}
