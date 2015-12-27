#include <iostream>
#include <vector>

const int WIN_HEIGHT = 50;//25*2
const int WIN_WIDTH  = 80;

using std::cout;
using std::endl;

using pixel = bool;
using screen = std::bitset<WIN_HEIGHT*WIN_WIDTH>;
using rect = struct {
  int x,y;
  int w,h;
};
using obj_list = std::vector<rect>;

void toscreen(const screen s, const int x, const int y) {
  pixel top = s[y*WIN_WIDTH + x];
  pixel bot = s[(y+1)*WIN_WIDTH + x];
  if(top){
    if(bot){
      cout << "█";
    }else{
      cout << "▀";
    }
  }else{
    if(bot){
      cout << "▄";
    }else{
      cout << " ";
    }
  }
}

void drawScreen(const screen &s) {
  for(int y=0;y<WIN_HEIGHT;y+=2){
    for(int x=0;x<WIN_WIDTH;x++){
      toscreen(s,x,y);
    }
    cout << endl;
  }
}
void clearScreen(){
  cout << ("\033[" + std::to_string(WIN_HEIGHT/2) + "A");
}

inline bool inCircle(const int x, const int y,
    const int cx, const int cy, const int cr){
  int dx = std::abs(x-cx);
  if (dx>cr) return false;
  int dy = std::abs(y-cy);
  if (dy>cr) return false;
  if (dx+dy <= cr) return true;
  int square_dist = (cx - x)*(cx - x) + (cy - y)*(cy - y);
  return square_dist <= cr*cr;
}

void drawCircle(screen &s, const int cx, const int cy, const int cr) {
  for(int y=0;y<WIN_HEIGHT;y++){
    for(int x=0;x<WIN_WIDTH;x++){
      s[y*WIN_WIDTH + x] = s[y*WIN_WIDTH + x] | inCircle(x,y,cx,cy,cr);
    }
  }
}
void drawRect(screen &s, const rect r) {
  for(int y=r.y;y<r.y+r.h;y++){
    for(int x=r.x;x<r.x+r.w;x++){
      s[y*WIN_WIDTH + x] = true;
    }
  }
}

int main(int argc, char const *argv[]) {
  screen s;
  obj_list o = {{0,0,1,WIN_HEIGHT},{0,0,WIN_WIDTH,1},{WIN_WIDTH-1,0,1,WIN_HEIGHT},{0,WIN_HEIGHT-1,WIN_WIDTH,1}};
  for(const auto &ob : o) drawRect(s,ob);
  drawScreen(s);
  return 0;
}
