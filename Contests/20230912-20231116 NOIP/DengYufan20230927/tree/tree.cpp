#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const LL kMaxN = 6001, kMod = 998244353;
struct V {
  LL s, p, f[kMaxN], g[kMaxN];
  vector<LL> e;
} v[kMaxN];
LL n, ans, d[kMaxN], p[kMaxN] = {1};

void S(LL f, LL x) {
  v[x].s = 1, v[x].p = f, v[x].f[0] = 1;
  for (LL i : v[x].e) {
    if (i != f) {
      S(x, i);
      fill(&d[0], &d[v[x].s + v[i].s], 0);
      for (LL j = 0; j < v[x].s; j++) {
        for (LL k = 0; k < v[i].s; k++) {
          d[j + k + 1] = (d[j + k + 1] + v[x].f[j] * v[i].f[k] % kMod) % kMod;
        }
      }
      v[x].s += v[i].s;
      for (LL j = 0; j < v[x].s; j++) {
        v[x].f[j] = (v[x].f[j] * p[v[i].s - 1] % kMod + d[j]) % kMod;
      }
    }
  }
}

void T(LL f, LL x) {
  for (LL i : v[x].e) {
    if (i != f) {
      for (LL j = 0; j <= v[i].s; j++) {
        v[i].g[j + 1] = v[x].g[j];
      }
      for (LL j : v[x].e) {
        if (j != f && j != i) {
          fill(&d[0], &d[v[i].s + 1] + 1, 0);
          for (LL k = 0; k <= v[i].s + 1; k++) {
            for (LL l = 0; l < v[j].s && l + k <= v[i].s; l++) {
              d[k + l + 1] = (d[k + l + 1] + v[i].g[k] * v[j].f[l] % kMod) % kMod;
            }
          }
          for (LL k = 0; k <= v[i].s + 1; k++) {
            v[i].g[k] = (v[i].g[k] * p[v[j].s - 1] % kMod + d[k]) % kMod;
          }
        }
      }
      v[i].g[0] = p[n - v[i].s - 1];
      T(x, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (LL i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  for (LL i = 1; i <= n; i++) {
    p[i] = p[i - 1] * 2 % kMod;
  }
  v[1].g[0] = 1, S(0, 1), T(0, 1);
  for (LL i = 1, s; i <= n; i++) {
    s = 0;
    for (LL j = 0, c = v[i].g[0]; j < v[i].s; j++) {
      c = (c + v[i].g[j + 1]) % kMod;
      s = (s + v[i].f[j] * c % kMod) % kMod;
    }
    for (LL j : v[i].e) {
      if (j != v[i].p) {
        for (LL k = 1, c = 0; k < v[j].s; k++) {
          c = (c + v[j].g[k]) % kMod;
          s = (s - v[j].f[k] * c % kMod + kMod) % kMod;
        }
      }
    }
    ans = (ans + s * i) % kMod;
  }
  cout << ans;
  return 0;
}
