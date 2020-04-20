//
//  main.cpp
//  Road game
//
//  Created by Mani Kireeti on 10/04/20.
//  Copyright © 2020 Mani Kireeti. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;
int A[17][31];

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

void display(int MX,int MY){
    cout<<"--------------------------------"<<endl;
    
    if(MX==0){
        int i=1;
        cout<<"|";
        for(;i<MY;i++) cout<<" ";
        cout<<"O";
        i++;
        for(;i<=30;i++) cout<<" ";
        cout<<"|";
        cout<<endl;
    }
    else{
        int i=1;
        cout<<"|";
        for(;i<31;i++) cout<<" ";
        cout<<"|"<<endl;
    }
    cout<<"--------------------------------"<<endl;
    for(int i=1;i<16;i++){
        cout<<"|";
        for(int j=1;j<=30;j++){
            if(i==MX && j==MY) cout<<"O";
            if(A[i][j]==0) cout<<" ";
            if(A[i][j]==1) cout<<"*";
        }
        cout<<"|"<<endl;
    }
    cout<<"--------------------------------"<<endl;
    for(int i=1;i<31;i++){
        if(A[16][i]==0) cout<<" ";
        if(A[16][i]==1) cout<<"O";
    }
    cout<<endl;
    cout<<"--------------------------------"<<endl;
}


void game(){
    system("clear");
    for(int i=0;i<17;i++){
        for(int j=1;j<=30;j++){
            A[i][j]=0;
        }
    }
    int MX=0,MY=15;
    cout<<"Select the difficulty level: 1 or 2 or 3"<<endl;
    int a;
    cin>>a;
    if(a==1){
        for(int i=1;i<=15;i++){
            int num=rand()%(2)+1;
            while(num>0){
                int x=rand()%30+1;
                A[i][x]=1;
                num--;
            }
        }
    }
    if(a==2){
        for(int i=1;i<=15;i++){
            int num=rand()%(7)+4;
            while(num>0){
                int x=rand()%30+1;
                A[i][x]=1;
                num--;
            }
        }
    }
    if(a==3){
        for(int i=1;i<=15;i++){
            int num=rand()%(6)+10;
            while(num>0){
                int x=rand()%30+1;
                A[i][x]=1;
                num--;
            }
        }
    }
    while(true){
        system("clear");
        if(MX==16){
            cout<<"CONGRATULATIONS YOU WON THE GAME"<<endl;
            cout<<"want to play another press p or q to quit: ";
            char i;
            cin >> i;
            if(i=='p' || i=='P') game();
            else return;
        }
        if(A[MX][MY]==1){
            cout<<"SORRY YOU LOST THE GAME"<<endl;
            cout<<"want to play another press p or q to quit: ";
            char i;
            cin >> i;
            if(i=='p' || i=='P') game();
            else {return; }
        }
        if(kbhit()){
            char a=getchar();
            if(a=='w'){
                if(MX!=0) MX--;
            }
            if(a=='s'){
                MX++;
            }
            if(a=='a'){
                MY--;
            }
            if(a=='d'){
                MY++;
            }
        }
        
        for(int i=1;i<16;i++){
            if(i%2==0){
                int temp=A[i][29];
                for(int j=29;j>1;j--){
                    A[i][j]=A[i][j-1];
                }
                A[i][1]=A[i][30];
                A[i][30]=temp;
            }
            if(i%2==1){
                int temp=A[i][2];
                for(int j=2;j<30;j++){
                    A[i][j]=A[i][j+1];
                }
                A[i][30]=A[i][1];
                A[i][1]=temp;
            }
        }
        
        display(MX,MY);
        usleep(1000000/8);
    }
}

int main() {
    system("clear");
    srand( static_cast<unsigned int>(time(nullptr)));
    cout<<"WELCOME TO THE ROAD GAME"<<endl;
    cout<<"Press P to play or Q to quit: ";
    char a;
    cin>>a;
    if(a=='P' || a=='p') game();
    return 0;
    
}
