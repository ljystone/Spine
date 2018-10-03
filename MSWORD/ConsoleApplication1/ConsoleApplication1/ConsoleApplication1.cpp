// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"	
#include <iostream>
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
  string str="We think in generalities, but we live:123.";
                             // quoting Alfred N. Whitehead
  string str2, str3;
  size_t pos;

  str2 = str.substr (12,12); // "generalities"

  pos = str.find(":")+1;      // position of "live" in str
  str3 = str.substr (pos);   // get from "live" to the end

  cout << str2 << ' ' << str3 << endl;

  return 0;
}

