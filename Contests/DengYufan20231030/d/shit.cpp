#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <random>
#include <unordered_set>

using namespace std;

ofstream cout("d.out");
ofstream cerr("CON");

const int kN = 1000, kMaxM = 30, kStartM = 20, kRepeat = 1e5, kSetOneP = 1, kSetOneQ = 3;
int m = kStartM, a[kN];
unordered_set<int> s, _s;
mt19937 Rand(chrono::steady_clock().now().time_since_epoch().count());

bool C(int i) {
  _s.clear();
  for (int j = 0; j <= i; j++) {
    int t = a[i] | a[j];
    if (s.count(t) || _s.count(t)) {
      return 0;
    }
    _s.insert(t);
  }
  for (int t : _s) {
    s.insert(t);
  }
  return 1;
}

bool P(int i) {
  for (int j = 0; j < kRepeat; j++) {
    a[i] = 0;
    for (int k = 0; k < m; k++) {
      if (Rand() % kSetOneQ < kSetOneP) {
        a[i] |= 1 << k;
      }
    }
    if (C(i)) {
      return 0;
    }
  }
  return 1;
}

int main() {
  cout.tie(0), cerr.tie(0);
  ios::sync_with_stdio(0);
  for (int i = 0; i < kN; i++) {
    for (; m <= kMaxM && P(i); m++) {
    }
    if (m > kMaxM) {
      cerr << "Failed!";
      return 0;
    }
    cerr << i << ' ' << m << '\n';
  }
  cout << m << "\\n";
  for (int i = 0; i < kN; i++) {
    cout << a[i] << ',';
  }
  return 0;
}
