/*
ID: dengyuf1
TASK: concom
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL g[101];
} v[101];
LL n;
bool flag;

int main() {
  // freopen("concom.in", "r", stdin);
  // freopen("concom.out", "w", stdout);
  cin >> n;
  for (LL i = 1, x, y, z; i <= n; i++) {
    cin >> x >> y >> z;
    v[x].g[y] = z;
  }
  for (LL i = 1; i <= 100; i++) {
    v[i].g[i] = 100;
  }
  for (LL t = 0; !t || flag; t++) {
    flag = 0;
    for (LL i = 1; i <= 100; i++) {
      for (LL j = 1; j <= 100; j++) {
        if (i != j) {
          LL c = 0;
          for (LL k = 1; k <= 100; k++) {
            if ((!t || k != i) && k != j && v[i].g[k] > 50) {
              c += v[k].g[j];
            }
          }
          if (v[i].g[j] < c) {
            v[i].g[j] = c;
            flag = 1;
          }
        }
      }
    }
  }
  for (LL i = 1; i <= 100; i++) {
    for (LL j = 1; j <= 100; j++) {
      if (i != j && v[i].g[j] > 50) {
        cout << i << " " << j << endl;
      }
    }
  }
  return 0;
}
