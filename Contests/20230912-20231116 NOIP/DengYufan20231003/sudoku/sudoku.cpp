#include <fstream>

using namespace std;

ifstream cin("sudoku.in");
ofstream cout("sudoku.out");

int t, a[10][10];

bool M() {
  for (int i = 1; i <= 9; i++) {
    int c[3] = {}, p[3] = {};
    for (int j = 1; j <= 9; j++) {
      c[a[i][j]]++, p[a[i][j]] = j;
    }
    if ((!c[0] || !c[1]) && c[2] == 1) {
      a[i][p[2]] = !c[1];
      return 1;
    }
  }
  for (int i = 1; i <= 9; i++) {
    int c[3] = {}, p[3] = {};
    for (int j = 1; j <= 9; j++) {
      c[a[j][i]]++, p[a[j][i]] = j;
    }
    if ((!c[0] || !c[1]) && c[2] == 1) {
      a[p[2]][i] = !c[1];
      return 1;
    }
  }
  for (int x = 1; x <= 9; x += 3) {
    for (int y = 1; y <= 9; y += 3) {
      int c[3] = {};
      pair<int, int> p[3] = {};
      for (int i = x; i <= x + 2; i++) {
        for (int j = y; j <= y + 2; j++) {
          c[a[i][j]]++, p[a[i][j]] = {i, j};
        }
      }
      if ((!c[0] || !c[1]) && c[2] == 1) {
        a[p[2].first][p[2].second] = !c[1];
        return 1;
      }
    }
  }
  return 0;
}

bool C() {
  for (int i = 1; i <= 9; i++) {
    int c[3] = {};
    for (int j = 1; j <= 9; j++) {
      c[a[i][j]]++;
    }
    if (!c[0] || !c[1]) {
      return 0;
    }
  }
  for (int i = 1; i <= 9; i++) {
    int c[3] = {};
    for (int j = 1; j <= 9; j++) {
      c[a[j][i]]++;
    }
    if (!c[0] || !c[1]) {
      return 0;
    }
  }
  for (int x = 1; x <= 9; x += 3) {
    for (int y = 1; y <= 9; y += 3) {
      int c[3] = {};
      for (int i = x; i <= x + 2; i++) {
        for (int j = y; j <= y + 2; j++) {
          c[a[i][j]]++;
        }
      }
      if (!c[0] || !c[1]) {
        return 0;
      }
    }
  }
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 9; j++) {
      if (a[i][j] == 2) {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 1; i <= 9; i++) {
      for (int j = 1; j <= 9; j++) {
        cin >> a[i][j];
      }
    }
    for (; M();) {
      t++, t--;
    }
    cout << (C() ? "Yes\n" : "No\n");
  }
  return 0;
}
