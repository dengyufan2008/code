#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("d.in");
ofstream cout("d.out");

const int kMaxN = 501, kMaxV = 2500000;
int t, n, m, k, a[kMaxN], o[kMaxN];
bitset<kMaxV * 2> f[kMaxN];

int Find(int n, int a[kMaxN], bool o) {  // 1:mx -1:mn
  int mx = 0;
  for (int i = 1; i <= n; i++) {
    if (~a[i]) {
      (!mx || (a[mx] > a[i]) ^ o) && (mx = i);
    }
  }
  return mx;
}

void Solve(int n, int m, int a[kMaxN], int o[kMaxN]) {
  for (; m >= n; m--) {
    int x = Find(n, a, 1);
    cout << o[x] << ' ' << k << '\n';
    a[x] = a[x] == k ? -1 : a[x] - k;
  }
  for (int i = 1; i < n; i++) {
    int x = Find(n, a, 0), y = Find(n, a, 1);
    if (a[x] == k) {
      cout << o[x] << ' ' << a[x] << '\n';
    } else {
      cout << o[x] << ' ' << a[x] << ' ' << o[y] << ' ' << k - a[x] << '\n';
      a[y] -= k - a[x];
    }
    a[x] = -1;
  }
}

void Makeup() {
  for (int i = 1; i <= n; i++) {
    a[i] -= k;
    if (a[i] >= 0) {
      f[i] = f[i - 1] | f[i - 1] << a[i];
    } else {
      f[i] = f[i - 1] | f[i - 1] >> -a[i];
    }
  }
  if (f[n].test(kMaxV - k)) {
    static int b[kMaxN], c[kMaxN];
    static int ob[kMaxN], oc[kMaxN];
    int nb = 0, nc = 0;
    int w = -k;
    for (int i = n; i >= 1; i--) {
      if (f[i - 1][w - a[i] + kMaxV]) {
        w -= a[i], nb++, b[nb] = a[i] + k, ob[nb] = i;
      } else {
        nc++, c[nc] = a[i] + k, oc[nc] = i;
      }
    }
    Solve(nb, nb - 1, b, ob), Solve(nc, nc - 1, c, oc);
  } else {
    cout << -1 << '\n';
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  f[0].set(kMaxV);
  for (int i = 1; i < kMaxN; i++) {
    o[i] = i;
  }
  cin >> t;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    m == n - 2 ? Makeup() : Solve(n, m, a, o);
  }
  return 0;
}
