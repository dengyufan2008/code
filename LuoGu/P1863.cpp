#include <cmath>
#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

int n;
bool b[1001] = {1};
pair<int, int> a[1001] = {{0, 0}};

int ChaCheng(int o, int x, int y) {
  return (a[x].first - a[o].first) * (a[y].second - a[o].second) - (a[y].first - a[o].first) * (a[x].second - a[o].second);
}

double Dis(int x, int y) {
  return sqrt((a[x].first - a[y].first) * (a[x].first - a[y].first) + (a[x].second - a[y].second) * (a[x].second - a[y].second));
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
  }
  cout << n << ' ';
  for (int i = 1, p = 0; i <= n; i++) {
    int mx = 0;
    for (int j = 1; j <= n; j++) {
      if (!b[j] && (!mx || ChaCheng(p, mx, j) < 0 || ChaCheng(p, mx, j) == 0 && Dis(p, j) < Dis(p, mx))) {
        mx = j;
      }
    }
    b[mx] = 1;
    cout << (p = mx) << ' ';
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
