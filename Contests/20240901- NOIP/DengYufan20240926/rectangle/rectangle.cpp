#include <fstream>

using namespace std;

ifstream cin("rectangle.in");
ofstream cout("rectangle.out");

const int kMaxN = 2e5 + 1;
struct A {
  int u, d, l, r;
} a[kMaxN];
int n;
long long ans;

bool C(pair<int, int> x, pair<int, int> y) {
  x.second - x.first < y.second - y.first ? swap(x, y) : void();
  return x.first <= y.first && y.first <= x.second || x.first <= y.second && y.second <= x.second;
}

bool C(int x, int y) {
  return C({a[x].u, a[x].d}, {a[y].u, a[y].d}) && C({a[x].l, a[x].r}, {a[y].l, a[y].r});
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i].u >> a[i].d >> a[i].l >> a[i].r;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      for (int k = j + 1; k <= n; k++) {
        if (!C(i, j) && !C(i, k) && !C(j, k)) {
          ans++;
        }
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
