#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, p[11], q[11], ap, aq;
char tmp;

void C(int x) {
  if (x > n) {
    return;
  }
  ap = p[x] * aq + ap * q[x], aq = q[x] * aq;
  C(x + 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i] >> tmp >> q[i];
  }
  ap = p[1], aq = q[1];
  C(2);
  for (int i = 2; i <= max(sqrt(ap), sqrt(aq)); i++) {
    while (!(ap % i) && !(aq % i)) {
      ap /= i, aq /= i;
    }
  }
  cout << ap << "/" << aq;
  return 0;
}
