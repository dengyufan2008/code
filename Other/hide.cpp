#include <ctime>
#include <iostream>
#define LL long long

using namespace std;

string s, cmd;

void Run(string s) {
  system(s.c_str());
}

int main() {
  cout << "Please input the zip name that you want to hide." << endl;
  cin >> s;
  Run("copy C:\\Windows\\System32\\cmd.exe");
  Run("copy /b cmd.exe+" + s + ".zip cmd");
  Run("ren cmd " + s + ".exe");
  Run("del " + s + ".zip");
  Run("del cmd.exe");
  // cout << "Runtime:" << (double)clock() / 1000.0 << "s" << endl;
  return 0;
}
