#include <fstream>

using namespace std;

ifstream cin("j.in");
ofstream cout("j.out");

int t, a[8], h[3], r[128];
char w[8];
string s;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  r['R'] = 0, r['G'] = 1, r['B'] = 2;
  w[1] = 'R', w[2] = 'G', w[4] = 'B';
  cin >> t;
  while (t--) {
    h[0] = h[1] = h[2] = 0, cin >> s;
    for (int i = 0; i < 8; i++) {
      a[i] = r[s[i]], h[a[i]]++;
    }
    int ans = 0, p = 0, q = 4;
    if (a[p] == a[q]) {
      ans |= 1 << a[p];
    } else if (h[a[p]] != h[a[q]]) {
      ans |= h[a[p]] > h[a[q]] ? 1 << a[p] : 1 << a[q];
    } else {
      ans |= 1 << a[p] | 1 << a[q];
    }
    if ((ans & -ans) == ans) {
      cout << w[ans] << '\n';
    } else {
      cout << "N\n";
    }
  }
  return 0;
}
