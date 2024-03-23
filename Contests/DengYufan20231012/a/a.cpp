#include <algorithm>
#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

const int kMaxN = 1e5 + 1, kInf = 1e9;
int n, m, ans, a[kMaxN], c[16];

int PopCount(int x) {
  int c = 0;
  for (; x; x >>= 1) {
    c += x & 1;
  }
  return c;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 0, x; i < m; i++) {
    cin >> x;
    for (int j = 1, y; j <= x; j++) {
      cin >> y;
      a[y] |= 1 << i;
    }
  }
  for (int i = 1; i <= n; i++) {
    c[a[i]]++;
  }
  ans += c[15];
  c[15] = 0;
  for (int i = 1; i < 16; i++) {
    for (int j = 1; j < 16; j++) {
      if (PopCount(i) == 3 && PopCount(j) == 1 && !(i & j)) {
        int t = min(c[i], c[j]);
        ans += t, c[i] -= t, c[j] -= t;
      }
    }
  }
  ans += c[7] + c[11] + c[13] + c[14];
  c[7] = c[11] = c[13] = c[14] = 0;
  for (int i = 1; i < 16; i++) {
    for (int j = 1; j < 16; j++) {
      if (PopCount(i) == 2 && PopCount(j) == 2 && !(i & j)) {
        int t = min(c[i], c[j]);
        ans += t, c[i] -= t, c[j] -= t;
      }
    }
  }
  for (int i = 1; i < 16; i++) {
    for (int j = 1; j < 16; j++) {
      for (int k = 1; k < 16; k++) {
        if (PopCount(i) == 2 && PopCount(j) == 1 && PopCount(k) == 1 && !(i & j) && !(i & k) && !(j & k)) {
          int t = min(min(c[i], c[j]), c[k]);
          ans += t, c[i] -= t, c[j] -= t, c[k] -= t;
        }
      }
    }
  }
  for (int i = 1; i < 16; i++) {
    for (int j = 1; j < 16; j++) {
      if (PopCount(i) == 2 && PopCount(j) == 1 && !(i & j)) {
        int t = min(c[i], c[j]);
        ans += t, c[i] -= t, c[j] -= t;
      }
    }
  }
  ans += c[3] + c[5] + c[6] + c[9] + c[10] + c[12];
  c[3] = c[5] = c[6] = c[9] = c[10] = c[12] = 0;
  ans += max(max(c[1], c[2]), max(c[4], c[8]));
  c[1] = c[2] = c[4] = c[8] = 0;
  cout << ans;
  return 0;
}
