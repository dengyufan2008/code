#include <bitset>
#include <fstream>

using namespace std;

ifstream cin("thief.in");
ofstream cout("thief.out");

const int kMaxN = 502, kMaxV = 51;
int n, m, k, s, c[kMaxV], p[kMaxV];
bitset<kMaxN * kMaxV> f[kMaxN][kMaxV], ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    cin >> x, s += x, c[x]++;
    if (m < x) {
      m = x, k = 1;
    } else if (m == x) {
      k++;
    }
  }
  for (int i = 1; i < kMaxV; i++) {
    c[i] += c[i - 1];
  }
  for (int i = 0; i < kMaxV; i++) {
    p[i] = -1;
    for (int j = i + 1; j < kMaxV; j++) {
      if (c[i] != c[j]) {
        p[i] = j;
        break;
      }
    }
  }
  f[n][0].set(0);
  if (k == 1) {
    for (int i = n; i > 0; i--) {
      for (int v = 0; v != m; v = p[v]) {
        if (n - i + 1 <= c[v]) {
          f[i - 1][v] |= f[i][v] << v;
        }
        for (int w = p[v]; w != m; w = p[w]) {
          f[i - 1][w] |= f[i][v] << w;
        }
      }
    }
    for (int i = 1; i < kMaxV; i++) {
      if (p[i] == m) {
        ans = f[k][i] << m;
        break;
      }
    }
  } else {
    for (int i = n; i > 0; i--) {
      for (int v = 0; v != -1; v = p[v]) {
        if (n - i + 1 <= c[v]) {
          f[i - 1][v] |= f[i][v] << v;
        }
        for (int w = p[v]; w != -1; w = p[w]) {
          f[i - 1][w] |= f[i][v] << w;
        }
      }
    }
    ans = f[0][m];
  }
  for (int i = ans._Find_first(); i != kMaxN * kMaxV; i = ans._Find_next(i)) {
    cout << i - s << ' ';
  }
  cout << '\n';
  return 0;
}
