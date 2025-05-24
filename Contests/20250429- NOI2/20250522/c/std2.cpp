// 可用带分段的兔队线段树维护, 但我懒
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
    int ans1 = 0, ans2 = 0;
    for (int j = 1, mx = 0; j <= n; j++) {
      if (a[j] > mx) {
        ans1 = max(ans1, l[j] + 1);
        if (a[j] < x) {
          mx = a[j];
        }
      }
    }
    for (int j = 1, k = 1; j <= n; j = k = k + 1) {
      for (; k < n && !(a[k] >= x && a[k + 1] >= x && l[k + 1] == ans1 - 1); k++) {
      }
      for (int p = j, u = 1, mx = 0; p <= k; p++) {
        if (a[p] >= x) {
          if (u) {
            ans2 = max(ans2, l[p]);
          } else {
            ans2 = max(ans2, l[p] + 1);
          }
        } else {
          if (a[p] > mx) {
            mx = a[p];
            if (u || a[p - 1] >= x && l[p] == ans1 - 1) {
              ans2 = max(ans2, l[p]);
            } else {
              ans2 = max(ans2, l[p] + 1);
            }
          }
          u = 0;
        }
      }
    }
    cout << min(ans1, ans2) << '\n';
  }
  return 0;
}
