#include <iostream>
#define LL long long

using namespace std;

struct E {
  LL t, v;
} e[10001];
LL t, m, f[10000001];

int main() {
  cin >> t >> m;
  for (LL i = 1; i <= m; i++) {
    cin >> e[i].t >> e[i].v;
  }
  for (LL i = 1; i <= m; i++) {
    for (LL j = e[i].t; j <= t; j++) {
      f[j] = max(f[j], f[j - e[i].t] + e[i].v);
    }
  }
  cout << f[t] << endl;
  return 0;
}
