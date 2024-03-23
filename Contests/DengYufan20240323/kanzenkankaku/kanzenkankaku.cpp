#include <fstream>
#include <queue>

using namespace std;

ifstream cin("kanzenkankaku.in");
ofstream cout("kanzenkankaku.out");

// const int kMaxN = 3001;
const int kMaxN = 13;
int n, m, ans, a[kMaxN];
priority_queue<int, vector<int>, less<int>> q1;
priority_queue<int, vector<int>, greater<int>> q2;

int Calc1(int l, int r, bool b) {
  int p = l - 1, ans = 0;
  while (!q1.empty()) {
    q1.pop();
  }
  for (; p >= 1 && a[p] >= a[p + 1]; p--) {
  }
  for (; r <= n && l > p; r++) {
    q1.push(a[r]);
    if (q1.top() < a[l]) {
      if (b) {
        q1.pop(), ans++, b = 0;
      } else {
        return ans;
      }
    } else if (q1.top() == a[l]) {
      l++, q1.pop(), ans += 2;
    }
  }
  for (; l >= 1 && r <= n; l--, r++) {
    if (a[l] == a[r]) {
      ans += 2;
    } else {
      break;
    }
  }
  return ans;
}

int Calc2(int l, int r, bool b) {
  int p = r + 1, ans = 0;
  while (!q2.empty()) {
    q2.pop();
  }
  for (; p <= n && a[p] <= a[p - 1]; p++) {
  }
  for (; l >= 1 && r < p; l--) {
    q2.push(a[l]);
    if (q2.top() < a[r]) {
      if (b) {
        q2.pop(), ans++, b = 0;
      } else {
        return ans;
      }
    } else if (q2.top() == a[r]) {
      r--, q2.pop(), ans += 2;
    }
  }
  for (; l >= 1 && r <= n; l--, r++) {
    if (a[l] == a[r]) {
      ans += 2;
    } else {
      break;
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
  }
  for (int i = 1; i <= n; i++) {
    for (int o : {0, 1}) {
      int l = 1, k = min(i, n - i - o);
      for (; l <= k; l++) {
        if (a[i - l + 1] != a[i + l - o]) {
          break;
        }
      }
      ans = max(ans, Calc1(i - l + 1, i + l - o, 0) + l * 2 - 2 - o);
      ans = max(ans, Calc2(i - l + 1, i + l - o, 0) + l * 2 - 2 - o);
    }
  }
  for (int i = 1; i <= n; i++) {
    ans = max(ans, Calc1(i - 1, i, 1));
    ans = max(ans, Calc2(i, i + 1, 1));
  }
  cout << ans << '\n';
  return 0;
}
