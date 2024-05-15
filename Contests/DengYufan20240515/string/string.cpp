#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("string.in");
ofstream cout("string.out");

int u, n, m;
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> u;
  while (u--) {
    cin >> s, n = s.size(), m = 0;
    for (int i = 0; i < n; i++) {
      m += s[i] == '1';
    }
    if (m * 2 > n) {
      reverse(s.begin(), s.end());
      for (char &c : s) {
        c ^= 1;
      }
    }
    
  }
  return 0;
}
