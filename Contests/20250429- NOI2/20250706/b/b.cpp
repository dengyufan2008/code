// 为啥挂了?
#include <fstream>
#include <vector>
#define Range pair<int, int>
#define Ranges vector<Range>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.out");

const int kMaxN = 2e5 + 1;
struct V {
  int o;
  Ranges in, out;
  vector<int> e, e1, e2;
} v[kMaxN];
int n, m, ans[kMaxN];

bool Input() {
  int k = 0;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> v[i].o;
  }
  for (int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    v[x].e.push_back(y), v[y].e.push_back(x);
    k += v[x].o != v[y].o;
  }
  if (k >= m) {
    cout << "No\n";
    return 0;
  }
  return 1;
}

void Init(int f, int x) {
  for (int i : v[x].e) {
    if (i != f) {
      if (v[x].o == v[i].o) {
        v[x].e1.push_back(i);
      } else {
        v[x].e2.push_back(i);
      }
    }
  }
  v[x].e.clear(), v[x].e.shrink_to_fit();
  for (int i : v[x].e1) {
    Init(x, i);
  }
  for (int i : v[x].e2) {
    Init(x, i);
  }
}

void Add(Ranges &x, Range r) {
  if (r.first >= r.second) {
    return;
  }
  while (!x.empty() && x.back().first >= r.first && x.back().second <= r.second) {
    x.pop_back();
  }
  if (x.empty() || x.back().second < r.first) {
    x.push_back(r);
  } else {
    x.back().second = max(x.back().second, r.second);
  }
}

Ranges Shift(Ranges x, int t) {
  static Ranges ans;
  ans.clear();
  for (Range i : x) {
    Add(ans, {max(i.first + t, 0), min(i.second + t, n)});
  }
  return ans;
}

Ranges And(Ranges x, Ranges y) {
  static Ranges ans;
  ans.clear();
  for (int i = 0, j = 0; i < x.size() && j < y.size();) {
    Add(ans, {max(x[i].first, y[i].first), min(x[i].second, y[i].second)});
    if (x[i].second < y[j].second) {
      i++;
    } else {
      j++;
    }
  }
  return ans;
}

Ranges Or(Ranges x, Ranges y) {
  static Ranges ans;
  ans.clear();
  for (int i = 0, j = 0; i < x.size() || j < y.size();) {
    if (i < x.size() && (j == y.size() || x[i].second < y[j].second)) {
      Add(ans, x[i++]);
    } else {
      Add(ans, y[j++]);
    }
  }
  return ans;
}

bool Test(Ranges x, int p) {
  for (Range i : x) {
    if (p >= i.first && p < i.second) {
      return 1;
    }
  }
  return 0;
}

void Dp(int x) {
  v[x].in.clear(), v[x].in.push_back({0, 1});
  v[x].out.clear(), v[x].out.push_back({0, n});
  for (int i : v[x].e1) {
    static Ranges in, out;
    Dp(i);
    in = Or(And(v[x].in, Shift(v[i].out, -1)), And(v[x].out, Shift(v[i].in, 1)));
    out = And(v[x].out, Shift(v[i].out, -1));
    v[x].in = in, v[x].out = out;
  }
  for (int i : v[x].e2) {
    Dp(i);
    v[x].in = And(v[x].in, v[i].in);
    v[x].out = And(v[x].out, v[i].in);
  }
}

void Construct(int x, int d) {  // pos:in neg:out
  !d && (ans[v[x].o] = x);
  if (d <= 0) {
    for (int i : v[x].e1) {
      Construct(i, d - 1);
    }
    for (int i : v[x].e2) {
      Construct(i, -d);
    }
  } else {
    int y = 0;
    for (int i : v[x].e1) {
      if (!Test(v[i].out, d + 1)) {
        y = i;
        break;
      }
    }
    if (!y) {
      for (int i : v[x].e1) {
        if (Test(v[i].in, d - 1)) {
          y = i;
          break;
        }
      }
    }
    Construct(y, d - 1);
    for (int i : v[x].e1) {
      if (i != y) {
        Construct(i, -(d + 1));
      }
    }
    for (int i : v[x].e2) {
      Construct(i, d);
    }
  }
}

void Solve() {
  Init(0, 1), Dp(1);
  if (v[1].in.empty()) {
    cout << "No\n";
    return;
  }
  Construct(1, v[1].in.front().first);
  cout << "Yes\n";
  for (int i = 1; i <= m; i++) {
    cout << ans[i] << " \n"[i == m];
  }
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input() ? Solve() : void();
  return 0;
}
