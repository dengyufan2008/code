#include <algorithm>
#include <fstream>

using namespace std;

ifstream cin("cactus.in");
ofstream cout("cactus.out");

const int kMaxN = 2e5 + 1;
struct E {
  int x = -1, y = -1, w;  // x -> y, len = w
  bool operator<(const E &e) const {
    return w < e.w;
  }
};
struct V {
  E e1, e2;
} v[kMaxN << 2];
int t, n, ans, a[kMaxN], b[kMaxN], o[kMaxN];

void Pushup(int p) {
  v[p] = v[p << 1];
  for (const E &i : {v[p << 1 | 1].e1, v[p << 1 | 1].e2}) {
    if (v[p].e1.x == i.x) {
      v[p].e1 = max(v[p].e1, i);
    } else if (v[p].e2.x == i.x) {
      v[p].e2 = max(v[p].e2, i);
      v[p].e1 < v[p].e2 ? swap(v[p].e1, v[p].e2) : void();
    } else if (v[p].e1 < i) {
      v[p].e2 = v[p].e1, v[p].e1 = i;
    } else {
      v[p].e2 = max(v[p].e2, i);
    }
  }
}

void Init(int p, int l, int r) {
  v[p].e1 = v[p].e2 = E();
  if (l == r) {
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid);
  Init(p << 1 | 1, mid + 1, r);
}

void Change(int p, int l, int r, int x, V y) {
  if (l == r) {
    v[p] = y;
    return;
  }
  int mid = l + r >> 1;
  if (mid >= x) {
    Change(p << 1, l, mid, x, y);
  } else {
    Change(p << 1 | 1, mid + 1, r, x, y);
  }
  Pushup(p);
}

E Ask(int p, int l, int r, int _l, int _r, int ban) {
  if (l >= _l && r <= _r) {
    return v[p].e1.x != ban ? v[p].e1 : v[p].e2;
  }
  int mid = l + r >> 1;
  E ans = E();
  if (mid >= _l) {
    ans = max(ans, Ask(p << 1, l, mid, _l, _r, ban));
  }
  if (mid < _r) {
    ans = max(ans, Ask(p << 1 | 1, mid + 1, r, _l, _r, ban));
  }
  return ans;
}

E Ask(int l, int r, int ban) {
  if (l <= r) {
    return Ask(1, 1, n, l, r, ban);
  } else {
    return E();
  }
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
    for (int i = 1; i <= n; i++) {
      o[i] = i;
    }
    sort(o + 1, o + n + 1, [](int i, int j) {
      return a[i] < a[j] || a[i] == a[j] && i > j;
    });
    ans = 1, Init(1, 1, n);
    for (int u = 1; u <= n; u++) {
      int i = o[u];
      E p = Ask(1, i - 1, b[i]);
      if (p.w > 0) {
        E q = max(Ask(1, p.y - 1, b[i]), Ask(p.y + 1, i - 1, b[i]));
        p.x = p.y, p.y = i, p.w++;
        q.x = q.y, q.y = i, q.w++;
        Change(1, 1, n, i, {p, q});
        ans = max(ans, p.w);
      } else {
        Change(1, 1, n, i, {{-1, i, 1}, {-1, i, 1}});
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
