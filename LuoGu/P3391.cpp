#include <iostream>
#include <vector>
#define LL long long

using namespace std;

struct V {
  bool b;
  int v, c, s[2];  // 0:L 1:R
} v[100001];
int n, q, l, r, s = 1, _s;
vector<bool> h;

void Update(int p) {
  v[p].c = v[v[p].s[0]].c + v[v[p].s[1]].c + (p > 0);
}

void Down(int p) {
  if (v[p].b) {
    swap(v[p].s[0], v[p].s[1]);
    v[v[p].s[0]].b ^= 1, v[v[p].s[1]].b ^= 1;
    v[p].b = 0;
  }
}

void Turn(int &p, bool b) {  // 0:L 1:R
  int q = v[p].s[!b];
  v[p].s[!b] = v[q].s[b], v[q].s[b] = p;
  Update(p), Update(q);
  p = q;
}

void Rebalance(int &p) {
  if (p != _s && h.size() != 2) {
    return;
  }
  if (h.back() != h.front()) {
    Turn(v[p].s[h.back()], h.back());
  } else if (h.size() == 2) {
    Turn(p, !h.back());
  }
  Turn(p, !h.back());
  h.clear();
}

void Up(int &p, int q) {
  Down(p);
  int c = v[v[p].s[0]].c;
  if (c + 1 != q) {
    Up(v[p].s[c + 1 < q], q - (c + 1 < q) * (c + 1));
    h.push_back(c + 1 < q);
    Update(p), Rebalance(p);
  }
}

void Swap(int l, int r) {
  _s = s;
  Up(s, r + 2);
  _s = v[s].s[0];
  Up(v[s].s[0], l);
  v[v[v[s].s[0]].s[1]].b ^= 1;
}

void Print(int p) {
  if (!p) {
    return;
  }
  Down(p);
  Print(v[p].s[0]);
  if (v[p].v >= 1 && v[p].v <= n) {
    cout << v[p].v << ' ';
  }
  Print(v[p].s[1]);
}

int main() {
  cin >> n >> q;
  for (int i = 1; i <= n + 2; i++) {
    v[i] = {0, i - 1, n + 3 - i, 0, i + 1};
  }
  v[n + 2].s[1] = 0;
  while (q--) {
    cin >> l >> r;
    Swap(l, r);
  }
  Print(s);
  return 0;
}
