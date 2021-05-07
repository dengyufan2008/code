/*
ID: dengyuf1
TASK: milk3
LANG: C++                 
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a, b, c;
bool ans[61];

void Dfs(int _a, int _b) {
  int _c = c - _a - _b;
  if (_a < 0 || _b < 0 || _c < 0 || ans[_c]) {
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

void Print() {
  int mx = 60;
  for (; mx >= 0; mx--) {
    if (ans[mx]) {
      break;
    }
  }
  for (int i = 0; i < mx; i++) {
    if (ans[i]) {
      cout << i << " ";
    }
  }
  cout << mx << endl;
}

int main() {
  //	freopen("milk3.in", "r", stdin);
  //	freopen("milk3.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> a >> b >> c;
  Dfs(0, 0);
  Print();
  return 0;
}
