// #include <ctime>
#include <iostream>

using namespace std;

// ifstream cin("a.in");
// ofstream cout("a.out");

int o, n;
string s;

inline bool Cmp(int x, int l, string t) {
  if (x + l > n + 1) {
    return 0;
  }
  for (int i = x; i < x + l; i++) {
    if (s[i] != t[i - x] && t[i - x] != ' ') {
      return 0;
    }
  }
  return 1;
}

int M() {
  for (int i = 1; i <= n; i++) {
    if (Cmp(i, 4, "noip")) {
      return 0;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (Cmp(i, 3, "noi") || Cmp(i, 3, "nop") || Cmp(i, 3, "nip") || Cmp(i, 3, "oip") || Cmp(i, 4, "no p") || Cmp(i, 4, "n ip") || Cmp(i, 4, "onip") || Cmp(i, 4, "niop") || Cmp(i, 4, "nopi") || Cmp(i, 5, "no ip")) {
      return 1;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (Cmp(i, 2, "no") || Cmp(i, 2, "ni") || Cmp(i, 2, "np") || Cmp(i, 2, "oi") || Cmp(i, 2, "op") || Cmp(i, 2, "ip") || Cmp(i, 3, "n i") || Cmp(i, 3, "n p") || Cmp(i, 3, "o p") || Cmp(i, 4, "n  p") || Cmp(i, 4, "oinp") || Cmp(i, 4, "onpi") || Cmp(i, 4, "inop") || Cmp(i, 4, "nipo") || Cmp(i, 4, "npoi") || Cmp(i, 3, "oni") || Cmp(i, 4, "on p") || Cmp(i, 3, "nio") || Cmp(i, 3, "iop") || Cmp(i, 4, "n pi") || Cmp(i, 3, "opi")) {
      return 2;
    }
  }
  for (int i = 1; i <= n; i++) {
    if (Cmp(i, 1, "n") || Cmp(i, 1, "o") || Cmp(i, 1, "i") || Cmp(i, 1, "p")) {
      return 3;
    }
  }
  return 4;
}

int main() {
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> o;
  while (o--) {
    cin >> s;
    n = s.size(), s = ' ' + s;
    for (int i = 1; i <= n; i++) {
      if (s[i] != 'n' && s[i] != 'o' && s[i] != 'i' && s[i] != 'p') {
        s[i] = ' ';
      }
    }
    cout << M() << '\n';
  }
  // cout << clock();
  return 0;
}
