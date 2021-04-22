#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int b, g;
} v[200001], c[200001];

int t, na, nb, k;
unsigned LL ans;

int main() {
  cin >> t;
  while (t--) {
    cin >> na >> nb >> k;
    ans = 0;
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= k; i++) {
      cin >> v[i].b;
      c[v[i].b].b++;
    }
    for (int i = 1; i <= k; i++) {
      cin >> v[i].g;
      c[v[i].g].g++;
    }
    for (int i = 1; i <= k; i++) {
      ans += k - c[v[i].b].b - c[v[i].g].g + 1;
    }
    cout << ans / 2 << endl;
  }
  return 0;
}
