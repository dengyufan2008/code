#include <algorithm>
#include <fstream>
#include <iomanip>
#define PDD pair<double, double>

using namespace std;

ifstream cin("f.in");
ofstream cout("f.out");

const int kMaxN = 3001;
struct L {
  double a, b, c;
} l[kMaxN];
int n;
double ans;

int Next(int x) { return x == n ? 1 : x + 1; }

PDD Cross(int x, int y) {
  double t = l[x].a * l[y].b - l[y].a * l[x].b;
  return {(l[x].c * l[y].b - l[y].c * l[x].b) / t,
          (l[y].c * l[x].a - l[x].c * l[y].a) / t};
}

double Cross(PDD x, PDD y) {
  return x.first * y.second - x.second * y.first;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> l[i].a >> l[i].b >> l[i].c;
  }
  sort(l + 1, l + n + 1, [](L i, L j) {
    if (i.b == 0 || j.b == 0) {
      return (i.b == 0) < (j.b == 0);
    } else {
      return j.a / j.b < i.a / i.b;
    }
  });
  for (int i = 1; i <= n; i++) {
    PDD s = {0, 0};
    for (int j = Next(i); j != i; j = Next(j)) {
      PDD x = Cross(i, j);
      ans += Cross(s, x);
      s.first += x.first, s.second += x.second;
    }
  }
  ans = ans * 3 / n / (n - 1) / (n - 2);
  cout << fixed << setprecision(5) << ans << '\n';
  return 0;
}
