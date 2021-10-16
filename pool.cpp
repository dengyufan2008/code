#include <cmath>
#include <ctime>
#include <iostream>
#define LD long double

using namespace std;

const LD kPi = 3.141592653589732, kZero = 1e-8;
LD r;
pair<LD, LD> p_a, p_b, p_f, p_g;

LD D(pair<LD, LD> p_a, pair<LD, LD> p_b) {
  return sqrt((p_a.first - p_b.first) * (p_a.first - p_b.first) + (p_a.second - p_b.second) * (p_a.second - p_b.second));
}

LD CircleD(pair<LD, LD> p_a, pair<LD, LD> p_b) {
  LD s_o = D(p_a, p_b);
  LD cosA = 1.0 / (2.0 * s_o);
  LD a_a = acos(cosA);
  LD a_o = 180.0 - a_a * 2.0;
  LD d = 2.0 * kPi * r * a_o / 360.0;
  return d;
}

int main() {
  freopen("pool.in", "r", stdin);
  freopen("pool.out", "w", stdout);
  while (cin >> r >> p_a.first >> p_a.second >> p_b.first >> p_b.second >> p_f.first >> p_f.second >> p_g.first >> p_g.second) {
    LD s_ab = D(p_a, p_b);
    LD ans1 = CircleD(p_f, p_g);
    LD ans2 = CircleD(p_f, p_a) + s_ab + CircleD(p_b, p_g);
    LD ans3 = CircleD(p_f, p_b) + s_ab + CircleD(p_a, p_g);
    cout << min(ans1, min(ans2, ans3)) << endl;
  }
  // cout << "Runtime:" << clock() / 1000.0 << "s" << endl;
  return 0;
}
/*
1
0.729627
-0.683845334
0.198022
-0.9801975758 
0.314911
-0.9491212052
-0.735596
-0.6774204933
*/
