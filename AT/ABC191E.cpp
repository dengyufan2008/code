#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int p, d, x;
} e[2001];
struct B {
  int et, d = -1;
} v[2001];
int n, m;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for (int i = 1, a, b, c; i <= m; i++) {
    cin >> a >> b >> c;
    e[i] = {v[a].et, b, c}, v[a].et = i;
  }
  
  for (int i = 1; i <= n; i++) {
    cout << v[i].d << endl;
  }
  return 0;
}
