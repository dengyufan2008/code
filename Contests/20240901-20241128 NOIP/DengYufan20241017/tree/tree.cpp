#include <fstream>
#include <vector>
#define LL long long

using namespace std;

ifstream cin("tree.in");
ofstream cout("tree.out");

const int kMaxN = 1e6 + 1, kMod = 998244353;
struct V {
  vector<int> e;
} v[kMaxN];
int n, m;
LL ans;

void T(int f, int x) {
  int w = m - !!f;
  for (int i : v[x].e) {
    if (i != f) {
      ans = ans * --w % kMod;
      T(x, i);
    }
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
  }
  ans = m, T(0, 1);
  cout << ans << '\n';
  return 0;
}
