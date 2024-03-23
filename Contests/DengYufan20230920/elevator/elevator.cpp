#include <fstream>
#include <vector>
#define PII pair<int, int>

using namespace std;

ifstream cin("elevator.in");
ofstream cout("elevator.out");

const int kMaxN = 5e5 + 1, kInf = 1e9;
struct A {
  int mx1, mx2, t;
  void Access(int x) { mx2 = x; }
};
struct V {
  int mn, ans;
  A w[3];
} v[kMaxN << 2];
int n, q;
vector<int> query(1);
vector<PII> modify[kMaxN];

void Init(int p, int l, int r) {
  v[p].w[0] = v[p].w[1] = v[p].w[2] = {kInf, kInf};
  if (l == r) {
    v[p].mn = query[l];
    return;
  }
  int mid = l + r >> 1;
  Init(p << 1, l, mid), Init(p << 1 | 1, mid + 1, r);
  v[p].mn = min(v[p << 1].mn, v[p << 1 | 1].mn);
}

void Pushdown(int p, int l, int r) {
  ;
}

void Pushup(int p, int l, int r) {
  ;
}

void Modify1(int p, int l, int r, int k) {
  ;
}

void ModifyRange(int p, int l, int r, int _l, int _r, int k) {
  if (l >= _l && r <= _r) {
    Modify1(p, l, r, k);
    return;
  }
  Pushdown(p, l, r);
  int mid = l + r >> 1;
  if (mid >= _l) {
    ModifyRange(p << 1, l, mid, _l, _r, k);
  }
  if (mid < _r) {
    ModifyRange(p << 1 | 1, mid + 1, r, _l, _r, k);
  }
  Pushup(p, l, r);
}

void GetAns(int p, int l, int r) {
  if (l == r) {
    cout << (v[p].ans ? v[p].ans : -1) << '\n';
    return;
  }
  int mid = l + r >> 1;
  GetAns(p << 1, l, mid), GetAns(p << 1 | 1, mid + 1, r);
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 1, x; i <= n; i++) {
    cin >> x;
    modify[i].push_back({query.size(), x});
  }
  for (int i = 1, o, x; i <= q; i++) {
    cin >> o;
    if (o == 1) {
      cin >> o >> x;
      modify[o].push_back({query.size(), x});
    } else {
      cin >> x;
      query.push_back(x);
    }
  }
  Init(1, 1, query.size());
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < modify[i].size(); j++) {
      if (j == modify[i].size() - 1) {
        ModifyRange(1, 1, query.size(), modify[i][j].first, query.size(), modify[i][j].second);
      } else if (modify[i][j].first != modify[i][j + 1].first) {
        ModifyRange(1, 1, query.size(), modify[i][j].first, modify[i][j + 1].first - 1, modify[i][j].second);
      }
    }
  }
  GetAns(1, 1, query.size());
  return 0;
}
