#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, t, a, b, p, d;
bool flag = true;

void Update(int a, int b) {
  d -= a - p;
  flag = flag && (d > 0);
  d += min(b - a, n - d);
  p = b;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> m >> t;
  d = n;
  for (int i = 1; i <= m; i++) {
    cin >> a >> b;
    Update(a, b);
  }
  Update(t, t);
  cout << (flag ? "Yes" : "No") << endl;
  return 0;
}
