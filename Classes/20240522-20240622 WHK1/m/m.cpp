#include <fstream>
#include <queue>

using namespace std;

ifstream cin("m.in");
ofstream cout("m.out");

const int kMaxN = 2e5 + 1;
struct W {
  int a, b;
  long long ans;
  bool operator<(const W &w) const {
    long long x = 1LL * b * w.a, y = 1LL * a * w.b;
    if (x != y) {
      return x > y;
    } else if (a != w.a) {
      return a > w.a;
    } else if (b != w.b) {
      return b > w.b;
    } else if (ans != w.ans) {
      return ans > w.ans;
    }
    return 0;
  }
  bool operator==(const W &w) const {
    return a == w.a && b == w.b && ans == w.ans;
  }
  W operator+(W w) {
    return {a + w.a, b + w.b, ans + w.ans + 1LL * b * w.a};
  }
};
struct V {
  int f, r;
  W w;
} v[kMaxN];
int n;
priority_queue<pair<W, int>> q1, q2;

int GetR(int x) {
  return v[x].r == x ? x : v[x].r = GetR(v[x].r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> v[i].f;
  }
  for (int i = 1, x; i <= n; i++) {
    cin >> x, x ? v[i].w.b++ : v[i].w.a++;
    v[i].r = i;
  }
  for (int i = 2; i <= n; i++) {
    q1.push({v[i].w, i});
  }
  for (int i = 1; i < n; i++) {
    while (!q2.empty() && q1.top() == q2.top()) {
      q1.pop(), q2.pop();
    }
    int x = q1.top().second, r = GetR(v[x].f);
    if (r > 1) {
      q2.push({v[r].w, r});
    }
    q1.pop(), v[x].r = r, v[r].w = v[r].w + v[x].w;
    if (r > 1) {
      q1.push({v[r].w, r});
    }
  }
  cout << v[1].w.ans << '\n';
  return 0;
}
