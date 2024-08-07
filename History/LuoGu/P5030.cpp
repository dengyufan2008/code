#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kInf = 114514, kMove[4][2] = {{1, 3}, {3, 1}, {3, -1}, {1, -3}};
int n, m, k, ans, b[40000], v[40000];
vector<int> e[40000];

bool T(int x, int k) {
  if (b[x] < k) {
    b[x] = k;
    for (int i : e[x]) {
      if (!v[i] || T(v[i], k)) {
        v[i] = x;
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> n >> m >> k;
  for (int i = k, x, y; i--;) {
    cin >> x >> y;
    k -= b[x * 200 + y - 201] == kInf, b[x * 200 + y - 201] = kInf;
  }
  for (int j = 0; j < m; j++) {
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < 4; k++) {
        int _i = i + kMove[k][0], _j = j + kMove[k][1];
        if (_i < n && _j < m && _j >= 0 && b[i * 200 + j] != kInf && b[_i * 200 + _j] != kInf) {
          if (i & 1) {
            e[i * 200 + j].push_back(_i * 200 + _j);
          } else {
            e[_i * 200 + _j].push_back(i * 200 + j);
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i & 1 && b[i * 200 + j] != kInf) {
        ans += T(i * 200 + j, i * 200 + j);
      }
    }
  }
  cout << n * m - k - ans;
  return 0;
}
