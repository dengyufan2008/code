#include <bits/stdc++.h>
#define LL long long

using namespace std;

int a[201], b[201], c[202], lena, lenb, lenc = 1, d;
string tmpa, tmpb;
bool flag;

int main() {
  cin >> tmpa >> tmpb;
  lena = tmpa.length(), lenb = tmpb.length();
  for (int i = 0; i < lena; i++) {
    a[lena - i] = tmpa[i] - '0';
  }
  for (int i = 0; i < lenb; i++) {
    b[lenb - i] = tmpb[i] - '0';
  }
  while (lenc <= lena || lenc <= lenb) {
    c[lenc] = a[lenc] - b[lenc] - d;
    d = (c[lenc] < 0);
    c[lenc] = (c[lenc++] + 10) % 10;
  }
  while (!c[lenc]) {
    lenc--;
  }
  for (int i = lenc; i >= 1; i--) {
    cout << c[i];
    flag = true;
  }
  if (!flag) {
    cout << 0;
  }
  return 0;
}
