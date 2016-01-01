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
        break;
      case Arrow:
        cout << ArrowKeyName[k.arrowKey] << endl;
        break;
      case Unknown:
        cout << "Unknown" << endl;
        break;
    }
  }

  endIo();
}
