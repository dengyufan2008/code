#include <iostream>
#define LL long long

using namespace std;

struct E {
  int p, t;
} e[10001];
int m, n, f[100000001];

int main() {
  cin >> m >> n;
  for (int i = 1; i <= n; i++) {
    cin >> e[i].p >> e[i].t;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (j >= e[i].t) {
        f[j] = max(f[j], f[j - e[i].t] + e[i].p);
      }
    }
  }
  cout << f[m] << endl;
  return 0;
}
