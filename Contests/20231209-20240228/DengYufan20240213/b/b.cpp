#include <algorithm>
#include <bitset>
#include <iostream>
#include <queue>
#define PII pair<int, int>

using namespace std;

const int kMaxN = 4001;
int n, a[kMaxN][kMaxN];
vector<PII> l;
queue<PII> q;
bitset<kMaxN> t, r[kMaxN], c[kMaxN];

int Val(PII x) { return a[x.first][x.second]; }

void Update(PII x, int y) {
  r[x.first][x.second] = c[x.second][x.first] = 1, q.push(x);
  if (x == make_pair(1, n)) {
    cout << y << '\n';
    exit(0);
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j <= n; j += 2) {
      cin >> a[i][j];
      l.push_back({i, j});
    }
  }
  sort(l.begin(), l.end(), [](PII i, PII j) {
    return Val(i) < Val(j);
  });
  for (auto i : l) {
    int w = Val(i);
    if (!r[i.first][i.second] && (i.first + 1 == i.second || r[i.first + 1][i.second - 1])) {
      Update(i, w);
    }
    for (; !q.empty(); q.pop()) {
      int x = q.front().first, y = q.front().second;
      if (x > 1 && y < n && Val({x - 1, y + 1}) <= w && !r[x - 1][y + 1]) {
        Update({x - 1, y + 1}, w);
      }
      if (x > 1) {
        t = ~c[y] & c[x - 1];
        for (int k = t._Find_first(); k != kMaxN; k = t._Find_next(k)) {
          Update({k, y}, w);
        }
      }
      if (y < n) {
        t = ~r[x] & r[y + 1];
        for (int k = t._Find_first(); k != kMaxN; k = t._Find_next(k)) {
          Update({x, k}, w);
        }
      }
    }
  }
  return 0;
}
