#include <bits/stdc++.h>
#define LL long long

using namespace std;

struct A {
  int x, y;
} v[3];

int t, n;
bool b[401][401];
char ch;

int main() {
  cin.tie(0), cout.tie(0);
  std::ios::sync_with_stdio(false);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, m = 0; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> ch;
        b[i][j] = (ch == '*');
        if (b[i][j]) {
          v[++m] = {i, j};
        }
      }
    }
    if (v[1].x == v[2].x) {
      if (v[1].x == n) {
        b[v[1].x - 1][v[1].y] = b[v[2].x - 1][v[2].y] = true;
      } else {
        b[v[1].x + 1][v[1].y] = b[v[2].x + 1][v[2].y] = true;
      }
    } else {
      if (v[1].y == v[2].y) {
        if(v[1].y == n) {
          b[v[1].x][v[1].y - 1] = b[v[2].x][v[2].y - 1] = true;
        } else {
          b[v[1].x][v[1].y + 1] = b[v[2].x][v[2].y + 1] = true;
        }
      } else {
        b[v[1].x][v[2].y] = b[v[2].x][v[1].y] = true;
      }
    }
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        cout << (b[i][j] ? "*" : ".");
      }
      cout << endl;
    }
  }
  return 0;
}
