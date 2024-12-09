#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("proud.in");
ofstream cout("proud.out");

const int kMaxN = 2e6 + 2, kInf = 1e9;
int n, d[kMaxN], l[kMaxN], f[kMaxN], g[kMaxN], p[kMaxN];
string s;

int GetRoot(int x) {
  return p[x] == x ? x : p[x] = GetRoot(p[x]);
}

void Erase(int x) {
  p[x] = GetRoot(x + 1);
}

int Next(int x) {
  return GetRoot(min(x, n + 1));
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> s, n = s.size(), s = '~' + s, d[1] = n;
  for (int i = 2, j, k = 0; i <= n; i++) {
    if (i < k) {
      if (i + d[i - j + 1] < k) {
        d[i] = d[i - j + 1];
        continue;
      }
    } else {
      k = i;
    }
    for (j = i; k <= n && s[k] == s[k - j + 1]; k++) {
    }
    d[i] = k - j;
  }
  p[n + 1] = n + 1;
  for (int i = 1; i <= n; i++) {
    l[i] = i, g[i] = kInf, p[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) {
    return d[i] < d[j];
  });
  for (int i = 1, j = 1; i <= n; i++) {
    for (; j <= n && d[l[j]] == i - 1; j++) {
      Erase(l[j]);
    }
    f[i] = min(f[i - 1] + 1, g[i]);
    for (int k = i, c = 1; k <= n; k = Next(k + 1) + i - 1, c++) {
      g[k] = min(g[k], f[i] + k - c * (i - 1));
    }
  }
  cout << f[n] << '\n';
  return 0;
}
