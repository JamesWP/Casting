
#ifndef IOH
#define IOH

#include <iostream>
#include <termios.h>

using ArrowKey = enum{Up,Down,Left,Right};
using KeyType = enum{Arrow,Char,Unknown};

using Key = struct {
  KeyType type;
  union{
    ArrowKey arrowKey;
    char ch;
  };
};

void startIo();
void endIo();
bool hasKey();
Key getKey();

#endif
