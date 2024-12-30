#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

const int kMaxN = 81, kMod = 1e9 + 7;
struct V {
  int s;
  LL f[kMaxN];            // 用了 j 个点的答案
  LL g[kMaxN][kMaxN][2];  // 用了 j 个点, 至少有 k 个等号, 是否钦定了最后一个连续段
  vector<int> e;
} v[kMaxN];
int n;
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

void Dp(int x) {
  static LL g[kMaxN][kMaxN][2];
  v[x].g[0][0][0] = 1;
  for (int i : v[x].e) {
    for (int j1 = 0; j1 <= v[x].s; j1++) {
      for (int k1 = 0; k1 <= j1; k1++) {
        if (v[x].g[j1][k1][0] || v[x].g[j1][k1][1]) {
          for (int j2 = 0; j2 <= v[i].s; j2++) {
            for (int k2 = 0; k2 <= j2; k2++) {
              Update(g[j1 + j2][k1 + k2][0], v[x].g[j1][k1][0] * v[i].g[j2][k2][0]);
              Update(g[j1 + j2][k1 + k2][1], v[x].g[j1][k1][0] * v[i].g[j2][k2][1]);
              Update(g[j1 + j2][k1 + k2][1], v[x].g[j1][k1][1] * v[i].g[j2][k2][0]);
              for (int l = 0; l + j2 <= v[i].s; l++) {
                Update(g[j1 + j2 + l][k1 + k2][1], v[x].g[j1][k1][0] * v[i].g[j2][k2][0] * v[i].f[l]);
              }
            }
          }
        }
      }
    }
    v[x].s += v[i].s;
  }
  for (int i = 0; i <= v[x].s; i++) {
    for (int j = 0; j < v[x].s; j++) {
      if (j & 1) {
        Update(v[x].f[i], kMod - v[x].g[i][j][1]);
      } else {
        Update(v[x].f[i], v[x].g[i][j][1]);
      }
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
  T(0, 1), cout << v[1].f[v[1].s] << '\n';
  return 0;
}
