#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 81, kMod = 1e9 + 7;
struct V {
  int s;
  LL f[kMaxN];  // 用了 j 个点
  vector<int> e;
} v[kMaxN];
int n;
LL h[kMaxN][kMaxN];  // 将 i 个有标号点分配到 j 个互不区分但内部有序的连续段
LL fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, int y = kMod - 2) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % kMod;
    }
    x = x * x % kMod;
  }
  return ans;
}

LL C(int x, int y) {
  return fact[x] * _fact[y] % kMod * _fact[x - y] % kMod;
}

void Update(LL &x, LL y) { x = (x + y) % kMod; }

void CalcH() {
  h[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 1; k + i <= n; k++) {
        LL w = C(i + k - 1, i) * fact[k] % kMod;  // 互不区分则最后一个在连续段内, 内部有序则任意重排
        Update(h[i + k][j + 1], h[i][j] * w);
      }
    }
  }
}

void Dp(int x) {
  static LL f[kMaxN][kMaxN][2], g[kMaxN][kMaxN][2];
  // 用了 j 个点 (包括最后一个连续段), 钦定了 k 个连续段 (不包括最后一个连续段), 是否钦定了最后一个连续段
  v[x].s = f[0][0][0] = f[1][1][0] = f[1][0][1] = 1;
  for (int i : v[x].e) {
    for (int j1 = 0; j1 <= v[x].s; j1++) {
      for (int k1 = 0; k1 <= j1; k1++) {
        for (int j2 = 0; j2 <= v[i].s; j2++) {
          for (int k2 = 0; k2 <= j2; k2++) {
            LL w = h[j2][k2] * C(v[i].s, j2) % kMod;
            (j2 - k2 & 1) && (w = kMod - w);  // 容斥系数为与连续段数量上界的差
            Update(g[j1 + j2][k1 + k2][0], f[j1][k1][0] * w);
            Update(g[j1 + j2][k1 + k2][1], f[j1][k1][1] * w);
            for (int l = 1; l + j2 <= v[i].s; l++) {
              LL _w = v[i].f[l] * h[j2][k2] % kMod * C(v[i].s - l, j2) % kMod;
              (j2 - k2 & 1) && (_w = kMod - _w);  // 容斥系数为与连续段数量上界的差
              Update(g[j1 + j2 + l][k1 + k2][1], f[j1][k1][0] * _w);
              if (k2) {  // 最后一段与前面不能相等, 钦定一个段放在最后, 并将符号取反
                _w = _w * (kMod - k2) % kMod;
                Update(g[j1 + j2 + l][k1 + k2 - 1][1], f[j1][k1][0] * _w);
              }
            }
          }
        }
      }
    }
    v[x].s += v[i].s;
    for (int j = 0; j <= v[x].s; j++) {
      for (int k = 0; k <= j; k++) {
        f[j][k][0] = g[j][k][0], f[j][k][1] = g[j][k][1];
        g[j][k][0] = g[j][k][1] = 0;
      }
    }
  }
  for (int i = 0; i <= v[x].s; i++) {
    for (int j = 0; j <= i; j++) {
      Update(v[x].f[i], f[i][j][1] * fact[j]);  // 段是有序的
      f[i][j][0] = f[i][j][1] = 0;
    }
  }
}

void T(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  for (int i : v[x].e) {
    T(x, i);
  }
  Dp(x);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  _fact[kMaxN - 1] = Pow(fact[kMaxN - 1]);
  for (int i = kMaxN - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % kMod;
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  CalcH(), T(0, 1), cout << v[1].f[v[1].s] << '\n';
  return 0;
}
