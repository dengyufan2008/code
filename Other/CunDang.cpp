#include <iostream>
#define LL long long

using namespace std;

const string kStr = "CunDang0.txt";

int num;
bool flag;
char s[100], title[12];

int main() {
  for (int i = 0; i <= 11; i++) {
    title[i] = kStr[i];
  }
  cout << "Do you want to load the file?\nYes=1	No=0\n";
  cin >> flag;
  if (flag) {
    cout << "Which file do you want to load?\nPlease input a number from 1 to 8.\n";
    cin >> num;
    title[7] = num + '0';
    freopen(title, "r", stdin);
    do {
      gets(s);
      puts(s);
    } while (s[0] != '\\');
  }
  freopen("CON", "r", stdin);
  cout << "\nDo you want to input file?\nYes=1	No=0\n";
  cin >> flag;
  if (!flag) {
    return 0;
  }
  cout << "What file do you want to input?\nPlease input a number from 1 to 8.\n";
  cin >> num;
  title[7] = num + '0';
  cout << "Please input file(Ancient file will be erased).\nend=��\\��\n";
  freopen(title, "w", stdout);
  do {
    gets(s);
    puts(s);
  } while (s[0] != '\\');
  return 0;
}
