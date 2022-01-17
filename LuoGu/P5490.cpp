#include <algorithm>
#include <iostream>
#define LL long long

using namespace std;

struct L {
  int x, y1, y2;
  bool operator<(const L &l) const {
    return x < l.x;
  }
} l[200001];
int n, a[200001], y[200001];

int main() {
  cin >> n;
  for (int i = 1, x1, y1, x2, y2; i <= n; i++) {
    cin >> x1 >> y1 >> x2 >> y2;
    a[i * 2 - 1] = i * 2 - 1, a[i * 2] = i * 2;
    y[i * 2 - 1] = y1, y[i * 2] = y2;
    l[i * 2 - 1] = {x1}, l[i * 2] = {x2};
  }
  sort(a + 1, a + n * 2 + 1, [](int i, int j) { return y[i] < y[j]; });
  for (int i = 1; i <= n * 2; i++) {
    (a[i] & 1 ? l[a[i]].y1 : l[a[i]].y2) = (a[i - 1] & 1 ? l[a[i - 1]].y1 : l[a[i - 1]].y2) + (y[a[i - 1]] != y[a[i]]);
  }
  for (int i = 1; i <= n; i++) {
    (l[i * 2 - 1].y1 ? l[i * 2].y1 : l[i * 2 - 1].y1) = (l[i * 2 - 1].y1 ? l[i * 2 - 1].y1 : l[i * 2].y1);
    (l[i * 2 - 1].y2 ? l[i * 2].y2 : l[i * 2 - 1].y2) = (l[i * 2 - 1].y2 ? l[i * 2 - 1].y2 : l[i * 2].y2);
  }
  sort(l + 1, l + n * 2 + 1);
  
  return 0;
}
