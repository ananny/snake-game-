#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include<iostream>
using namespace std;
bool game;
const int height=50;
const int width=30;
int x,y,score;
int fruitx,fruity;
enum eDirecton {STOP=0, LEFT , RIGHT , UP , DOWN };
eDirecton dir;


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}


void setup(){
game=false;
dir=STOP;
x=width/2;
y=height/2;
fruitx=rand()%width;
fruity=rand()%height;
score=0;
}//setup()






void input(){
if(kbhit()){
switch(getchar())
{
        case 'w':
        dir = UP;
        break;
        
        case's':
        dir=DOWN;
        break;
        case'a':
        dir=LEFT;
        break;
        case'd':
        dir=RIGHT;
        
        case 'e':
        game=true;
        break;

}//switch



}//if

}//void Inut

void draw(){

system("clear");
for(int i=0;i<=width+1;i++){
cout<<"-";

}//for(to draw  uppar width)
cout<<endl;
for(int i=0;i<height;i++){ 
        for(int j=0;j<=width;j++){
                if(j==0){
                cout<<"|";
                }
                
                // for snake pos
                if(i==y && j==x){
                cout<<"*";
                }
                //for fruit pos
                else if(i==fruity && j==fruitx){
                cout<<"$";
                }
               else{
               cout<<" ";
               }               
                
                if(j==width-1){
                cout<<"|";
                }
                
         } 
         cout<<endl;
         
}



for(int i=0;i<width+2;i++){
cout<<"-";
}//to draw down width
cout<<endl;

cout<<"SCORE:-"<<score<<endl;

}//void draw()

void logic(){

switch(dir)
{
case UP:
y--;
break;

case DOWN:
y++;
break;

case LEFT:
x--;
break;

case RIGHT:
x++;
break;

default:
break;

}//switch

if(x>=width|| x<=0 && y>=height||y<=0){
game=true;
}
if(x == fruitx && y == fruity){

score=score+10;
fruitx=rand() % width;
fruity=rand() % height;
}


}//void logic



int main()
{



setup();
while(!game){
sleep(1);
draw();
logic();
input();




}//while


}//main()
