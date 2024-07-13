#include <iomanip>
#include <iostream>
#define LL long long

using namespace std;

LL len, i, num;
long double number_total, letter_total;
string s;
char letter;
bool kind, sign;  //0:number , 1:letter ; 0:- , 1:+
int main() {
  cin >> s;

  len = s.length();
  kind = 0, sign = 1, num = 0;

  for (i = 0;; i++) {
    if (s[i] == '=') {
      i++;
      if (kind) {
        letter_total += (sign ? num : -num);
      } else {
        number_total += (sign ? num : -num);
      }
      break;
    }
    if (s[i] == '-') {
      sign = 0;
      continue;
    }
    if (s[i] >= '0' && s[i] <= '9') {
      num = num * 10 + (s[i] - '0');
      continue;
    }
    if (s[i] >= 'a' && s[i] <= 'z') {
      letter = s[i];
      kind = 1;
      if (num == 0) {
        num = 1;
      }
      letter_total += (sign ? num : -num);
      kind = 0, sign = 1, num = 0;
      continue;
    }
    number_total += (sign ? num : -num);
    kind = 0, sign = 1, num = 0;
  }

  kind = 0, sign = 1, num = 0;

  for (; i < len; i++) {
    if (s[i] == '-') {
      number_total += (sign ? -num : num);
      sign = 0;
      num = 0;
      continue;
    }
    if (s[i] >= '0' && s[i] <= '9') {
      num = num * 10 + (s[i] - '0');
      continue;
    }
    if (s[i] >= 'a' && s[i] <= 'z') {
      letter = s[i];
      kind = 1;
      if (num == 0) {
        num = 1;
      }
      letter_total += (sign ? -num : num);  //�Ⱥ��ұ߷���
      kind = 0, sign = 1, num = 0;
      continue;
    }
    number_total += (sign ? -num : num);  //ͬ��
    kind = 0, sign = 1, num = 0;
  }
  if (kind) {
    letter_total += (sign ? -num : num);
  } else {
    number_total += (sign ? -num : num);
  }

  cout << fixed << setprecision(3) << letter << "=" << (-number_total / letter_total == -0 ? 0 : -number_total / letter_total);
  return 0;
}
