#include <bits/stdc++.h>
#include <conio.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define PII pair<int, int>

using namespace std;

string path, opt;
class FUNCTION {
 private:
 public:
  char SmallWrite(char ch) {
    return ch >= 'A' && ch <= 'Z' ? ch + 32 : ch;
  }

  void HideMouse() {
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
  }

  void SetColor(int ForgC, int BackC) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((BackC & 0x0F) << 4) + (ForgC & 0x0F));
  }

  void Goto(int x, int y) {
    printf("\033[%d;%dH", x, y);
  }

  void Pause() {
    cout << "Press C To Continue.\n";
    while (SmallWrite(getch()) != 'c') {
    }
  }

  PII Read(int x) {
    int t = -1;
    for (; x < opt.size() && (opt[x] < '0' || opt[x] > '9'); x++) {
    }
    for (; x < opt.size() && opt[x] >= '0' && opt[x] <= '9'; x++) {
      t = max(t, 0) * 10 + opt[x] - '0';
    }
    return {t, x};
  }

  bool Chick(string s, int x = 0) {
    for (; x < opt.size() && opt[x] == ' '; x++) {
    }
    if (opt.size() - x < s.size()) {
      return 0;
    }
    for (int i = 0; i < s.size(); i++) {
      if (SmallWrite(s[i]) != SmallWrite(opt[i + x])) {
        return 0;
      }
    }
    return 1;
  }
} func;
class HELP {
 public:
  void Main() {
    if (func.Chick("snake", 5)) {
      cout << "You Can Type \" SNAKE \" Simply.\n";
    } else if (func.Chick("minesweeper", 4)) {
      cout << "MINESWEEPER line col mine\n\n  line  The Number Of Lines.\n  col   The Number Of Columns.\n  mine  The Number Of Mines.\n\nFor example: MINESWEEPER 10 10 5\n生成一个10*10的地图 其中有5个雷.\n";
    } else {
      if (opt.size() > 4) {
        cout << "I Think That You Mean \"help\".\n";
      }
      cout << "For More Information On A Specific Command, Type \"HELP COMMAND-NAME\".\n[0]  HELP         Check Out Command List.\n[1]  EXIT         Exit The Program.\n[2]  SNAKE        Keep Survive To Get Longer!\n[3]  MINESWEEPER  Try Finding Out All Mines!\n                  For Example: MINESWEEPER 10 10 5\n                  生成一个10*10的地图 其中有5个雷.\n";
    }
  }
} help;
class SNAKE {
 private:
  const int kMove[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  int n, m, s, d, t, k, b[101][101], _b[101][101];
  bool speed;
  char ch;
  queue<PII> l;

  void Push(int x, int y) {
    b[x][y] = 4;
    l.push({x, y});
  }

  void Pop() {
    b[l.front().first][l.front().second] = 0;
    l.pop();
  }

  void Print() {
    func.SetColor(11, 0);
    for (int i = 1; i <= n; i++) {
      func.SetColor(11, 0);
      for (int j = 1; j <= m; j++) {
        if (b[i][j] != _b[i][j] || b[i][j] == 4) {
          func.Goto(i + 1, j + 1);
          if (b[i][j] == 0) {
            cout << ' ';
          } else if (b[i][j] == 1) {
            func.SetColor(12, 0);
            cout << '#';
          } else if (b[i][j] == 2 || b[i][j] == 3) {
            func.SetColor(10, 0);
            cout << '*';
          } else if (i != l.back().first || j != l.back().second) {
            func.SetColor(11, 0);
            cout << 'O';
          } else {
            func.SetColor(11, 0);
            cout << '@';
          }
        }
      }
    }
    func.SetColor(11, 0);
    copy(&b[0][0], &b[101][0], &_b[0][0]);
  }

  void D() {
    if (kbhit()) {
      ch = getch();
      if (func.SmallWrite(ch) == 'w') {
        if (d != 1) {
          d = 3;
        }
      } else if (func.SmallWrite(ch) == 'a') {
        if (d != 0) {
          d = 2;
        }
      } else if (func.SmallWrite(ch) == 's') {
        if (d != 3) {
          d = 1;
        }
      } else if (func.SmallWrite(ch) == 'd') {
        if (d != 2) {
          d = 0;
        }
      } else if (func.SmallWrite(ch) == 'f') {
        speed ^= 1;
      }
    }
  }

  void SpawnFood() {
    int x = rand() % n + 1, y = rand() % m + 1;
    while (b[x][y]) {
      x = rand() % n + 1, y = rand() % m + 1;
    }
    b[x][y] = 2;
  }

  void SpawnSuperFood() {
    int c = n * m, _b[101][101] = {};
    int x = rand() % (n - 1) + 1, y = rand() % (m - 1) + 1;
    while (c && (b[x][y] || b[x + 1][y] || b[x][y + 1] || b[x + 1][y + 1])) {
      c -= !_b[x][y], _b[x][y] = 1;
      x = rand() % (n - 1) + 1, y = rand() % (m - 1) + 1;
    }
    b[x][y] = b[x + 1][y] = b[x][y + 1] = b[x + 1][y + 1] = 3;
  }

  void EraseSuperFood() {
    t = k + rand() % 25 + 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (b[i][j] == 3) {
          b[i][j] = 0;
        }
      }
    }
  }

  bool Move() {
    int x = (l.back().first + kMove[d][0] + n - 1) % n + 1, y = (l.back().second + kMove[d][1] + m - 1) % m + 1;
    if (b[x][y] == 1 || b[x][y] == 4) {
      return 1;
    } else if (b[x][y] == 2) {
      s++;
      Push(x, y);
      SpawnFood();
    } else {
      if (b[x][y] == 3) {
        s += 11 - k + t;
        EraseSuperFood();
      }
      Push(x, y);
      Pop();
    }
    return 0;
  }

  void Prepare() {
    bool flag;
    system("cls");
    func.SetColor(11, 0);
    cout << "Press WASD To Change Your Direction.\n按下 WASD 以改变移动方向.\nPress F To Change Your Speed.\n按下 F 以切换移动速度.\n";
    func.Pause();
    system("cls");
    n = 20, m = 52, s = 0, d = 0, k = 0, speed = 1;
    fill(&b[0][0], &b[101][0], 0), fill(&_b[0][0], &_b[101][0], -1);
    for (int i = 1; i <= 2; i++) {
      for (int j = 1; j <= 16; j++) {
        b[i + 3][j + 6] = b[i + 3][j + 30] = b[i + 15][j + 6] = b[i + 15][j + 30] = 1;
      }
    }
    for (int i = 1; i <= 3; i++) {
      for (int j = 1; j <= 6; j++) {
        b[i + 5][j + 6] = b[i + 5][j + 40] = b[i + 12][j + 6] = b[i + 12][j + 40] = 1;
      }
    }
    for (int i = 1; i <= 4; i++) {
      for (int j = 1; j <= 8; j++) {
        b[i + 8][j + 22] = 1;
      }
    }
    while (!l.empty()) {
      l.pop();
    }
    Push(2, 13), Push(2, 14), Push(2, 15), Push(2, 16);
    SpawnFood(), t = k + rand() % 25 + 1;
    func.SetColor(11, 0);
    for (int i = 1; i <= n; i++) {
      func.Goto(i + 1, 1);
      cout << '|';
      func.Goto(i + 1, m + 2);
      cout << '|';
    }
    for (int i = 1; i <= m; i++) {
      func.Goto(1, i + 1);
      cout << '-';
      func.Goto(n + 2, i + 1);
      cout << '-';
    }
  }

  void Playing() {
    for (k = 0;; k++) {
      Sleep(100 + speed * 100);
      Print(), D();
      if (Move()) {
        while (kbhit()) {
          getch();
        }
        return;
      } else if (k == t) {
        SpawnSuperFood();
      } else if (k == t + 25) {
        EraseSuperFood();
      }
    }
  }

  void Ending() {
    system("cls");
    cout << "Game Over!\nYour Score is " << s << ".\n";
    func.Pause();
    system("cls");
    cout << "LunarPursuer Gameset [Version 10.0.22621.608]\n(c) Seek Lunar Corporation. All Rights Reserved.\nType \"help\" To Check Out Command List.\n输入 \"help\" 以查看命令列表.\n";
  }

 public:
  void Main() {
    Prepare();
    Playing();
    Ending();
  }
} snake;
class MINESWEEPER {
 private:
  const int kMove[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
  struct A {
    int x, y;
  };
  int n, x, y, k, _k, a[101][101];
  bool b[101][101], _b[101][101];
  queue<A> q;

  void Bfs(int _x, int _y) {
    for (q.push({_x, _y}); !q.empty(); q.pop()) {
      A c = q.front();
      if (c.x < 1 || c.y < 1 || c.x > x || c.y > y || b[c.x][c.y] || _b[c.x][c.y]) {
        continue;
      }
      b[c.x][c.y] = 1, k--;
      if (!a[c.x][c.y]) {
        for (int i = 0; i <= 7; i++) {
          q.push({c.x + kMove[i][0], c.y + kMove[i][1]});
        }
      }
    }
  }

  bool Print(bool c) {
    bool flag = 0;
    func.SetColor(11, 0);
    for (int i = 0; i <= y; i++) {
      cout << setw(3) << i;
    }
    for (int i = 1; i <= x; i++) {
      cout << "\n";
      func.SetColor(11, 0);
      cout << setw(3) << i;
      for (int j = 1; j <= y; j++) {
        if (_b[i][j] && !c) {
          func.SetColor(10, 0);
          cout << setw(3) << "*";
        } else if (b[i][j]) {
          if (a[i][j] == 9) {
            func.SetColor(12, 0);
            cout << setw(3) << "#";
            flag = 1;
          } else {
            func.SetColor(a[i][j] ? a[i][j] : 9, 0);
            cout << setw(3) << a[i][j];
          }
        } else {
          func.SetColor(11, 0);
          cout << setw(3) << ".";
        }
      }
    }
    cout << "\n\n";
    func.SetColor(11, 0);
    return flag;
  }

  void Prepare() {
    system("cls");
    func.SetColor(11, 0);
    cout << "Spawning The Map...\n";
    Sleep(500);
    for (int i = 1, _x, _y; i <= n;) {
      _x = rand() % x + 1, _y = rand() % y + 1;
      if (a[_x][_y] != 9) {
        a[_x][_y] = 9;
        i++;
        for (int j = 0; j <= 7; j++) {
          if (a[_x + kMove[j][0]][_y + kMove[j][1]] != 9) {
            a[_x + kMove[j][0]][_y + kMove[j][1]]++;
          }
        }
      }
    }
    cout << "Done!\n";
    func.Pause();
    system("cls");
  }

  void Playing() {
    int _x, _y, c;
    k = x * y, _k = n;
    bool flag = 0;
    while (k > _k && _k > 0) {
      if (Print(0)) {
        cout << "You Have Found Some Mines!\nGame Over!\n";
        return;
      }
      cout << "Please Input Command.\n0/1 For Mine/Mark One Place, x And y For The Coordinate Of The Place.\nFor Example: 0 1 1.\n             挖开坐标为(1, 1)的地方.\nFor Example: 1 1 1.\n             标记坐标为(1, 1)的地方.\n";
      cin >> c >> _x >> _y;
      if (!c) {
        Bfs(_x, _y);
      } else if (c == 1 && !b[_x][_y]) {
        _b[_x][_y] ^= 1, k -= _b[_x][_y] ? 1 : -1, _k -= _b[_x][_y] ? 1 : -1;
      } else if (c == 2) {
        int d = 0;
        for (int i = 0; i <= 7; i++) {
          if (_x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
            d += _b[_x + kMove[i][0]][_y + kMove[i][1]];
          }
        }
        for (int i = 0; i <= 7; i++) {
          if (d == a[_x][_y] && b[_x][_y] && _x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
            Bfs(_x + kMove[i][0], _y + kMove[i][1]);
          }
        }
      } else if (c == 3) {
        int d = 0;
        for (int i = 0; i <= 7; i++) {
          if (_x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
            d += !b[_x + kMove[i][0]][_y + kMove[i][1]];
          }
        }
        for (int i = 0; i <= 7; i++) {
          if (d == a[_x][_y] && b[_x][_y] && !b[_x + kMove[i][0]][_y + kMove[i][1]] && _x + kMove[i][0] && _y + kMove[i][1] && _x + kMove[i][0] <= x && _y + kMove[i][1] <= y) {
            _b[_x + kMove[i][0]][_y + kMove[i][1]] = 1, k--;
          }
        }
      }
      system("cls");
    }
    if (Print(0)) {
      cout << "You Have Found Some Mines!\nGame Over!\n";
      return;
    }
    func.SetColor(11, 0);
    for (int i = 1; i <= x; i++) {
      for (int j = 1; j <= y; j++) {
        if (!_b[i][j] && a[i][j] == 9 || _b[i][j] && a[i][j] != 9) {
          cout << "You Have Marked Some Wrong Mines!\nGame Over!\n";
          return;
        }
      }
    }
    cout << "You Have Marked Each Mine!\nYou Won The Game!\n";
  }

  void Ending() {
    bool flag;
    cout << "Want To Watch The Map?\nYes = 1, No = 0\n";
    cin >> flag;
    if (flag) {
      system("cls");
      fill(&b[0][0], &b[100][100] + 1, 1);
      Print(1);
      func.Pause();
    }
    getchar();
    system("cls");
    cout << "LunarPursuer Gameset [Version 10.0.22621.608]\n(c) Seek Lunar Corporation. All Rights Reserved.\nType \"help\" To Check Out Command List.\n输入 \"help\" 以查看命令列表.\n";
    fill(&a[0][0], &a[100][100] + 1, 0);
    fill(&b[0][0], &b[100][100] + 1, 0);
    fill(&_b[0][0], &_b[100][100] + 1, 0);
  }

 public:
  void Main() {
    PII p;
    p = func.Read(p.second);
    if ((x = p.first) == -1) {
      cout << "Incorrect Command!\nType \"help minesweeper\" To Check Out Regular.\n输入 \"help minesweeper\" 以查看语法.\n";
      return;
    }
    p = func.Read(p.second);
    if ((y = p.first) == -1) {
      cout << "Incorrect Command!\nType \"help minesweeper\" To Check Out Regular.\n输入 \"help minesweeper\" 以查看语法.\n";
      return;
    }
    p = func.Read(p.second);
    if ((n = p.first) == -1) {
      cout << "Incorrect Command!\nType \"help minesweeper\" To Check Out Regular.\n输入 \"help minesweeper\" 以查看语法.\n";
      return;
    }
    Prepare();
    Playing();
    Ending();
  }
} minesweeper;

int main() {
  func.HideMouse();
  srand(time(0));
  system("title Gameset");
  system("cls");
  cin.tie(0), cout.tie(0);
  path = string(getcwd(NULL, 0));
  func.SetColor(11, 0);
  cout << "LunarPursuer Gameset [Version 10.0.22621.608]\n(c) Seek Lunar Corporation. All Rights Reserved.\nType \"help\" To Check Out Command List.\n输入 \"help\" 以查看命令列表.\n";
  while (1) {
    cout << "\n" + path + "> ";
    opt = "";
    getline(cin, opt);
    if (opt != "") {
      cout << '\n';
      if (func.Chick("help")) {
        help.Main();
      } else if (func.Chick("exit")) {
        break;
      } else if (func.Chick("snake")) {
        snake.Main();
      } else if (func.Chick("minesweeper")) {
        minesweeper.Main();
      } else {
        cout << "Incorrect Command!\nType \"help\" To Check Out Command List.\n输入 \"help\" 以查看命令列表.\n";
      }
    }
  }
  func.Pause();
  system("cls");
  return 0;
}
