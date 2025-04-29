#include <fstream>
#define int long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 5;
int n, m, k, ans, a[kMaxN];

bool Insert(int *p, int x) {
  for (int i = kMaxN - 1LL; i >= 0; i--) {
    if (x >> i & 1LL) {
      if (p[i]) {
        x ^= p[i];
      } else {
        p[i] = x;
        return 1LL;
      }
    }
  }
  return 0;
}

void ReCalc(int *p) {
  for (int i = 0; i < kMaxN; i++) {
    if (p[i]) {
      for (int j = i + 1LL; j < kMaxN; j++) {
        if (p[j] >> i & 1LL) {
          p[j] ^= p[i];
        }
      }
    }
  }
}

bool Same(int *p, int *q) {
  for (int i = 0; i < kMaxN; i++) {
    if (p[i] != q[i]) {
      return 0;
    }
  }
  return 1LL;
}

signed main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1LL; i <= n; i++) {
    int x = 0;
    for (int j = 1LL; j <= m; j++) {
      static char c;
      cin >> c, x = x << 1LL | (c == '1');
    }
    if (!Insert(a, x)) {
      cout << 0 << '\n';
      return 0;
    }
  }
  ReCalc(a);
  for (int i = 1LL; i <= m; i++) {
    static char c;
    cin >> c, k = k << 1LL | (c == '1');
  }
  for (int s = 1LL; s < 1LL << k; s++) {
    static int p[kMaxN];
    fill(&p[0], &p[kMaxN], 0);
    for (int i = 1LL; i <= k; i++) {
      if (s >> i - 1LL & 1LL) {
        Insert(p, i);
      }
    }
    ReCalc(p);
    if (Same(a, p)) {
      ans++;
    }
  }
  cout << ans << '\n';
  return 0;
}
