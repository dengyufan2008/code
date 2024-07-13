#include <iostream>
#define LL long long

using namespace std;

int n, m, ans, b[151], v[151], c[151];
bool l[151][151];

bool T(int x, int k) {
  if (b[x] != k) {
    b[x] = k;
    for (int i = 1; i <= n; i++) {
      if (l[x][i] && (!v[i] || T(v[i], k))) {
        c[v[i]]--, c[v[i] = x]++;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    l[y][x] = 1;
  }
  for (int i = 1; i <= n; i++) {
    T(i, i);
  }
  for (int i = 1; i <= n; i++) {
    if (!c[i]) {
      ans++;
      for (int j = i; j; j = v[j]) {
        cout << j << ' ';
      }
      cout << '\n';
    }
  }
  cout << ans;
  return 0;
}
