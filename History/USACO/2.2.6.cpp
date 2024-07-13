/*
ID: dengyuf1
TASK: lamps
LANG: C++
*/
#include <iostream>
#define LL long long

using namespace std;

const int kM[8][8] = {{0, 2, 2, 2, 2, 2, 2}, {0, 2, 2, 1, 1, 1, 2}, {0, 2, 1, 2, 1, 2, 1}, {0, 2, 1, 1, 2, 1, 1}, {0, 1, 2, 2, 1, 2, 2}, {0, 1, 2, 1, 2, 1, 2}, {0, 1, 1, 2, 2, 2, 1}, {0, 1, 1, 1, 1, 1, 1}};
const bool kD[4][10] = {{0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 1, 0, 1, 0, 0}, {1, 1, 1, 0, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1}};
int n, c, a[10];
bool f, f2;

void Print(int i) {
  f2 = 1;
  for (int j = 1; j <= n; j++) {
    cout << (kM[i][(j % 6 != 0) ? j % 6 : 6] != 2);
  }
  cout << endl;
}

bool C(int x) {
  for (int i = 1; i <= 6; i++) {
    if (kM[x][i] != a[i] && a[i]) {
      return 0;
    }
  }
  return 1;
}

void M(int c) {
  for (int i = 0; i <= 7; i++) {
    if (C(i) && kD[c][i]) {
      Print(i);
    }
  }
}

int main() {
  freopen("lamps.in", "r", stdin);
  freopen("lamps.out", "w", stdout);
  cin >> n >> c;
  c = (c > 3 ? 3 : c);
  for (int i = 1; i <= 2; i++) {
    for (int j = 1, p = 0; j <= n && p != -1;) {
      cin >> p;
      if (p != -1) {
        f |= !c;
        if (i == 1) {
          a[p % 6 ? p % 6 : 6] = 1;
        } else {
          a[(p % 6 != 0) ? p % 6 : 6] ? f = 1 : a[(p % 6 != 0) ? p % 6 : 6] = 2;
        }
      }
    }
  }
  M(c);
  if (f) {
    cout << "IMPOSSIBLE" << endl;
  } else if (!c) {
    for (int i = 1; i <= n; i++) {
      cout << 1;
    }
    cout << endl;
  } else if (!f2) {
    cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
