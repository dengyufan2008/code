#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n, tmp, m, c;
double e;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> tmp;
    m += abs(tmp), e += abs(tmp) * abs(tmp), c = max(abs(tmp), c);
  }
  cout << m << endl;
  printf("%.15lf\n", sqrt(e));
  cout << c << endl;
  return 0;
}
