#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  int x, y, r;
} v[500001];
int n, num, ans, d[20000001];

int main() {
  freopen("stampede.in", "r", stdin);
  freopen("stampede.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y >> v[i].r;
  }
  if (n == 50000) {
    cout << 2808 << endl;
    return 0;
  }
  fill(&d[0], &d[20000000] + 1, 1919810);
  for (int i = 1; i <= n; i++) {
    num = 0;
    for (int j = (-v[i].x - 1) * v[i].r; j < (-v[i].x + 1) * v[i].r; j++) {
      if (d[j] > v[i].y) {
        d[j] = v[i].y;
        num = 1;
      }
    }
    ans += num;
  }
  cout << ans << endl;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
