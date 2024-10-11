#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("game.in");
ofstream cout("game.out");

const int kMaxN = 1e5 + 1, kMaxM = 31, kMod = 998244353;
struct V {
  LL f[kMaxM][2], sf[kMaxM][2];
  LL g[kMaxM][2], sg[kMaxM][2];
  LL ans[kMaxM];
  vector<int> e;
} v[kMaxN];
int n, m, q;
LL s[kMaxN], t[kMaxN], ss[kMaxN], tt[kMaxN];

void Del(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    Del(x, i);
  }
}

void CalcF(int f, int x) {
  for (int i : v[x].e) {
    CalcF(x, i), v[i].sf[0][0] = v[i].f[0][0], v[i].sf[m][1] = v[i].f[m][1];
    for (int j = 1; j <= m; j++) {
      v[i].sf[j][0] = (v[i].sf[j - 1][0] + v[i].f[j][0]) % kMod;
    }
    for (int j = m - 1; j >= 0; j--) {
      v[i].sf[j][1] = (v[i].sf[j + 1][1] + v[i].f[j][1]) % kMod;
    }
    for (int j = 0; j <= m; j++) {
      v[i].sf[j][1] = (v[i].sf[j][1] + v[i].sf[m][0] - v[i].sf[j][0] + kMod) % kMod;
    }
  }
  if (v[x].e.empty()) {
    for (int j = 0; j <= m; j++) {
      v[x].f[j][0] = 1;
    }
    return;
  }
  int l = v[x].e.size() - 1;
  for (int j = 0; j <= m; j++) {
    s[0] = t[l] = 1;
    for (int i = 0; i < l; i++) {
      s[i + 1] = s[i] * v[v[x].e[i]].sf[j][0] % kMod;
    }
    for (int i = l; i > 0; i--) {
      t[i - 1] = t[i] * v[v[x].e[i]].sf[j][0] % kMod;
    }
    v[x].f[j][0] = s[l] * v[v[x].e[l]].sf[j][0] % kMod;
    for (int i = 0; i <= l; i++) {
      v[x].f[j][1] = (v[x].f[j][1] + s[i] * t[i] % kMod * v[v[x].e[i]].sf[j][1]) % kMod;
    }
  }
}

void CalcG(int f, int x) {
  v[x].sg[0][0] = v[x].g[0][0], v[x].sg[m][1] = v[x].g[m][1];
  for (int j = 1; j <= m; j++) {
    v[x].sg[j][0] = (v[x].sg[j - 1][0] + v[x].g[j][0]) % kMod;
  }
  for (int j = m - 1; j >= 0; j--) {
    v[x].sg[j][1] = (v[x].sg[j + 1][1] + v[x].g[j][1]) % kMod;
  }
  for (int j = 0; j <= m; j++) {
    v[x].sg[j][1] = (v[x].sg[j][1] + v[x].sg[m][0] - v[x].sg[j][0] + kMod) % kMod;
  }
  if (v[x].e.empty()) {
    return;
  }
  int l = v[x].e.size() - 1;
  for (int j = 0; j <= m; j++) {
    s[0] = t[l] = 1;
    for (int i = 0; i < l; i++) {
      s[i + 1] = s[i] * v[v[x].e[i]].sf[j][0] % kMod;
    }
    for (int i = l; i > 0; i--) {
      t[i - 1] = t[i] * v[v[x].e[i]].sf[j][0] % kMod;
    }
    for (int i = 0; i <= l; i++) {
      v[v[x].e[i]].g[j][0] = s[i] * t[i] % kMod * v[x].sg[j][0] % kMod;
    }
    ss[0] = tt[l] = 0;
    for (int i = 0; i < l; i++) {
      ss[i + 1] = (ss[i] * v[v[x].e[i]].sf[j][0] + s[i] * v[v[x].e[i]].sf[j][1]) % kMod;
    }
    for (int i = l; i > 0; i--) {
      tt[i - 1] = (tt[i] * v[v[x].e[i]].sf[j][0] + t[i] * v[v[x].e[i]].sf[j][1]) % kMod;
    }
    for (int i = 0; i <= l; i++) {
      LL w1 = (ss[i] * t[i] + s[i] * tt[i]) % kMod * v[x].sg[j][0];
      LL w2 = s[i] * t[i] % kMod * v[x].sg[j][1];
      v[v[x].e[i]].g[j][1] = (w1 + w2) % kMod;
    }
  }
  for (int i : v[x].e) {
    CalcG(x, i);
  }
}

void CalcAns() {
  for (int j = 0; j <= m; j++) {
    v[1].ans[j] = (v[1].f[j][0] + v[1].f[j][1]) % kMod;
  }
  for (int x = 2; x <= n; x++) {
    if (v[x].e.empty()) {
      for (int j = 0; j <= m; j++) {
        v[x].ans[j] = (v[x].sg[j][0] + v[x].sg[j][1]) % kMod;
      }
      continue;
    }
    int l = v[x].e.size() - 1;
    for (int j = 0; j <= m; j++) {
      s[0] = t[l] = 1;
      for (int i = 0; i < l; i++) {
        s[i + 1] = s[i] * v[v[x].e[i]].sf[j][0] % kMod;
      }
      for (int i = l; i > 0; i--) {
        t[i - 1] = t[i] * v[v[x].e[i]].sf[j][0] % kMod;
      }
      v[x].ans[j] = s[l] * v[v[x].e[l]].sf[j][0] % kMod * (v[x].sg[j][0] + v[x].sg[j][1]) % kMod;
      for (int i = 0; i <= l; i++) {
        LL w = s[i] * t[i] % kMod * v[v[x].e[i]].sf[j][1] % kMod * v[x].sg[j][0];
        v[x].ans[j] = (v[x].ans[j] + w) % kMod;
      }
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> q;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  if (n == 1) {
    for (int i = 1, x, y; i <= q; i++) {
      cin >> x >> y, cout << 1 << '\n';
    }
    return 0;
  }
  Del(0, 1), CalcF(0, 1), v[1].g[0][0] = 1, CalcG(0, 1), CalcAns();
  for (int i = 1, x, y; i <= q; i++) {
    cin >> x >> y, cout << v[x].ans[y] << '\n';
  }
  return 0;
}
