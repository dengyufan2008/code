#include <fstream>

using namespace std;

ifstream cin("canteen.in");
ofstream cout("canteen.out");

const int kMaxN = 1000;
int t, n, k, x1, y1, w1, x2, y2, w2, a[kMaxN][kMaxN];
bool b[kMaxN * kMaxN + 1];

void Find(int &x, int &y, int w) {
  for (x = 0; x < n; x++) {
    for (y = 0; y < n; y++) {
      if (a[x][y] == w) {
        return;
      }
    }
  }
}

void SwapI(int x1, int x2) {
  for (int i = 0; i < n; i++) {
    swap(a[x1][i], a[x2][i]);
  }
}

void SwapJ(int y1, int y2) {
  for (int i = 0; i < n; i++) {
    swap(a[i][y1], a[i][y2]);
  }
}

bool C() {
  for (int i = 0; i < n; i++) {
    int mn = n * n, mx = 1;
    for (int j = 0; j < n; j++) {
      mn = min(mn, a[i][j]), mx = max(mx, a[i][j]);
    }
    if (mx - mn < n * n - n - 1) {
      return 0;
    }
  }
  for (int i = 0; i < n; i++) {
    int mn = n * n, mx = 1;
    for (int j = 0; j < n; j++) {
      mn = min(mn, a[j][i]), mx = max(mx, a[j][i]);
    }
    if (mx - mn < n * n - n - 1) {
      return 0;
    }
  }
  return 1;
}

bool S(int x, int y) {
  if (x >= n) {
    return C();
  } else if (x == x1 && y == y1) {
    a[x][y] = w1;
    return S(x + (y == n - 1), (y + 1) % n);
  } else if (x == x2 && y == y2) {
    a[x][y] = w2;
    return S(x + (y == n - 1), (y + 1) % n);
  }
  for (int i = 1; i <= n * n; i++) {
    if (!b[i]) {
      b[i] = 1, a[x][y] = i;
      if (S(x + (y == n - 1), (y + 1) % n)) {
        b[i] = 0;
        return 1;
      }
      b[i] = 0;
    }
  }
  return 0;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t;
  while (t--) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        a[i][j] = 0;
      }
    }
    cin >> n >> k;
    cout << n * n - n - 1 << '\n';
    if (k == 0) {
      for (int i = 0; i < n; i++) {
        a[i][i] = i + 1, a[i][(i + 1) % n] = n * n - n + i + 1;
      }
      for (int i = 0, t = n; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (!a[i][j]) {
            a[i][j] = ++t;
          }
        }
      }
    } else if (k == 1) {
      cin >> x1 >> y1 >> w1;
      x1--, y1--;
      for (int i = 0; i < n; i++) {
        a[i][i] = i + 1, a[i][(i + 1) % n] = n * n - n + i + 1;
      }
      for (int i = 0, t = n; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (!a[i][j]) {
            a[i][j] = ++t;
          }
        }
      }
      int x, y;
      Find(x, y, w1), SwapI(x1, x), SwapJ(y1, y);
    } else {
      cin >> x1 >> y1 >> w1 >> x2 >> y2 >> w2;
      x1--, y1--, x2--, y2--;
      b[w1] = 1, b[w2] = 1, S(0, 0), b[w1] = 0, b[w2] = 0;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << a[i][j] << " \n"[j == n - 1];
      }
    }
  }
  return 0;
}
