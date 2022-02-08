#include <iostream>
#include <vector>
#define LL long long

using namespace std;

int n, m, ans, d[250000], b[250000], v[250000], c[250000];
char ch[500][500];
vector<int> e[250000];

bool T(int x, int k) {
  if (b[x] != k) {
    b[x] = k;
    for (int i : e[x]) {
      if (!v[i] || T(v[i], k)) {
        c[v[i]]--, c[v[i] = x]++;
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
      cin >> ch[i][j];
      if (ch[i][j] == '0') {
        int _i = i, _j = j;
        for (; ch[_i][j] == '0'; _i--) {
        }
        for (; ch[i][_j] == '0'; _j--) {
        }
        e[i * 500 + _j].push_back(_i * 500 + j);
        d[i * 500 + _j] |= 1, d[_i * 500 + j] |= 2;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (d[i * 500 + j] & 1) {
        ans += T(i * 500 + j, i * 500 + j);
      }
    }
  }
  cout << ans << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (d[i * 500 + j] & 1 && !c[i * 500 + j]) {
        cout << i + 1 << ' ' << j + 1 << " DESNO\n";
      }
      if (d[i * 500 + j] & 2 && v[i * 500 + j]) {
        cout << i + 1 << ' ' << j + 1 << " DOLJE\n";
      }
    }
  }
  return 0;
}
