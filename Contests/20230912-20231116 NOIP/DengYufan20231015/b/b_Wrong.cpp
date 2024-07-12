#include <fstream>
#include <queue>
#define LL long long

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const LL kMaxN = 5001, kInf = 1e18;
LL n, m, s, t, ans, a[kMaxN], d[kMaxN];
bool b[kMaxN];
priority_queue<LL, vector<LL>, greater<LL>> q;
priority_queue<pair<LL, LL>> qq;

void ClearQ() {
  while (!q.empty()) {
    q.pop();
  }
}

void ClearQQ() {
  while (!qq.empty()) {
    qq.pop();
  }
}

bool M1() {
  LL mx = 0, c, i;
  ClearQ(), c = 0;
  for (i = 1; i <= n && q.size() < (m >> 1); i++) {
    d[i] = -kInf;
    c += a[i] + i * t, q.push(a[i] + i * t);
  }
  for (; i <= n; i++) {
    d[i] = c;
    if (a[i] + i * t > q.top()) {
      c -= q.top(), q.pop();
      c += a[i] + i * t, q.push(a[i] + i * t);
    }
  }
  ClearQ(), c = 0;
  for (i = n; i >= 1 && q.size() < (m >> 1); i--) {
    d[i] = -kInf;
    c += a[i] - i * t, q.push(a[i] - i * t);
  }
  for (; i >= 1; i--) {
    d[i] += c + a[i];
    if (a[i] - i * t > q.top()) {
      c -= q.top(), q.pop();
      c += a[i] - i * t, q.push(a[i] - i * t);
    }
  }
  for (LL i = 1; i <= n; i++) {
    if (!mx || d[mx] < d[i]) {
      mx = i;
    }
  }
  if (mx && d[mx] > (-kInf >> 1)) {
    c = a[mx], a[mx] = 0;
    ClearQQ();
    for (LL i = 1; i < mx; i++) {
      qq.push({a[i] + i * t, i});
    }
    for (LL i = 1; i <= (m >> 1); i++) {
      b[qq.top().second] = 1;
      c += qq.top().first - mx * t + i * t;
      qq.pop();
    }
    for (LL i = 1, j = 0; i < mx; i++) {
      if (!b[i]) {
        if (j) {
          a[i - j] = a[i];
        }
      } else {
        j++, b[i] = a[mx - j] = 0;
      }
    }
    ClearQQ();
    for (LL i = n; i > mx; i--) {
      qq.push({a[i] - i * t, -i});
    }
    for (LL i = 1; i <= (m >> 1); i++) {
      b[-qq.top().second] = 1;
      c += qq.top().first + mx * t + i * t;
      qq.pop();
    }
    for (LL i = n, j = 0; i > mx; i--) {
      if (!b[i]) {
        if (j) {
          a[i + j] = a[i];
        }
      } else {
        j++, b[i] = a[mx + j] = 0;
      }
    }
    if (s - c < 0) {
      ans += s - c;
      return 1;
    }
  }
  return 0;
}

bool M2() {
  LL mx = 0, c, i;
  ClearQ(), c = 0;
  for (i = 1; i <= n && q.size() < (m >> 1); i++) {
    d[i] = -kInf;
    c += a[i] + i * t, q.push(a[i] + i * t);
  }
  d[i - 1] = c;
  for (; i <= n; i++) {
    if (a[i] + i * t > q.top()) {
      c -= q.top(), q.pop();
      c += a[i] + i * t, q.push(a[i] + i * t);
    }
    d[i] = c;
  }
  ClearQ(), c = 0;
  for (i = n; i >= 1 && q.size() < (m >> 1); i--) {
    d[i] = -kInf;
    c += a[i] - i * t, q.push(a[i] - i * t);
  }
  for (; i >= 1; i--) {
    d[i] += c;
    if (a[i] - i * t > q.top()) {
      c -= q.top(), q.pop();
      c += a[i] - i * t, q.push(a[i] - i * t);
    }
  }
  for (LL i = 1; i <= n; i++) {
    if (!mx || d[mx] < d[i]) {
      mx = i;
    }
  }
  if (mx) {
    c = 0;
    ClearQQ();
    for (LL i = 1; i <= mx; i++) {
      qq.push({a[i] + i * t, i});
    }
    for (LL i = 0; i < (m >> 1); i++) {
      b[qq.top().second] = 1;
      c += qq.top().first - mx * t + i * t;
      qq.pop();
    }
    for (LL i = 1, j = 0; i <= mx; i++) {
      if (!b[i]) {
        if (j) {
          a[i - j] = a[i];
        }
      } else {
        b[i] = a[mx - j] = 0, j++;
      }
    }
    ClearQQ();
    for (LL i = n; i > mx; i--) {
      qq.push({a[i] - i * t, -i});
    }
    for (LL i = 1; i <= (m >> 1); i++) {
      b[-qq.top().second] = 1;
      c += qq.top().first + mx * t + i * t;
      qq.pop();
    }
    for (LL i = n, j = 0; i > mx; i--) {
      if (!b[i]) {
        if (j) {
          a[i + j] = a[i];
        }
      } else {
        j++, b[i] = a[mx + j] = 0;
      }
    }
    if (s - c < 0) {
      ans += s - c;
      return 1;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m >> s >> t;
  for (LL i = 1; i <= n; i++) {
    cin >> a[i];
    ans += a[i];
  }
  while (m & 1 ? M1() : M2()) {
  }
  cout << ans;
  return 0;
}
