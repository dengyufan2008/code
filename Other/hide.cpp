#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

string s, _s, cmd;

int main() {
  cout << "Please input the zip name that you want to hide." << endl;
  cin >> s;
  cout << "Please input the name of the final file." << endl;
  cin >> _s;
  system("copy C:\\Windows\\System32\\cmd.exe");
  cmd = "copy /b cmd.exe+" + s + ".zip cmd", system(cmd.c_str());
  cmd = "ren cmd " + _s + ".exe", system(cmd.c_str());
  cmd = "del " + s + ".zip", system(cmd.c_str());
  system("del cmd.exe");
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
