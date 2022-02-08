#include <iostream>
#include <vector>
#define LL long long

using namespace std;

const int kD = 250000;
int n, m, ans, b[250000], v[500000], c[250000];
bool a[500000];
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

void M(int x) {
  if (!a[x]) {
    a[x] = 1;
    for (int i : e[x]) {
      if (!a[i]) {
        a[i] = 1, M(v[i]);
      }
    }
  }
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
        e[i * 500 + _j].push_back(_i * 500 + j + kD);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ch[i][j] == '1') {
        ans += T(i * 500 + j, i * 500 + j);
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ch[i][j] == '1' && !c[i * 500 + j]) {
        M(i * 500 + j);
      }
    }
  }
  cout << ans << '\n';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i + j && ch[i][j] == '1') {
        if (!a[i * 500 + j]) {
          cout << i + 1 << ' ' << j + 1 << " DESNO\n";
        }
        if (a[i * 500 + j + kD]) {
          cout << i + 1 << ' ' << j + 1 << " DOLJE\n";
        }
      }
    }
  }
  return 0;
}
