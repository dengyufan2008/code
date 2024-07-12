#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("set.in");
ofstream cout("set.out");

const int kMaxN = 1024;
int n, m;
vector<int> a[kMaxN], b[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < (1 << n); i++) {
    int c = 0;
    for (int j = i; j; j >>= 1) {
      c += j & 1;
    }
    if (c == (n + 1 >> 1)) {
      m++;
      for (int j = 0; j < n; j++) {
        if (i >> j & 1) {
          a[j].push_back(m);
          b[m].push_back(j);
        }
      }
    }
  }
  cout << m << '\n';
  for (int i = 0; i < n; i++) {
    sort(a[i].begin(), a[i].end());
    cout << a[i].size() << ' ';
    for (int j : a[i]) {
      cout << j << ' ';
    }
    cout << '\n';
  }
  for (int i = 1; i <= m; i++) {
    sort(b[i].begin(), b[i].end());
    cout << b[i].size() << ' ';
    for (int j : b[i]) {
      cout << j + 1 << ' ';
    }
    cout << '\n';
  }
  return 0;
}
