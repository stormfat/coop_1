#include <iostream>
#include <string>
using namespace std;

class Screen;//先声明类,可以让Dog中的成员函数使用

class Dog {
 public:
  int foo(Screen&);  //先声明函数,不能直接定义.因为这时Dog类看不见Screen的定义.无法访问其中的成员数据.定义要写在Screen类定义之后.
};

class Screen {
 public:
  typedef string::size_type index;
  Screen(int ht = 0, int wd = 0)
      : contents(ht * wd, ' '), cursor(0), height(ht), width(wd) {}
  friend int calcArea(Screen&);  //声明一个友元函数,可以让其使用类中私有成员.
  friend class
      Windows_Mgr;  //将一个类都作为友元,其类中的所有成员函数都可访问主类的数据成员.
  friend int Dog::foo(Screen&);//将一个类中的一个成员函数作为友元函数.

  //...
  int area() const { return height * width; }

 private:
  string contents;
  index cursor;
  int height, width;
};

//窗口管理类
class Windows_Mgr {
 public:
  void relocate(int r, int c, Screen& s) {
    s.height += r;
    s.width += c;
  }
};

int Dog::foo(Screen& screen) { return screen.height * screen.width; }

//非类成员函数,在成为友元前无法看见类的私有成员.
int calcArea(Screen& screen) { return screen.height * screen.width; }

int main() {
  Screen a;
  cout << "ok" << endl;
  return 0;
}