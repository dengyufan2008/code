#include <fstream>
#include <vector>

using namespace std;

ifstream cin("c.in");
ofstream cout("c.ans");

const int kMaxN = 2.5e5 + 1;
int n, m, a[kMaxN], l[kMaxN];
vector<int> v;

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = n; i >= 1; i--) {
    for (; !v.empty() && a[i] >= v.back(); v.pop_back()) {
    }
    v.push_back(a[i]), l[i] = v.size();
  }
  for (int i = 1, x; i <= m; i++) {
    cin >> x;
    int ans = 0;
    bool o = 0;
    for (int j = 1, mx = 0; j <= n; j++) {
      if (a[j] > mx) {
        ans = max(ans, l[j]);
        if (a[j] < x) {
          mx = a[j];
        }
      }
    }
    for (int j = 1, mx = 0; j <= n; j++) {
      if (a[j] > mx) {
        o |= l[j] + !!mx > ans;
        if (a[j] < x) {
          mx = a[j];
        } else if (j < n && mx < a[j + 1] && l[j + 1] == ans) {
          mx = 0;
        }
      }
    }
    cout << ans + o << '\n';
  }
  return 0;
}
