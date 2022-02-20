#include <algorithm>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int l, r;
  vector<int> d[2];
} v[101];
int n, k, c[101];
bool l[101][101], f[101][201], p[101][201];
vector<int> ans[2];

void S(int x, int k) {
  for (int i = 1; i <= n; i++) {
    if (!l[x][i] && x != i) {
      if (!c[i]) {
        if (c[x] == 1) {
          c[i] = 2, v[k].r++, v[k].d[1].push_back(i);
        } else {
          c[i] = 1, v[k].l++, v[k].d[0].push_back(i);
        }
        S(i, k);
      } else if (c[i] == c[x]) {
        cout << "No solution";
        exit(0);
      }
    }
  }
}

int main() {
  cin >> n;
  for (int i = 1, x; i <= n; i++) {
    do {
      cin >> x;
      l[i][x] = 1;
    } while (x);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (!l[i][j] || !l[j][i]) {
        l[i][j] = l[j][i] = 0;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (!c[i]) {
      c[i] = 1, v[++k].l++, v[k].d[0].push_back(i);
      S(i, k);
    }
  }
  f[0][n] = 1;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j <= n * 2; j++) {
      if (f[i][j]) {
        f[i + 1][j + v[i].l - v[i].r] = f[i + 1][j - v[i].l + v[i].r] = p[i + 1][j + v[i].l - v[i].r] = 1;
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    if (f[k][n + i] || f[k][n - i]) {
      for (int x = k, y = f[k][n + i] ? n + i : n - i; x; x--) {
        for (int i : v[x].d[0]) {
          ans[!p[x][y]].push_back(i);
        }
        for (int i : v[x].d[1]) {
          ans[p[x][y]].push_back(i);
        }
        y += (p[x][y] ? -1 : 1) * v[i].l - v[i].r;
      }
      break;
    }
  }
  sort(ans[0].begin(), ans[0].end()), sort(ans[1].begin(), ans[1].end());
  for (int i = 0; i < 2; i++) {
    cout << ans[i].size() << ' ';
    for (int j : ans[i]) {
      cout << j << ' ';
    }
    cout << '\n';
  }
  return 0;
}
