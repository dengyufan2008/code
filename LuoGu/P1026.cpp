#include <iostream>
#define LL long long

using namespace std;

int p, k, n, d[201][201], f[201][41];
string s, t[7];

int main() {
  cin >> p >> k;
  for (int i = 1; i <= p; i++) {
    cin >> t[0];
    s += t[0];
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> t[i];
  }
  for (int i = 0; i < s.size(); i++) {
    for (int j = i + 1; j < s.size(); j++) {
      for (int k = 1; k <= n; k++) {
        d[i][j] += s.substr(i, t[k].size()) == t[k];
      }
    }
  }
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j <= k; j++) {
      for (int k = 0; k < i; k++) {
        f[i][j] = max(f[i][j], f[k][j - 1] + d[k + 1][i]);
      }
    }
  }
  cout << f[s.size() - 1][k];
  return 0;
}
