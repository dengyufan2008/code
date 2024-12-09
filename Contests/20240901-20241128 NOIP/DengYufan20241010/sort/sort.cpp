#include <fstream>

using namespace std;

ifstream cin("sort.in");
ofstream cout("sort.out");

const int kMaxN = 5e5 + 1;
int t, n, mx, p, d[kMaxN];
bool b[kMaxN];
long long ans;

void Add(int x) {
  if (!b[x]) {
    b[x] = 1;
    for (int i = x; i <= n; i += i & -i) {
      d[i]++;
    }
  }
}

int Ask(int x) {
  int ans = 0;
  for (int i = x; i >= 1; i -= i & -i) {
    ans += d[i];
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    fill(&d[1], &d[n] + 1, 0);
    fill(&b[1], &b[n] + 1, 0);
    cin >> n >> mx, p = ans = 0;
    cout << 0 << " \n"[n == 1];
    for (int i = 2, w; i <= n; i++) {
      cin >> w;
      if (w > mx) {
        ans += p ? i - p + 2 : 2, Add(mx);
        mx = w, p = 0;
      } else if (w == mx) {
        !p && (p = i);
      } else {
        ans += Ask(n) - Ask(w) + 1, Add(w);
      }
      cout << ans << " \n"[i == n];
    }
  }
  return 0;
}
