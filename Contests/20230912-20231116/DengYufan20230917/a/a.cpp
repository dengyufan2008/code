#include <iostream>
#define LL long long

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

LL q, n, m;

LL Gcd(LL n, LL m) {
  return m ? Gcd(m, n % m) : n;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> q;
  while (q--) {
    cin >> n >> m;
    cout << n * m / Gcd(n, m) * 2 << '\n';
  }
  return 0;
}
