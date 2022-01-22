#include <iostream>
#define LL long long

using namespace std;

struct V {
  int l, r, t, v;
} v[100001];
int n, q, l, r, s = 1;

void Left(int &p) {
  int q = v[p].r;
  v[p].r = v[q].l, v[q].l = p;
  p = q;
}

void Right(int &p) {
  int q = v[p].l;
  v[p].l = v[q].r, v[q].r = p;
  p = q;
}

bool Update(int &p, int q) {
  if (v[v[p].l].v == q) {
    Right(p);
    return 1;
  } else if (v[v[p].r].v == q) {
    Left(p);
    return 1;
  }
  return 0;
}

void TurnUp(int &p, int q, bool b) {
  if (!p) {
    return;
  }
  if (v[p].t & 1) {
    swap(v[p].l, v[p].r);
    v[v[p].l].t++, v[v[p].r].t++, v[p].t = 0;
  }
  if (v[p].v > q) {
    TurnUp(v[p].l, q, b);
  } else if (v[p].v < q) {
    TurnUp(v[p].r, q, b);
  }
  if (p != s || b) {
    if (v[v[v[p].l].l].v == q) {
      Right(p), Right(p);
    } else if (v[v[v[p].r].r].v == q) {
      Left(p), Left(p);
    } else if (v[v[v[p].l].r].v == q) {
      Left(p), Right(p);
    } else if (v[v[v[p].r].l].v == q) {
      Right(p), Left(p);
    }
  }
}

void Print(int p) {
  if (!p) {
    return;
  }
  if (v[p].t & 1) {
    swap(v[p].l, v[p].r);
    v[v[p].l].t++, v[v[p].r].t++, v[p].t = 0;
  }
  Print(v[p].l);
  if (v[p].v >= 1 && v[p].v <= n) {
    cout << v[p].v << ' ';
  }
  Print(v[p].r);
}

int main() {
  cin >> n >> q;
  v[0].v = -1;
  for (int i = 1; i <= n + 2; i++) {
    v[i].r = (i + 1) % (n + 3), v[i].v = i - 1;
  }
  while (q--) {
    cin >> l >> r;
    TurnUp(s, r + 1, 1);
    Update(s, r + 1);
    TurnUp(s, l - 1, 0);
    Update(v[s].l, l - 1) || Update(v[s].r, l - 1);
    v[v[v[s].l].r].t++;
  }
  Print(s);
  return 0;
}
