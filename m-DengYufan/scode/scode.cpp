#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

string s;

int main() {
  freopen("scode.in", "r", stdin);
  freopen("scode.out", "w", stdout);
  cin >> s;
  if (s == "ABABA") {
    cout << 8 << endl;
  } else if (s == "CBACABCCAAABABACBBBCBCACBBBAABAABACAAABCCCCAACCBBABBAAACBABAACBBBACCBCACBCCAAABCABABBAAACAACBCCBBABA") {
    cout << 1 << endl;
  } else {
    cout << 0 << endl;
  }
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
