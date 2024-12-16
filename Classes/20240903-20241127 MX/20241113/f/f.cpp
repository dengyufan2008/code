#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 1e5 + 1, kMaxM = 201, kMod = 1e9 + 7;
struct V {
  int s;
  LL f[kMaxM];  // 子树内至少选了一个点, 所有的边都合法了
  LL g[kMaxM];  // f + 子树内至少选了一个点, 距离所有的边合法还需要子树外一点被选
  vector<int> e;
} v[kMaxN];
int n, m;
LL ans, f[kMaxM], g[kMaxM], fact[kMaxM], s2[kMaxM][kMaxM];

void T(int fa, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != fa) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  if (v[x].e.empty()) {
    v[x].s = 1, v[x].f[0] = v[x].g[0] = 1;
    return;
  }
  for (int i : v[x].e) {
    T(x, i);
    for (int j = min(v[i].s, m); j >= 1; j--) {
      v[i].g[j] = (v[i].g[j] + v[i].g[j - 1]) % kMod;
    }
    for (int j = 0; j <= min(v[x].s, m); j++) {
      f[j] = (f[j] + v[x].f[j]) % kMod;
      g[j] = (g[j] + v[x].g[j]) % kMod;
    }
    for (int j = 0; j <= min(v[i].s, m); j++) {
      f[j] = (f[j] + v[i].f[j]) % kMod;
      g[j] = (g[j] + v[i].g[j]) % kMod;
    }
    for (int j = 0; j <= min(v[x].s, m); j++) {
      for (int k = 0; k <= min(v[i].s, m); k++) {
        if (j + k <= m) {
          f[j + k] = (f[j + k] + v[x].g[j] * v[i].g[k]) % kMod;
          g[j + k] = (g[j + k] + v[x].g[j] * v[i].g[k]) % kMod;
        }
      }
    }
    v[x].s += v[i].s;
    for (int j = 0; j <= min(v[x].s, m); j++) {
      v[x].f[j] = f[j], f[j] = 0;
      v[x].g[j] = g[j], g[j] = 0;
    }
  }
  for (int i = 0; i <= min(v[x].s, m); i++) {
    v[x].f[i] = (v[x].f[i] + v[x].g[i]) % kMod;
    v[x].g[i] = v[x].g[i] * 2 % kMod;
  }
  v[x].f[0] = (v[x].f[0] + 1) % kMod;
  v[x].g[0] = (v[x].g[0] + 1) % kMod;
  v[x].s++;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = s2[0][0] = 1;
  for (int i = 1; i < kMaxM; i++) {
    fact[i] = fact[i - 1] * i % kMod;
    for (int j = 1; j <= i; j++) {
      s2[i][j] = (s2[i - 1][j] * j + s2[i - 1][j - 1]) % kMod;
    }
  }
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  T(0, 1);
  for (int i = 1; i <= m; i++) {
    ans = (ans + v[1].f[i] * s2[m][i] % kMod * fact[i]) % kMod;
  }
  cout << ans << '\n';
  return 0;
}
