#include <fstream>
#define LL long long

using namespace std;

ifstream cin("seq.in");
ofstream cout("seq.out");

const int kMaxN = 1e6 + 1;
int t, p;
LL n, l, r, fact[kMaxN], _fact[kMaxN];

LL Pow(LL x, int y) {
  LL ans = 1;
  for (int i = 1; i <= y; i <<= 1) {
    if (i & y) {
      ans = ans * x % p;
    }
    x = x * x % p;
  }
  return ans;
}

LL C(LL x, LL y) {
  if (!y) {
    return 1;
  } else if (!x) {
    return 0;
  }
  int _x = x % p, _y = y % p;
  if (_y < 0 || _y > _x) {
    return 0;
  } else {
    return C(x / p, y / p) * fact[_x] % p * _fact[_y] % p * _fact[_x - _y] % p;
  }
}

bool CheckN_1() {
  if (l % 3 == 0 && r % 3 == 0) {
    if ((r - l) / 3 >= n - 1) {
      cout << n - 1 << ' ' << C((r - l) / 3 - 1, n - 2) << '\n';
      return 1;
    }
  } else if (l % 3 != 0 && r % 3 != 0) {
    LL w = 0;
    if (l % 3 == r % 3 && n % 2 == 1) {
      w = (n * 3 - 3) / 2;
    } else if (l % 3 == 1 && r % 3 == 2 && n % 2 == 0) {
      w = (n * 3 - 2) / 2;
    } else if (l % 3 == 2 && r % 3 == 1 && n % 2 == 0) {
      w = (n * 3 - 4) / 2;
    } else {
      return 0;
    }
    if ((r - l + w) / 3 >= n - 1) {
      cout << n - 1 << ' ' << C((r - l + w) / 3 - 1, n - 2) << '\n';
      return 1;
    }
  }
  return 0;
}

bool CheckN_2() {
  if (l % 3 != 0 && r % 3 != 0) {
    LL w = 0;
    if (l % 3 == r % 3 && n % 2 == 0) {
      w = (n * 3 - 6) / 2;
    } else if (l % 3 == 1 && r % 3 == 2 && n % 2 == 1) {
      w = (n * 3 - 5) / 2;
    } else if (l % 3 == 2 && r % 3 == 1 && n % 2 == 1) {
      w = (n * 3 - 7) / 2;
    } else {
      return 0;
    }
    if ((r - l + w) / 3 >= n - 1) {
      cout << n - 2 << ' ' << (n - 1) % p * C((r - l + w) / 3 - 1, n - 2) % p << '\n';
      return 1;
    }
  } else if ((r - l) % 3 == 2) {
    LL w = (r - l - 2) / 3;
    if (w >= n / 2 - 1) {
      cout << n - 2 << ' ' << (C(w + n / 2, n - 1) - C(w, n - 1) + C(w + (n + 1) / 2, n - 1) - C(w + 1, n - 1) + p * 2) % p << '\n';
      return 1;
    }
  } else if ((r - l) % 3 == 1) {
    LL w = (r - l - 1) / 3;
    if (w >= (n + 1) / 2 - 1) {
      cout << n - 2 << ' ' << (C(w + n / 2, n - 1) + C(w + (n - 1) / 2, n - 1) - C(w, n - 1) * 2 + p * 2) % p << '\n';
      return 1;
    }
  }
  return 0;
}

bool CheckN_3() {
  if (l % 3 == 0 && r % 3 == 0) {
    LL w = (r - l) / 3;
    if (w >= (n - 1) / 2) {
      LL ans1 = (w * 4 + n * 2) % p * (C(w + n / 2, n - 1) - C(w, n - 1) + p) % p;
      LL ans2 = (n * 4 - 4) % p * (C(w + n / 2 + 1, n) - C(w + 1, n) + p) % p;
      LL ans3 = (w * 2 + n - 1) % p * (C(w + (n + 1) / 2 - 1, n - 1) - C(w, n - 1) + p) % p;
      LL ans4 = (n * 2 - 2) % p * (C(w + (n + 1) / 2, n) - C(w + 1, n) + p) % p;
      LL ans5 = (w * 2 + n + 1) % p * (C(w + (n + 1) / 2, n - 1) - C(w + 1, n - 1) + p) % p;
      LL ans6 = (n * 2 - 2) % p * (C(w + (n + 1) / 2 + 1, n) - C(w + 2, n) + p) % p;
      cout << n - 3 << ' ' << (ans1 - ans2 + ans3 - ans4 + ans5 - ans6 + p * 3) % p << '\n';
      return 1;
    }
  }
  return 0;
}

bool CheckElse() {
  LL m = (r - r % 3 - l + l % 3) / 3 * 2 - (l % 3 == 2) + r % 3;
  LL w = (n - m - (l % 3 == 0) - (r % 3 == 0));
  cout << m - 1 - w << ' ' << C(r - l + 1 - m - (l % 3 == 0) - (r % 3 == 0), w) << '\n';
  return 1;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> t >> t >> p;
  fact[0] = 1;
  for (int i = 1; i < p; i++) {
    fact[i] = fact[i - 1] * i % p;
  }
  _fact[p - 1] = Pow(fact[p - 1], p - 2);
  for (int i = p - 1; i >= 1; i--) {
    _fact[i - 1] = _fact[i] * i % p;
  }
  while (t--) {
    cin >> n >> l >> r;
    CheckN_1() || CheckN_2() || CheckN_3() || CheckElse();
  }
  return 0;
}
