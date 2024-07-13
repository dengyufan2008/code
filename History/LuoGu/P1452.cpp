#include <algorithm>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#define LL long long
#define Pii pair<int, int>

using namespace std;

int n, p = 1, s, d[50001] = {0, 1};
Pii c = {100000, 100000}, a[50001];

double Cross(Pii k, Pii x, Pii y) {
  return (x.first - k.first) * (y.second - k.second) - (y.first - k.first) * (x.second - k.second);
}

double Dis(Pii x, Pii y) {
  return sqrt((x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second));
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].first >> a[i].second;
    c = min(c, a[i]);
  }
  sort(a + 1, a + n + 1, [](Pii i, Pii j) {
    return Cross(c, i, j) > 0 || Cross(c, i, j) == 0 && Dis(c, i) < Dis(c, j);
  });
  for (int i = 2; i <= n; i++) {
    for (; p > 1 && Cross(a[d[p - 1]], a[d[p]], a[i]) < 0; p--) {
    }
    d[++p] = i;
  }
  for (int i = 1; i <= p; i++) {
    
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
