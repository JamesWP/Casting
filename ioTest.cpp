#include "io.hpp"

using namespace std;

int main()
{
  startIo();

  if(true){//hasKey()){
    auto k = getKey();

    switch(k.type){
      case Char:
        cout << k.ch << endl;
      case Arrow:
        cout << k.arrowKey << endl;
      case Unknown:
        cout << "Unknown" << endl;
    }
  }

  endIo();
}
