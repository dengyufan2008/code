#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct V {
  int x, y;
} v[1001];
int n, ans;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].x >> v[i].y;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      ans += abs(v[i].x - v[j].x) >= abs(v[i].y - v[j].y);
    }
  }
  cout << ans << endl;
  return 0;
}
