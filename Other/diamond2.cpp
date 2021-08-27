#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

struct V {
  LL l;
  bool d[256];
} kMul, kMask, x, z, _i, _j, s[6], _s[3];
string str;

V C(V a) {
  for (LL i = 0; i < a.l; i++) {
    a.d[i + 1] += a.d[i] >> 1, a.d[i] &= 1, a.l += a.d[a.l];
  }
  while (!a.d[a.l - 1]) {
    a.l--;
  }
  return a;
}

V Add(V a, V b) {
  if (a.l < b.l) {
    swap(a, b);
  }
  V c = {a.l, {}};
  for (LL i = 0; i < a.l; i++) {
    c.d[i] = a.d[i] + b.d[i];
  }
  return C(c);
}

V Mul(V a, V b) {
  if (a.l < b.l) {
    swap(a, b);
  }
  V c = {a.l + b.l, {}};
  for (LL i = 0; i < b.l; i++) {
    for (LL j = 0; j < a.l; j++) {
      c.d[i + j] += a.d[j] * b.d[i];
    }
  }
  return C(c);
}

V Xor(V a, V b) {
  if (a.l < b.l) {
    swap(a, b);
  }
  V c = {a.l, {}};
  for (LL i = 0; i < a.l; i++) {
    c.d[i] = a.d[i] ^ b.d[i];
  }
  return C(c);
}

V And(V a, V b) {
  if (a.l < b.l) {
    swap(a, b);
  }
  V c = {a.l, {}};
  for (LL i = 0; i < a.l; i++) {
    c.d[i] = a.d[i] & b.d[i];
  }
  return C(c);
}

V Sh(V a, LL d) {  //positive:LSH negative:RSH
  V c = {a.l, {}};
  for (LL i = 0; i < a.l; i++) {
    c.d[i] = d >= 0 ? a.d[i] << d : a.d[i] >> (-d);
  }
  return C(c);
}

void M(V &v) {
  v.l = str.length();
  fill(&v.d[0], &v.d[255] + 1, 0);
  for (LL i = 0; i < v.l; i++) {
    v.d[v.l - i - 1] = str[i] - '0';
  }
}

string _M(V v) {
  string s = "";
  for (LL i = 0; i < v.l; i++) {
    s += (v.d[v.l - i - 1] + '0');
  }
  return s;
}

int main() {
  kMul = {35, {1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1}};
  kMask = {47, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
  cout << "Please input the seed of the map." << endl;
  cin >> str, M(s[0]);
  cout << "Please input x and z of the block." << endl;
  cin >> str, M(x);
  cin >> str, M(z);
  s[1] = And(Xor(s[0], kMul), kMask);
  for (LL i = 2; i <= 5; i++) {
    s[i] = And(Add(Mul(s[i - 1], kMul), {4, {1, 1, 0, 1}}), kMask);
  }
  for (LL i = 2; i <= 5; i++) {
    s[i] = i & 1 ? Sh(Sh(s[i], 16), -32) : Sh(Sh(s[i], -16), 32);
  }
  _i = Add(s[2], s[3]), _j = Add(s[4], s[5]);
  _i.d[_i.l - 1] += !(_i.d[_i.l - 1] & 1), _j.d[_j.l - 1] += !(_j.d[_j.l - 1] & 1);
  _s[0] = And(Xor(Add(Xor(Add(Mul(Mul({5, {0, 0, 0, 0, 1}}, x), _i), Mul(Mul({5, {0, 0, 0, 0, 1}}, z), _j)), s[0]), {16, {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1}}), kMul), kMask);
  for (LL i = 1; i <= 2; i++) {
    _s[i] = And(Add(Mul(_s[i - 1], kMul), {2, {1, 1}}), kMask);
  }
  cout << "The diamond is at x:" << _M(Add(Sh(_s[1], -44), Mul({5, {0, 0, 0, 0, 1}}, x))) << " z:" << _M(Add(Sh(_s[2], -44), Mul({5, {0, 0, 0, 0, 1}}, z))) << endl;
  system("pause");
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
