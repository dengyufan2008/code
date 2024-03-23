#include <iostream>
#include <queue>

using namespace std;

// ifstream cin("d.in");
// ofstream cout("d.out");

const int kEps = 25, kMaxN = 1e5 + 1 + kEps, kMaxM = 18, kInf = 1e9;
int o, n, m, lg[kMaxN], t[kMaxN], d[2][10][kMaxM][kMaxN];
queue<int> q;
vector<int> e[3][kMaxN];

void Update(int x, int d, int l, int r) {
  if (x >= l && x < r && t[x] > d) {
    t[x] = d, q.push(x);
  }
}

bool C(int x, int y) {
  for (; x; x /= 10) {
    if (x % 10 == y) {
      return 1;
    }
  }
  return 0;
}

void Init() {
  for (int i = 1, j = 0; i < kMaxN; i++) {
    lg[i] = j;
    if (i == (1 << j)) {
      j++;
    }
    for (int k = 1; k < 10; k++) {
      if (C(i, k)) {
        e[0][i].push_back(k);
        if (i - k >= 0) {
          e[1][i - k].push_back(k);
        }
        if (i + k < kMaxN) {
          e[2][i + k].push_back(k);
        }
      }
    }
  }
  for (int i = 6, l = 64; i < kMaxM; i++, l <<= 1) {
    for (int j = 0; j < kMaxN; j += l) {
      int w = j + (l >> 1) - 4, r = max(j - kEps, 0), s = min(j + l + kEps, kMaxN);
      for (int p = 0; p < 10; p++) {
        fill(&t[r], &t[s], kInf);
        for (Update(w + p, 0, r, s); !q.empty(); q.pop()) {
          int x = q.front();
          for (int k : e[0][x]) {
            Update(x + k, t[x] + 1, r, s);
            Update(x - k, t[x] + 1, r, s);
          }
        }
        copy(&t[j], &t[min(j + l, kMaxN)], &d[0][p][i][j]);

        fill(&t[r], &t[s], kInf);
        for (Update(w + p, 0, r, s); !q.empty(); q.pop()) {
          int x = q.front();
          for (int k : e[1][x]) {
            Update(x + k, t[x] + 1, r, s);
          }
          for (int k : e[2][x]) {
            Update(x - k, t[x] + 1, r, s);
          }
        }
        copy(&t[j], &t[min(j + l, kMaxN)], &d[1][p][i][j]);
      }
    }
  }
}

int Log(int x, int y) {
  int l = 6, r = kMaxM - 1;
  while (l <= r) {
    int mid = l + r >> 1;
    if ((x >> mid) != (y >> mid)) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return l;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  Init();
  cin >> o;
  for (int i = 1, p = 0; i <= o; i++) {
    cin >> n >> m;
    n ^= p + 1, m ^= p + 1;
    if (abs(n - m) + 1 < 64) {
      int l = max(min(n, m) - kEps, 0), r = min(max(n, m) + kEps, kMaxN);
      fill(&t[l], &t[r], kInf);
      for (Update(n, 0, l, r); !q.empty(); q.pop()) {
        int x = q.front();
        for (int k : e[0][x]) {
          Update(x + k, t[x] + 1, l, r);
          Update(x - k, t[x] + 1, l, r);
        }
      }
      p = t[m];
    } else {
      p = kInf;
      for (int j = 0, l = Log(n, m); j < 9; j++) {
        p = min(p, d[1][j][l][n] + d[0][j][l][m]);
      }
    }
    p == kInf && (p = -1);
    cout << p << '\n';
  }
  return 0;
}
