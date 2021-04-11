#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, ml, fl;
double m[41], f[41], tmp2;
string tmp;

bool P1(double a, double b) {
  return a < b;
}

bool P2(double a, double b) {
  return a > b;
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> tmp >> tmp2;
    if (tmp[0] == 'm') {
      m[++ml] = tmp2;
    } else {
      f[++fl] = tmp2;
    }
  }
  sort(m + 1, m + 1 + ml, P1);
  sort(f + 1, f + 1 + fl, P2);
  for (int i = 1; i <= ml; i++) {
    cout << fixed << setprecision(2) << m[i] << " ";
  }
  for (int i = 1; i <= fl; i++) {
    cout << fixed << setprecision(2) << f[i] << " ";
  }
  return 0;
}
