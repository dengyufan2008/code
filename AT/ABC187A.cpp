#include <bits/stdc++.h>
#define LL long long

using namespace std;

int x, y;
string a, b;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b;
  for (int i = 0; i < a.length(); i++) {
    x += a[i] - '0';
  }
  for (int i = 0; i < b.length(); i++) {
    y += b[i] - '0';
  }
  cout << max(x, y) << endl;
  return 0;
}
