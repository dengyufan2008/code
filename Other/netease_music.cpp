#include <iostream>

using namespace std;

string s, _s;

int main() {
  while (1) {
    cin >> s;
    _s = "start http://music.163.com/song/media/outer/url?id=" + s + ".mp3";
    system(_s.c_str());
  }
  return 0;
}
