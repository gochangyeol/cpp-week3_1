#include "console.h"
#include <string.h>
#include<random>

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
int bodyLength=0;
int body_x[BOARD_SIZE*BOARD_SIZE];
int body_y[BOARD_SIZE*BOARD_SIZE];
int snakex_x[BOARD_SIZE*BOARD_SIZE];
int snakey_y[BOARD_SIZE*BOARD_SIZE];

string score="0";
string apple[BOARD_SIZE][BOARD_SIZE];
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<>distribution(1,BOARD_SIZE-1);
int rx=distribution(gen);
int ry=distribution(gen);

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
  apple[y][x]="■";
}
void drawapple(){

  while(true){

    if(apple[ry][rx]=="■"){
      rx=distribution(gen);
      ry=distribution(gen);
    }
    else{
      break;
    }
  }
  draw(rx,ry,"●");
  apple[ry][rx]="●";
}
void restart(){
    x = BOARD_SIZE / 2;
    y = BOARD_SIZE / 2;
    body_x[0] = 0;
    body_y[0] = 0;
    snake_x = -1;
    snake_y = 0;
    frame = 0;
    score = "0";
    bodyLength = 0; 

    for(int i = 0; i <= bodyLength; i++) {
        draw(body_x[i], body_y[i], " ");
    }

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            apple[i][j] = " ";
        }
    }

    clear();
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

    draw(6,21,"Score: ");
    draw(13,21,score);

    drawSnake();
    drawapple();
}

void movesnake(){

    for(int i = 0; i <= bodyLength; i++) {
        draw(body_x[i], body_y[i], " ");
    }

    draw(0,0,"┏");

    for(int i = bodyLength; i > 0; i--) {
        body_x[i] = body_x[i - 1];
        body_y[i] = body_y[i - 1];
    }

    body_x[0] = x;
    body_y[0] = y;

    for(int i = 0; i <= bodyLength; i++) {
        draw(body_x[i], body_y[i], "■");
    }
}
void addsnake(){
  int newx=body_x[bodyLength]+snakex_x[bodyLength]*-1;
  int newy=body_y[bodyLength]+snakey_y[bodyLength]*-1;
  draw(newx,newy,"■");
}

void game() {

  // 콘솔 라이브러리를 초기화한다.
  init();
  clear();
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
    draw(6,21,"Score: ");
    draw(13,21,score);
    
    drawSnake();
    drawapple();

  while (true) {
    
    frame++;

    draw(x,y," ");
    apple[y][x]=" ";
    
    
    restrictInScreen();
    handleInput();
    if(frame==MOVE_DELAY){
    frame=0;
    x+=snake_x;
    y+=snake_y;
    movesnake();
   }
   for(int i=1;i<=bodyLength;i++){
    if(y==body_y[i]&&x==body_x[i]){
      draw(6,10,"YOU LOSE!");
    draw(1,11,"Try again? (Enter)");
    draw(rx,ry," ");

    while (!key(K_ENTER) && !key(K_ESC)) {
           console::wait();
        }
        if (key(K_ENTER)) {
             restart();
             drawapple();
             
        } 
        else if (key(K_ESC)) {
            exit(0);
        }
    }
    }
   if(x==BOARD_SIZE||y==BOARD_SIZE||x==0||y==0||apple[y][x]=="■"||key(K_ESC)){
   
    draw(6,10,"YOU LOSE!");
    draw(1,11,"Try again? (Enter)");
    draw(rx,ry," ");

    while (!key(K_ENTER) && !key(K_ESC)) {
           console::wait();
        }
        if (key(K_ENTER)) {
             restart();
             drawapple();
             
        } 
        else if (key(K_ESC)) {
            break; 
        }
   }
   drawSnake();

   if(x==rx&&y==ry){
    drawapple();
    addsnake();
    bodyLength++;
   }
   
   console::wait();
  }
}


int main(){
  
    game();
    
   


    return 0;
}