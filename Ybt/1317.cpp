#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n, r, a[21];

void Dfs(int s, int d) {
  if (d == r) {
    for (int i = 1; i <= d; i++) {
      cout << setw(3) << a[i];
    }
    cout << endl;
    return;
  }
  for (int i = s; i <= n; i++) {
    a[d + 1] = i;
    Dfs(i + 1, d + 1);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n >> r;
  Dfs(1, 0);
  return 0;
}
