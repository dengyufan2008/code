#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 11;
struct V {
  int r, f;
  vector<int> e;
} v[kMaxN];
int t, n, a[kMaxN];

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      v[i].e.clear();
    }
    for (int i = 1, x, y; i < n; i++) {
      cin >> x >> y;
      v[x].e.push_back(y), v[y].e.push_back(x);
    }
    if (n <= 4) {
      cout << 0 << '\n';
      continue;
    }
    cout << Calc()
  }
  return 0;
}
