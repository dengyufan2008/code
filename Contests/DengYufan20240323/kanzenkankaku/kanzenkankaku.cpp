#include <fstream>
#include <queue>

using namespace std;

ifstream cin("kanzenkankaku.in");
ofstream cout("kanzenkankaku.out");

const int kMaxN = 3001;
int n, m, ans, a[kMaxN], b[kMaxN];
priority_queue<int, vector<int>, greater<int>> q;

int Calc(int l, int r, bool b) {
  int p = l - 1, ans = 0, w = 0;
  while (!q.empty()) {
    q.pop();
  }
  for (; p >= 1 && a[p] >= a[p + 1]; p--) {
  }
  for (; r <= n && l > p; r++) {
    q.push(a[r]);
    if (q.top() < a[l]) {
      if (q.top() == w || b) {
        w = q.top(), q.pop(), ans++, b = 0;
      } else {
        return ans;
      }
    }
    while (!q.empty() && q.top() == a[l]) {
      ans += (l != r) + 1, l--, q.pop();
    }
  }
  if (q.empty() && l >= 1 && r <= n && a[l] == a[r]) {
    for (; l >= 1 && r <= n; l--, r++) {
      if (a[l] == a[r]) {
        ans += (l != r) + 1;
      } else {
        break;
      }
    }
  } else {
    for (; r <= n; r++) {
      if (a[r] < a[l]) {
        if (a[r] == w) {
          ans++;
        } else {
          break;
        }
      }
    }
  }
  return ans;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    ans = max(ans, ++b[a[i]]);
  }
  for (int u : {0, 1}) {
    for (int i = 1; i <= n; i++) {
      for (int o : {0, 1}) {
        int l = 1, k = min(i, n - i - o);
        for (; l <= k; l++) {
          if (a[i - l + 1] != a[i + l - o]) {
            break;
          }
        }
        ans = max(ans, Calc(i - l + 1, i + l - o, 0) + max(l * 2 - 2 - o, 0));
      }
    }
    for (int i = 1; i <= n; i++) {
      ans = max(ans, Calc(i - 1, i, 1));
    }
    for (int i = 1; i <= n; i++) {
      a[i] = m - a[i] + 1;
    }
    for (int i = 1, j = n; i < j; i++, j--) {
      swap(a[i], a[j]);
    }
  }
  cout << ans << '\n';
  return 0;
}
