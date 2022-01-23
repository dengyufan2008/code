#include <iostream>
#define LL long long

using namespace std;

int n, m, f[101];
pair<int, int> a[101];

int GetRoot(int x) {
  return f[x] == x ? x : f[x] = GetRoot(f[x]);
}

int main() {
  cin >> n;
  for (int i = 1, o, x, y; i <= n; i++) {
    f[i] = i;
    cin >> o >> x >> y;
    if (o == 1) {
      a[++m] = {x, y};
      for (int j = 1; j < m; j++) {
        if (a[j].first < x && a[j].second > x || a[j].first < y && a[j].second > y) {
          f[GetRoot(i)] = GetRoot(j);
        }
      }
    } else {
      cout << (GetRoot(x) == GetRoot(y) ? "YES\n" : "NO\n");
    }
  }
  return 0;
}
