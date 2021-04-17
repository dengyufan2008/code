#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;
char a, b, c;

void T(char l, char r, char mid, int n) {
  if(n == 0) {
    return;
  }
  T(l, mid, r, n - 1);
  cout << l << "->" << n << "->" << r << endl;
  T(mid, r, l, n - 1);
}

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> n >> a >> b >> c;
  T(a, b, c, n);
  return 0;
}
