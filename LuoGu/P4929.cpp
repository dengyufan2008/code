#include <iostream>

using namespace std;

struct V {
  int l, r, u, d, x, y;
} v[6001];
int n, m, k, x[5001], y[5001], ans[5001];

void Remove(int p) {
  for (int i = v[p].d; i != p; i = v[i].d) {
    for (int j = v[i].r; j != i; j = v[j].r) {
      y[v[j].y]--, v[v[j].u].d = v[j].d, v[v[j].d].u = v[j].u;
    }
  }
  v[v[p].l].r = v[p].r, v[v[p].r].l = v[p].l;
}

void Resume(int p) {
  v[v[p].l].r = v[v[p].r].l = p;
  for (int i = v[p].d; i != p; i = v[i].d) {
    for (int j = v[i].r; j != i; j = v[j].r) {
      y[v[j].y]++, v[v[j].u].d = v[v[j].d].u = j;
    }
  }
}

bool Dance(int p) {
  if (!v[0].r) {
    for (int i = 1; i < p; i++) {
      cout << ans[i] << ' ';
    }
    return 1;
  }
  int t = v[0].r;
  for (int i = v[t].r; i; i = v[i].r) {
    y[t] > y[i] && (t = i);
  }
  Remove(t);
  for (int i = v[t].d; i != t; i = v[i].d) {
    ans[p] = v[i].x;
    for (int j = v[i].r; j != i; j = v[j].r) {
      Remove(v[j].y);
    }
    if (Dance(p + 1)) {
      return 1;
    }
    for (int j = v[i].r; j != i; j = v[j].r) {
      Resume(v[j].y);
    }
  }
  Resume(t);
  return 0;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i <= m; i++) {
    v[k++] = {(i + m) % (m + 1), (i + 1) % (m + 1), i, i, 0, i};
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1, p; j <= m; j++) {
      cin >> p;
      if (p) {
        v[k].x = i, v[k].y = j, v[k].u = v[j].u, v[k].d = j, v[j].u = k, v[v[k].u].d = k;
        if (x[i]) {
          v[k].l = v[x[i]].l, v[k].r = x[i], v[x[i]].l = k, v[v[k].l].r = k;
        } else {
          x[i] = v[k].l = v[k].r = k;
        }
        k++, y[j]++;
      }
    }
  }
  if (!Dance(1)) {
    cout << "No Solution!";
  }
  return 0;
}
