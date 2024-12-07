#include <iostream>
#include <vector>
#define ULL unsigned long long

using namespace std;

const int kMaxN = 1001, kMaxL = 64, kV = 1e6;
int n, m, k, a[kMaxN], t[kMaxN], d[kMaxN], w[kMaxN];
int g[kMaxL];  // -1: both, 0: force to 0, 1:force to 1
ULL ans;
vector<int> f[2][kMaxN];

void Input() {
  struct P {
    ULL w, s;
  };
  static int b[kMaxN], u[kMaxL];
  static ULL c[kMaxN];
  static P q, p[2][kMaxL];
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int o : {0, 1}) {
    for (int i = 0; i < m; i++) {
      cin >> u[i], b[u[i]] = 1;
      !t[u[i]] && (t[u[i]] = ++k);
      q = {c[u[i]], 1ULL << t[u[i]]};
      for (int j = kMaxL - 1; j >= 0; j--) {
        if (q.w >> j & 1) {
          if (p[o][j].w) {
            q.w ^= p[o][j].w, q.s ^= p[o][j].s;
          } else {
            p[o][j] = q;
            break;
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      if (b[i] == 1 && !(b[i] = 0)) {
        continue;
      }
      q = {c[i]};
      for (int j = kMaxL - 1; j >= 0; j--) {
        if (q.w >> j & 1) {
          q.w ^= p[o][j].w, q.s ^= p[o][j].s;
        }
      }
      for (int j = 0; j < m; j++) {
        if (q.s >> j & 1) {
          f[o][i].push_back(u[j]);
        }
      }
    }
  }
}

void Init() {
  for (int i = 1; i <= n; i++) {
    d[i] = i;
  }
  for (int i = 0; i < kMaxL; i++) {
    g[i] = -1;
  }
}

void Divide(int lo, int ro, int lv, int rv) {
  if (lo > ro || lv == rv) {
    for (int i = lo; i <= ro; i++) {
      w[d[i]] = lv;
    }
    return;
  }
  int x = lv + rv >> 1, y = x + 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input(), Init(), Divide(1, n, 0, kV);
  for (int i = 1; i <= n; i++) {
    ans += 1LL * (a[i] - w[i]) * (a[i] - w[i]);
  }
  cout << ans << '\n';
  return 0;
}
