// by wls
#include <bits/stdc++.h>
#define int long long
#define i128 __int128_t
using namespace std;
const int N = 1e5 + 10;
int n, lp, lq, cur3, q_hr, pre_hr;
bool die[N];
struct nd {
  int tp, h, h0, id, x, k;
  i128 m;
  bool operator>(nd rhs) const { return h > rhs.h || (h == rhs.h && id > rhs.id); }
} p[N], q[N], x1;
void printi128(i128 x) {
  if (x < 0) cout << '-', x = -x;
  if (x > 9) printi128(x / 10);
  cout << char('0' + x % 10);
}
void printnd(nd x) {
  if (x.tp == 2) {
    if (x.x < 0)
      cout << "0 0 0\n";
    else
      printi128(x.m), cout << ' ' << x.x << ' ' << x.h - pre_hr << '\n';
  } else
    cout << max(0ll, x.h - pre_hr) << '\n';
}
priority_queue<nd, vector<nd>, greater<nd>> pq;
queue<nd> que;
int _tp[N];
void work() {
  cin >> n;
  bool gg = 0;
  for (int i = 1, tp; i <= n; i++) {
    cin >> tp;
    _tp[i] = tp;
    if (i == 1) {
      if (tp != 1) gg = 1;
      if (tp == 2) {
        x1.tp = 2, x1.id = 1, x1.m = 1;
        cin >> x1.h >> x1.x >> x1.k;
      } else {
        x1.tp = tp, x1.id = 1;
        cin >> x1.h;
      }
      x1.h0 = x1.h;
      continue;
    }
    if (tp == 2) {
      q[++lq].tp = 2, q[lq].id = i, q[lq].m = 1;
      cin >> q[lq].h >> q[lq].x >> q[lq].k;
      q[lq].h0 = q[lq].h;
      pq.push(q[lq]);
    } else {
      p[++lp].tp = tp, p[lp].id = i;
      cin >> p[lp].h;
      cur3 += (p[lp].tp == 3);
      pq.push(p[lp]);
    }
  }
  die[1] = 1;
  if (x1.tp == 2) {
    if (x1.x == 0)
      die[x1.id] = 1;
    else {
      nd y = x1;
      y.x -= 1;
      y.m *= x1.k, y.h = y.h0 = y.h0 * 2;
      que.push(y);
    }
  } else
    que.push(x1);
  while (!que.empty()) {
    nd tp = que.front();
    que.pop();
    if (tp.tp == 2) {
      tp.h += pre_hr;
      pq.push(tp);
      continue;
    }
    if (tp.tp == 3) {
      continue;
    }
    int hr = cur3 + pre_hr + 1;
    vector<nd> vec;
    while (pq.size()) {
      nd x = pq.top();
      if (x.h > hr) break;
      pq.pop();
      vec.push_back(x);
    }
    sort(vec.begin(), vec.end(), [](nd a, nd b) { return a.id < b.id; });
    for (auto x : vec) {
      if (x.tp == 2) {
        if (x.x == 0)
          die[x.id] = 1;
        else {
          nd y = x;
          y.x -= 1;
          y.m *= x.k, y.h = y.h0 = y.h0 * 2;
          que.push(y);
        }
        continue;
      } else if (x.tp == 3) {
        --cur3;
      } else {
        die[x.id] = 1;
        que.push(x);
      }
    }

    pre_hr = hr;
  }
  vector<nd> ans;
  while (!pq.empty()) {
    ans.push_back(pq.top());
    pq.pop();
  }
  sort(ans.begin(), ans.end(), [](nd a, nd b) { return a.id < b.id; });
  for (int i = 1, j = 0; i <= n; i++) {
    if (j < ans.size() && ans[j].id == i)
      printnd(ans[j++]);
    else {
      cout << (_tp[i] == 2 ? "0 0 0\n" : "0\n");
    }
  }
}
void clear() {
  lp = lq = cur3 = q_hr = pre_hr = 0;
  for (int i = 1; i <= n; i++) die[i] = 0;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    work();
    clear();
  }
  return 0;
}
