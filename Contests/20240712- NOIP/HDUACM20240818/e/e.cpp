#include <fstream>
#include <vector>
#define LL long long
#define Point pair<LL, LL>

using namespace std;

ifstream cin("e.in");
ofstream cout("e.out");

const int kMaxN = 2e5 + 1;
struct Poly {
  LL s;
  vector<Point> v;
  bool operator<(const Poly &x) const {
    return s < x.s;
  }
} a[kMaxN], b[kMaxN];
int t, n;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
      int mn = 0, mx = 0;
      cin >> x;
      for (int j = 0, y, z; j < x; j++) {
        cin >> y >> z;
        Point p = {y, z};
        a[i].v.push_back(p);
        if (p < a[i].v[mn]) {
          mn = j;
        }
        if (p > a[i].v[mx]) {
          mx = j;
        }
      }
    }
    ;
  }
  return 0;
}
