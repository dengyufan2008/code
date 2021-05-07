/*
ID: dengyuf1
TASK: milk3
LANG: C++                 
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a, b, c;
bool ans[21];

void Dfs(int _a, int _b) {
  int _c = c - _a - _b;
  if (ans[_c]) {
    return;
  }
  if (!_a) {
    ans[_c] = true;
  }
  Dfs(_a + min(a - _a, _b), _b - min(a - _a, _b));
  Dfs(_a - min(b - _b, _a), _b + min(b - _b, _a));
  Dfs(_a + min(a - _a, _c), _b);
  Dfs(_a - min(c - _c, _a), _b);
  Dfs(_a, _b + min(b - _b, _c));
  Dfs(_a, _b - min(c - _c, _b));
}

int main() {
  //	freopen("milk3.in", "r", stdin);
  //	freopen("milk3.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c;
  Dfs(0, 0);
  for (int i = 0; i < c; i++) {
    if (ans[i]) {
      cout << i << " ";
    }
  }
  cout << c << endl;
  return 0;
}
