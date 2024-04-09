#include <fstream>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.out");

const int kMaxN = 3e5 + 1;
struct V {
  int w, t;
} v[kMaxN * 48];
int n, m, k, p[kMaxN], s[kMaxN];

void Init() {
  int a[kMaxN] = {}, d[kMaxN] = {};
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i >= 1; i--) {
    p[i] = d[a[i]], d[a[i]] = i;
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  return 0;
}
