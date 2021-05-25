#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, s, d, x, y;
bool flag;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> s >> d;
  for (int i = 1; i <= n; i++) {
    cin >> x >> y;
    flag = flag || x < s && y > d;
  }
  cout << (flag ? "Yes" : "No") << endl;
  return 0;
}
