/*
ID: dengyuf1
TASK: pprime
LANG: C++
*/
#include <bits/stdc++.h>
#define LL long long

using namespace std;

int x, y;
bool b[100000001], _b[100000001];

void Hw() {
  for (int i = 1; i <= 9; i++) {
    _b[i] = _b[i * 11] = true;
  }
  for (int i = 1; i <= 99; i++) {
    _b[i / 10 * 10 + i % 10 * 101] = _b[i / 10 * 110 + i % 10 * 1001] = i % 10;
  }
  for (int i = 1; i <= 999; i++) {
    _b[i / 100 * 100 + i / 10 % 10 * 1010 + i % 10 * 10001] = _b[i / 100 * 1100 + i / 10 % 10 * 10010 + i % 10 * 100001] = i % 10;
  }
  for (int i = 1; i <= 9999; i++) {
    _b[i / 1000 * 1000 + i / 100 % 10 * 10100 + i / 10 % 10 * 100010 + i % 10 * 1000001] = _b[i / 1000 * 11000 + i / 100 % 10 * 100100 + i / 10 % 10 * 1000010 + i % 10 * 10000001] = i % 10;
  }
}

void Prime(void) {
  for (int i = 2; i <= y; i++) {
    if (!b[i]) {
      for (int j = i * 2; j <= y; j += i) {
        b[j] = true;
      }
      if (i >= x && _b[i]) {
        cout << i << "\n";
      }
    }
  }
}

int main() {
  // freopen("pprime.in", "r", stdin);
  // freopen("pprime.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(false);
  cin >> x >> y;
  Hw();
  Prime();
  return 0;
}
