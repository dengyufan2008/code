/*
ID: dengyuf1
TASK: milk3
LANG: C++                 
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a[3], tmp[3];
bool ans[21], b[21][21][21];

void Dfs(int d[]) {
  int tmp[3];
  if (b[d[0]][d[1]][d[2]]) {
    return;
  }
  b[d[0]][d[1]][d[2]] = true;
  if (!d[0]) {
    ans[d[2]] = true;
  }
  for (int i = 0; i <= 2; i++) {
    for (int j = 0; j <= 2; j++) {
      if (i != j && d[j] < a[j] && d[i] > 0) {
        copy(&d[0], &d[2] + 1, &tmp[0]);
        tmp[i] -= min(a[j] - d[j], d[i]), tmp[j] += min(a[j] - d[j], d[i]);
        Dfs(tmp);
      }
    }
  }
}

int main() {
  freopen("milk3.in", "r", stdin);
  freopen("milk3.out", "w", stdout);
  cin >> a[0] >> a[1] >> a[2];
  tmp[2] = a[2];
  Dfs(tmp);
  for (int i = 0; i < a[2]; ++i) {
    if (ans[i]) {
      cout << i << " ";
    }
  }
  cout << a[2] << endl;
  return 0;
}
