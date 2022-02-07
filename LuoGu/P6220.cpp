#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, m, ans, b[250000], v[250000];
bool d[250000];
char c[500][500];
vector<int> e[250000];

bool T(int x, int k) {
  if (b[x] < k) {
    b[x] = k;
    for (int i : e[x]) {
      if (!v[i] || T(v[i], k)) {
        d[v[i]] = 0, d[v[i] = x] = 1;
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
    for (int j = 0; j < m; j++) {
      if (c[i][j] == '1') {
        ans += T(i * 500 + j, i * 500 + j);
      }
    }
  }
  cout << ans << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (c[i][j] == '1') {
        if (!d[i * 500 + j]) {
          cout << i + 1 << ' ' << j + 1 << " DESNO\n";
        }
        if (v[i * 500 + j]) {
          cout << i + 1 << ' ' << j + 1 << " DOLJE\n";
        }
      }
    }
  }
  return 0;
}
