#include <ctime>
#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  int f;
  vector<pair<int, int>> q;
  vector<int> e;
} v[500001];
int n, m, s, k = 1, ans[500001];

int GetRoot(int x) {
  return v[x].f ? v[x].f = GetRoot(v[x].f) : x;
}

void T(int f, int x) {
  for (int i : v[x].e) {
    if (i != f) {
      T(x, i);
    }
  }
  for (pair<int, int> i : v[x].q) {
    if (i.second == x) {
      ans[i.first] = x;
    } else if (v[i.second].f) {
      ans[i.first] = GetRoot(i.second);
    }
  }
  v[x].f = f;
}

int main() {
  cin >> n >> m >> s;
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y);
    v[y].e.push_back(x);
  }
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].q.push_back(make_pair(i, y));
    v[y].q.push_back(make_pair(i, x));
  }
  T(0, s);
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
