#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, m, a[201], b[201], ans = 512;
bool mark[201][513];

void Dfs(int x, int c) {  //还要从a[x]开始配,c当前为c
  if (x > n) {
    ans = min(ans, c);
    return;
  }
  if (mark[x][c]) {
    return;
  }
  mark[x][c] = true;
  for (int i = 1; i <= m; i++) {
    Dfs(x + 1, c | (a[x] & b[i]));
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
  }
  Dfs(1, 0);  //还要从a[1]开始配,c当前为0
  cout << ans;
  return 0;
}
