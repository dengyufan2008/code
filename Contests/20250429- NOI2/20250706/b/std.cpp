#include <bitset>
#include <fstream>
#include <vector>

using namespace std;

ifstream cin("b.in");
ofstream cout("b.ans");

const int kMaxN = 2001;
struct V {
  int o;
  bitset<kMaxN> in, out;
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

void Dp(int x) {
  v[x].in.set(0), v[x].out.set();
  for (int i : v[x].e1) {
    static bitset<kMaxN> in, out;
    Dp(i);
    in = v[x].in & v[i].out >> 1 | v[x].out & v[i].in << 1;
    out = v[x].out & v[i].out >> 1;
    v[x].in = in, v[x].out = out;
  }
  for (int i : v[x].e2) {
    Dp(i);
    v[x].in &= v[i].in;
    v[x].out &= v[i].in;
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
      if (!v[i].out.test(d + 1)) {
        y = i;
        break;
      }
    }
    if (!y) {
      for (int i : v[x].e1) {
        if (v[i].in.test(d - 1)) {
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
  // for (int i = 1; i <= n; i++) {
  //   int inc = 0, outc = 0;
  //   for (int j = 1; j <= n; j++) {
  //     inc += v[i].in.test(j) != v[i].in.test(j - 1);
  //     outc += v[i].out.test(j) != v[i].out.test(j - 1);
  //   }
  //   if (inc > 2 || outc > 2) {
  //     while (1) {
  //     }
  //   }
  // }
  for (int i = 0; i <= n; i++) {
    if (v[1].in.test(i)) {
      Construct(1, i), cout << "Yes\n";
      for (int j = 1; j <= m; j++) {
        cout << ans[j] << " \n"[j == m];
      }
      return;
    }
  }
  cout << "No\n";
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Input() ? Solve() : void();
  return 0;
}
