#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n, ans;
pair<int, int> a[701];

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i != j) {
        int num = 0;
        for (int k = 1; k <= n; k++) {
          num += (a[i].first - a[k].first) * (a[j].second - a[k].second) - (a[i].second - a[k].second) * (a[j].first - a[k].first) == 0;
        }
        ans = max(ans, num);
      }
    }
  }
  cout << ans;
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
