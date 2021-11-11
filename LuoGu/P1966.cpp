#include <algorithm>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int a[2], b[2];
  bool operator<(const V &v) const {
    return b[0] < v.b[0];
  }
} v[100001];
int n, ans, l[2][100001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].a[0];
    l[0][i] = i;
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i].a[1];
    l[1][i] = i;
  }
  sort(l[0] + 1, l[0] + n + 1, [](int i, int j) { return v[i].a[0] < v[j].a[0]; });
  sort(l[1] + 1, l[1] + n + 1, [](int i, int j) { return v[i].a[1] < v[j].a[1]; });
  for (int i = 1; i <= n; i++) {
    v[l[0][i]].b[0] = v[l[0][i - 1]].b[0] + 1;
    v[l[1][i]].b[1] = v[l[1][i - 1]].b[1] + 1;
  }
  sort(v + 1, v + n + 1);
  for (int i = 1; i <= n; i++) {
    while (v[i].b[1] != i) {
      swap(v[i].b[1], v[v[i].b[1]].b[1]);
      ans++;
    }
  }
  cout << ans;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
