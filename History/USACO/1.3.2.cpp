/*
ID: dengyuf1
TASK: transform
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int n;
char a[15][15], b[15][15], c[15][15], d[15][15];

bool Work1() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      b[j][n - i + 1] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (b[i][j] != c[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

bool Work2() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      b[n - i + 1][n - j + 1] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (b[i][j] != c[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

bool Work3() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      b[n - j + 1][i] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (b[i][j] != c[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

bool Work4() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      b[i][n - j + 1] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (b[i][j] != c[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

bool Work5() {
  Work4();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = b[i][j];
    }
  }
  if (Work1()) {
    return 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = b[i][j];
    }
  }
  if (Work2()) {
    return 1;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = b[i][j];
    }
  }
  if (Work3()) {
    return 1;
  }
  return 0;
}

bool Work6() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (b[i][j] != c[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

void Work() {
  if (Work1()) {
    cout << 1 << endl;
    return;
  }
  if (Work2()) {
    cout << 2 << endl;
    return;
  }
  if (Work3()) {
    cout << 3 << endl;
    return;
  }
  if (Work4()) {
    cout << 4 << endl;
    return;
  }
  if (Work5()) {
    cout << 5 << endl;
    return;
  }
  if (Work6()) {
    cout << 6 << endl;
    return;
  }
  cout << 7 << endl;
}
int main() {
  freopen("transform.in", "r", stdin);
  freopen("transform.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      d[i][j] = a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> c[i][j];
    }
  }
  Work();
  return 0;
}
