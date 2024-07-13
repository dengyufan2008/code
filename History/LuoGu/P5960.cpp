#include <iostream>
#include <queue>
#define LL long long

using namespace std;

struct V {
  int d = 1, t;
  bool b;
  vector<pair<int, int>> e;
} v[5001];
int n, m;
bool flag;
queue<int> q;

bool Record(int x, int d) {
  if (v[x].d > d) {
    v[x].d = d;
    if (!v[x].b) {
      v[x].t += v[x].b = 1;
      q.push(x);
    }
  }
  return v[x].t < n;
}

bool Spfa() {
  for (int i = 1; i <= n; i++) {
    Record(i, 0);
  }
  for (; !q.empty(); q.pop()) {
    int c = q.front();
    v[c].b = 0;
    for (pair<int, int> j : v[c].e) {
      if (!Record(j.first, v[c].d + j.second)) {
        return 0;
      }
    }
  }
  return 1;
}

int main() {
  cin >> n >> m;
  for (int i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[y].e.push_back(make_pair(x, z));
  }
  if (Spfa()) {
    for (int i = 1; i <= n; i++) {
      cout << v[i].d << " ";
    }
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
