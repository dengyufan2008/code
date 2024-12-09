#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("gravekeeper.in");
ofstream cout("gravekeeper.out");

const int kMaxN = 501, kMod = 1e9 + 7;
struct V {
  int s;
  LL w, f[kMaxN];
  vector<int> e;
} v[kMaxN];
int n;
LL g[kMaxN][kMaxN], h[kMaxN], fact[kMaxN];

void Add(LL &x, LL y) { x = (x + y) % kMod; }
void Minus(LL &x, LL y) { x = (x - y) % kMod; }

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

void S(int f, int x) {
  static vector<int> e;
  for (int i : v[x].e) {
    if (i != f) {
      e.push_back(i);
    }
  }
  v[x].e.swap(e), e.clear();
  v[x].s = 1, v[x].w = fact[v[x].e.size()];
  for (int i : v[x].e) {
    S(x, i), v[x].s += v[i].s, v[x].w = v[x].w * v[i].w % kMod;
  }
}

void T(int x) {
  if (v[x].e.empty()) {
    return;
  }
  LL w = 1;
  for (int i = 0; i <= v[x].e.size(); i++) {
    for (int j = 0; j <= n; j++) {
      g[i][j] = 0;
    }
  }
  g[0][0] = 1;
  for (int i : v[x].e) {
    w = w * v[i].w % kMod;
    for (int j = v[x].e.size() - 1; j >= 0; j--) {
      for (int k = 0; k + v[i].s <= n; k++) {
        Add(g[j + 1][k + v[i].s], g[j][k]);
      }
    }
  }
  for (int i : v[x].e) {
    w = w * Pow(v[i].w) % kMod;
    for (int j = 0; j < v[x].e.size(); j++) {
      for (int k = 0; k + v[i].s <= n; k++) {
        Minus(g[j + 1][k + v[i].s], g[j][k]);
      }
    }
    for (int j = 0; j <= n; j++) {
      h[j] = 0;
    }
    for (int j = 0; j < v[x].e.size(); j++) {
      LL c = fact[j] * fact[v[x].e.size() - j - 1] % kMod;
      for (int k = 0; k + v[i].s <= n; k++) {
        Add(h[k], g[j][k] * c);
      }
    }
    for (int j = 0; j <= n; j++) {
      h[j] = h[j] * w % kMod;
    }
    for (int j = 0; j <= n; j++) {
      for (int k = 0; j + k < n; k++) {
        Add(v[i].f[j + k + 1], v[x].f[j] * h[k]);
      }
    }
    w = w * v[i].w % kMod;
    for (int j = v[x].e.size() - 1; j >= 0; j--) {
      for (int k = 0; k + v[i].s <= n; k++) {
        Add(g[j + 1][k + v[i].s], g[j][k]);
      }
    }
  }
  for (int i : v[x].e) {
    T(i);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  fact[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    fact[i] = fact[i - 1] * i % kMod;
  }
  cin >> n;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  S(0, 1), v[1].f[1] = 1, T(1);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << (v[i].f[j] + kMod) * v[i].w % kMod << " \n"[j == n];
    }
  }
  return 0;
}
