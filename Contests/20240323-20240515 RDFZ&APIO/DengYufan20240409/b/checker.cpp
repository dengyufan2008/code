#include <bitset>
#include <fstream>
using namespace std;

ifstream cin("b.in");
ifstream cout("b.out");
ofstream cans("b.ans");

int n, p, M, m;
bitset<10200 * 3> a[200];
bitset<3000 * 3> b[2000];
bool v[2000][2000];
template <typename tp>
inline void work(tp* a) {
  for (int i = 0; i < n << 1; ++i) {
    string s;
    cout >> s;
    if (s.size() ^ m) {
      cans << "Wrong Len\n";
      return;
    }
    for (int j = 0; j < m; ++j)
      if (s[j] < 'A' || 'C' < s[j]) {
        cans << s[j] << '\n';
        return;
      } else
        a[i][j * 3 + s[j] - 'A'] = 1;
  }
  for (int i = 0; i < n << 1; ++i)
    for (int j = i + 1; j < n << 1; ++j)
      if ((a[i] & a[j]).count() == m) {
        cans << "Same " << i + 1 << ' ' << j + 1 << '\n';
        return;
      }
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      if (!(a[i] & a[j]).count()) {
        cans << "Not Edge " << i + 1 << ' ' << j + 1 << '\n';
        return;
      }
  for (int i = n; i < n << 1; ++i)
    for (int j = i + 1; j < n << 1; ++j)
      if (!(a[i] & a[j]).count()) {
        cans << "Not Edge " << i + 1 << ' ' << j + 1 << '\n';
        return;
      }
  for (int i = 0; i < n; ++i)
    for (int j = n; j < n << 1; ++j)
      if (v[i][j] ^ ((a[i] & a[j]).count() > 0)) {
        cans << "Wrong Edge " << i + 1 << ' ' << j + 1 << '\n';
        return;
      }
  cans << "AC\n";
}
int main() {
  cin >> n >> p >> M;
  for (int u, v; p--;)
    cin >> u >> v, ::v[u - 1][v - 1] = 1;
  cout >> m;
  if (m < 1 || m > M) {
    cans << "Out Of Range!\n";
    return 0;
  }
  if (m > 3000)
    work(a);
  else
    work(b);
}