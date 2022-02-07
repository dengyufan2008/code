#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, m, ans, b[250000], v[250000];
char c[500][500];
vector<int> e[250000];

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
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> c[i][j];
      if (c[i][j] == '0') {
        int _i = i, _j = j;
        for (; _i >= 0 && c[_i][j] != '1'; _i--) {
        }
        for (; _j >= 0 && c[i][_j] != '1'; _j--) {
        }
        e[_i * 500 + j].push_back(i * 500 + _j);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans += T(i * 500 + j, i * 500 + j);
    }
  }
  cout << ans << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (v[i * 500 + j]) {
        int _i = v[i * 500 + j] / 500, _j = v[i * 500 + j] % 500;
        if (abs(i - _i) > 1) {
          cout << _i + 1 << ' ' << _j + 1 << " DOLJE\n";
        }
        if (abs(j - _j) > 1) {
          cout << i + 1 << ' ' << j + 1 << " DESNO\n";
        }
      }
    }
  }
  return 0;
}
