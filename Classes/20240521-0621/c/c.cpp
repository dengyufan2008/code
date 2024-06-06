#include <fstream>
#define ULL unsigned long long

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 1e6 + 1, kMaxM = 1001;
const int kInf = 1e9, kBase = 15553;
int o, n, m, k, f[kMaxM << 1][kMaxM];
ULL hs[kMaxN], ht[kMaxN], pw[kMaxN];
string s, t;

void Max(int &x, int y) { x = max(x, y); }

int W() {
  for (int i = 0; i <= k; i++) {
    if (f[n - m + kMaxM][i] == m) {
      cout << "YES\n"
           << i << '\n';
      return i;
    }
  }
  cout << "NO\n";
  return 0;
}

int Print(int n, int m, int x) {
  if (x <= 0) {
    return n + 1;
  } else if (f[n - m + 1 + kMaxM][x - 1] >= m - 1) {
    int w = Print(n, m - 1, x - 1);
    cout << "INSERT " << w << ' ' << t[m] << '\n';
    return w + 1;
  } else if (f[n - m - 1 + kMaxM][x - 1] >= m) {
    int w = Print(n - 1, m, x - 1);
    cout << "DELETE " << w << '\n';
    return w;
  } else if (s[n] != t[m]) {
    int w = Print(n - 1, m - 1, x - 1);
    cout << "REPLACE " << w << ' ' << t[m] << '\n';
    return w + 1;
  }
  return Print(n - 1, m - 1, x) + 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  pw[0] = 1;
  for (int i = 1; i < kMaxN; i++) {
    pw[i] = pw[i - 1] * kBase;
  }
  cin >> o;
  while (o--) {
    cin >> n >> m >> k >> s >> t;
    if (abs(n - m) > k) {
      cout << "NO\n";
      continue;
    }
    s = '~' + s, t = '~' + t;
    for (int i = 1; i <= n; i++) {
      hs[i] = hs[i - 1] * kBase + s[i];
    }
    for (int i = 1; i <= m; i++) {
      ht[i] = ht[i - 1] * kBase + t[i];
    }
    for (int i = max(-k, -m); i <= min(k, n); i++) {
      f[i + kMaxM][0] = min(-i, 0);
    }
    for (int &i = f[kMaxM][0]; i < n && i < m && s[i + 1] == t[i + 1]; i++) {
    }
    for (int x = 1; x <= k; x++) {
      for (int i = max(-k, -m); i <= min(k, n); i++) {
        int &p = f[i + kMaxM][x];
        p = f[i + kMaxM][x - 1] + 1;
        if (i > max(-k, -m)) {
          p = max(p, f[i - 1 + kMaxM][x - 1]);
        }
        if (i < min(k, n)) {
          p = max(p, min(f[i + 1 + kMaxM][x - 1] + 1, m));
        }
        if (p >= max(-i, 0)) {
          int l = p + 1, r = min(n - i, m);
          while (l <= r) {
            int mid = l + r >> 1;
            ULL ws = hs[i + mid] - hs[i + p] * pw[mid - p];
            ULL wt = ht[mid] - ht[p] * pw[mid - p];
            ws == wt ? l = mid + 1 : r = mid - 1;
          }
          p = r;
        }
      }
    }
    Print(n, m, W());
  }
  return 0;
}
