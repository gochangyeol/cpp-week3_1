#include "console.h"

using namespace std;
using namespace console;

#define BOARD_SIZE 20
#define MOVE_DELAY 15
#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"

int x = BOARD_SIZE/2;
int y = BOARD_SIZE/2;
int snake_x=-1;
int snake_y=0;
int frame=0;

void handleInput() {
  if (key(K_LEFT)) {
    snake_x=-1;
    snake_y=0;
  }
  if (key(K_RIGHT)) {
    snake_x=1;
    snake_y=0;
  }
  if (key(K_UP)) {
    snake_x=0;
    snake_y=-1;
  }
  if (key(K_DOWN)) {
    snake_x=0;
    snake_y=1;
  }
}

void restrictInScreen() {
  // x, y 위치를 화면의 최대 크기에서 벗어나지 않게 한다.
  if (x < 1)
    x = 1;
  if (x >= BOARD_SIZE)
    x = BOARD_SIZE - 1;
  if (y < 1)
    y = 1;
  if (y >= BOARD_SIZE)
    y = BOARD_SIZE - 1;
}

void drawSnake() {
  // x, y 위치에 *을 그린다.
  draw(x, y, "■");
}

void game() {

  // 콘솔 라이브러리를 초기화한다.
  init();

  draw(0,0,"┏");
    draw(BOARD_SIZE,0,"┓");
    draw(0,BOARD_SIZE,"┗");
    draw(BOARD_SIZE,BOARD_SIZE,"┛");
    for(int i=1;i<BOARD_SIZE;i++){
        draw(i,0,"━");
        draw(0,i,"┃");
        }
    for(int i=BOARD_SIZE-1;i>0;i--){
        draw(i,BOARD_SIZE,"━");
        draw(BOARD_SIZE,i,"┃");

    }

  while (true) {
    frame++;

    draw(x,y," ");

    restrictInScreen();
    handleInput();
    if(frame==MOVE_DELAY){
    frame=0;
    x+=snake_x;
    y+=snake_y;
   }
   if(x==BOARD_SIZE||y==BOARD_SIZE){
    break;
   }
   drawSnake();
    wait();
  }
}


int main(){
    game();
   
    return 0;
}