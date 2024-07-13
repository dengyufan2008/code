#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int p, d;
} e[2][101];
int n, k, a[101], l[101], h[2][101];
string s;

void Insert(int x, int y, bool b) {
  e[b][++k] = {h[b][x], y};
  h[b][x] = k;
}

int main() {
  cin >> s;
  n = s.length();
  for (int i = 1; i <= n; i++) {
    l[i] = i;
  }
  sort(l + 1, l + n + 1, [](int i, int j) { return s[i - 1] < s[j - 1]; });
  for (int i = 1; i <= n; i++) {
    a[l[i]] = a[l[i - 1]] + (s[l[i - 1] - 1] != s[l[i] - 1]);
  }
  for (int p = 1; p <= n; p <<= 1) {
    for (int i = n; i >= 1; i--) {
      Insert(i + p <= n ? a[i + p] : 0, i, 0);
    }
    for (int i = n; i >= 1; i--) {
      for (int j = h[0][i]; j; j = e[0][j].p) {
        Insert(a[e[0][j].d - p], e[0][j].d, 1);
      }
    }
    
  }
  return 0;
}
