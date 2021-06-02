#include <bits/stdc++.h>
#define LL long long

using namespace std;

LL n;
long double u, f;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cout << "Please input u(0<u<1)." << endl;
  cin >> u;
  cout << "Please input f(f>0)." << endl;
  cin >> f;
  cout << "Please input n(n>0)." << endl;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cout << "[" << i << "]:" << u << endl;
    u = u * (1 - u) * f;
  }
  return 0;
}
