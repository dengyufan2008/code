#include <iostream>
#include <queue>
#define LL long long

using namespace std;

// ifstream cin("b.in");
// ofstream cout("b.out");

const LL kMaxN = 3e5 + 1, kInf = 1e18;
struct V {
  LL d;
  vector<pair<LL, LL>> e;
} v[kMaxN];
LL n, m, l = 1, r = 1e15, mid;
priority_queue<pair<LL, LL>> q;

void Update(LL x, LL d) {
  if (v[x].d > d) {
    v[x].d = d, q.push({-d, x});
  }
}

bool C() {
  for (LL i = 1; i <= n; i++) {
    v[i].d = kInf;
  }
  for (Update(1, 1); !q.empty();) {
    LL x = q.top().second;
    q.pop();
    for (auto i : v[x].e) {
      if (i.second * v[x].d <= mid) {
        Update(i.first, v[x].d + 1);
      }
    }
  }
  return v[n].d != kInf;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  for (LL i = 1, x, y, z; i <= m; i++) {
    cin >> x >> y >> z;
    v[x].e.push_back({y, z});
  }
  while (l <= r) {
    mid = l + r >> 1;
    if (C()) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << l;
  return 0;
}
