#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct E {
  int a, b;
} e[200001];
int n, ans, f[200001];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].a >> e[i].b;
  }
  sort(e + 1, e + n + 1, [](E i, E j) {
    return i.a < j.a;
  });
  for (int i = 1; i <= n; i++) {
    if (e[i].b > f[ans]) {
      f[++ans] = e[i].b;
    } else {
      int l = 0, r = ans, mid;
      while (l <= r) {
        mid = (l + r) >> 1;
        if (f[mid] <= e[i].b) {
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      f[l] = min(f[l], e[i].b);
    }
  }
  cout << ans << endl;
  return 0;
}
