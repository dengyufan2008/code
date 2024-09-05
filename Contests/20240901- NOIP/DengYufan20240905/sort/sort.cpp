#include <fstream>
#include <vector>

using namespace std;

ifstream cin("sort.in");
ofstream cout("sort.out");

const int kMaxN = 1001;
int t, n, a[kMaxN], b[kMaxN];
vector<int> ans;

bool Solve() {
  ans.clear();
  for (int i = 1; i <= n; i++) {
    int x = 0;
    for (int j = i; j <= n; j++) {
      if (a[j] == b[i]) {
        x = j;
        break;
      }
    }
    if (!x) {
      return 0;
    }
    for (int j = x - 1; j >= i; j--) {
      if (a[j] < a[j + 1]) {
        return 0;
      }
      swap(a[j], a[j + 1]), ans.push_back(j);
    }
  }
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
    }
    if (Solve()) {
      cout << 0 << '\n';
      cout << ans.size() << '\n';
      for (int i : ans) {
        cout << i << ' ' << i + 1 << '\n';
      }
    } else {
      cout << -1 << '\n';
    }
  }
  return 0;
}
