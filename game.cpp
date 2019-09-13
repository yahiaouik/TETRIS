#include "game.h"
#include <vector>
#include <QTimer>
#include <iostream>
#include <QWidget>
using namespace std;

Game::Game(QTimer* timer_fall)
{
    srand (time(NULL));
    for(int i=0;i<21;i++){
        for(int j=0;j<12;j++){
            if(i==20 ||j==11 || j==0){
               grille[i][j].valeur=1;
               grille[i][j].couleur=0;
            }else{
              grille[i][j].valeur=0;
              grille[i][j].couleur=0;
            }
        }
    }
    timerReference=timer_fall;
    piece_touch=false;
    this->new_piece();


}

void Game::create_line(){

    grille[0][3].valeur=2;
    grille[0][4].valeur=3;
    grille[0][5].valeur=2;
    grille[0][6].valeur=2;

    grille[0][3].couleur=1;
    grille[0][4].couleur=1;
    grille[0][5].couleur=1;
    grille[0][6].couleur=1;

}

void Game::create_cube(){
    grille[0][5].valeur=2;
    grille[0][6].valeur=2;
    grille[1][5].valeur=2;
    grille[1][6].valeur=2;

    grille[0][5].couleur=2;
    grille[0][6].couleur=2;
    grille[1][5].couleur=2;
    grille[1][6].couleur=2;
}

void Game::create_z(){
    grille[0][5].valeur=2;
    grille[0][6].valeur=2;
    grille[1][6].valeur=2;
    grille[1][7].valeur=3;

    grille[0][5].couleur=3;
    grille[0][6].couleur=3;
    grille[1][6].couleur=3;
    grille[1][7].couleur=3;
}

void Game::create_s(){
    grille[0][6].valeur=2;
    grille[0][7].valeur=2;
    grille[1][5].valeur=3;
    grille[1][6].valeur=2;

    grille[0][6].couleur=4;
    grille[0][7].couleur=4;
    grille[1][5].couleur=4;
    grille[1][6].couleur=4;
}

void Game::create_t(){
    grille[1][5].valeur=3;
    grille[1][6].valeur=2;
    grille[1][7].valeur=2;
    grille[0][6].valeur=2;

    grille[1][5].couleur=5;
    grille[1][6].couleur=5;
    grille[1][7].couleur=5;
    grille[0][6].couleur=5;
}

void Game::create_l(){
    grille[1][5].valeur=2;
    grille[1][6].valeur=3;
    grille[1][7].valeur=2;
    grille[0][7].valeur=2;

    grille[1][5].couleur=6;
    grille[1][6].couleur=6;
    grille[1][7].couleur=6;
    grille[0][7].couleur=6;
}

void Game::create_j(){
    grille[1][5].valeur=2;
    grille[1][6].valeur=3;
    grille[1][7].valeur=2;
    grille[0][5].valeur=2;

    grille[1][5].couleur=7;
    grille[1][6].couleur=7;
    grille[1][7].couleur=7;
    grille[0][5].couleur=7;
}

void Game::new_piece(){

int type_piece=rand()%7;
    switch (type_piece) {
        case 0:
        create_z();
        break;
    case 1:
         create_t();
        break;
    case 2:
        create_j();
        break;
    case 3:
        create_l();
        break;
    case 4:
        create_s();
        break;
    case 5:
        create_cube();
        break;
    case 6:
        create_line();
        break;

}
     piece_touch=false;
}

void Game::turn_piece_right(){

    able_to_turn_right=true;


    for(int i=20;i>=0;i--){
        for(int j=11;j>=0;j--){
            if((grille[i][j].valeur==2 || grille[i][j].valeur==3) && (grille[i][j+1].valeur==1)){
            able_to_turn_right=false;
            }
        }
    }

    for(int i=20;i>=0;i--){
        for(int j=11;j>=0;j--){
            if((grille[i][j].valeur==2 || grille[i][j].valeur==3) && (able_to_turn_right==true)){
                    grille[i][j+1]=grille[i][j];
                    grille[i][j].valeur=0;
                    grille[i][j].couleur=0;
            }
        }
    }
}

void Game::turn_piece_left(){

   able_to_turn_left=true;

    for(int i=20;i>=0;i--){
        for(int j=0;j<12;j++){
            if((grille[i][j].valeur==2 || grille[i][j].valeur==3) && (grille[i][j-1].valeur==1)){
                    able_to_turn_left=false;
            }
        }
    }

    for(int i=20;i>=0;i--){
        for(int j=0;j<12;j++){
            if((grille[i][j].valeur==2 || grille[i][j].valeur==3) && (able_to_turn_left==true)){
                    grille[i][j-1]=grille[i][j];
                    grille[i][j].valeur=0;
                    grille[i][j].couleur=0;
            }
        }
    }
}

void Game::calcul_points(int lines){

    int level=calcul_level();
    if (level!=_level) {
        timerReference->stop();
        timerReference->start(setSpeed(level));
        _level=level;
    }
    switch (lines){
    case 0:
        break;
    case 1:
        points=points+(40*(level+1));
        break;
    case 2:
        points=points+(100*(level+1));
        break;
    case 3:
        points=points+(300*(level+1));
        break;
    default:
        points=points+(1200*(level+1));
        break;
    }
}

void Game::rotate_piece(){
    int x=0,y=0;
    int newx=0,newy=0;
    int relativ_x,relativ_y;
    bool can_rot=true;
    for(int i=0;i<20;i++){
        for(int j=1;j<11;j++){
            if(grille[i][j].valeur==3){
               x=i;
               y=j;
            }
        }

    }

    for(int i=x-2;i<x+3;i++){
        for(int j=y-2;j<y+3;j++){
            if(grille [i][j].valeur==1 )
                can_rot=false;
        }
    }

    if(can_rot){
    for(int i=x-2;i<x+3;i++){
       for(int j=y-2;j<y+3;j++)
        if(grille[i][j].valeur==2){
            relativ_x=i-x;
            relativ_y=j-y;
            newx=((0*relativ_x)+(1*relativ_y))+x;
            newy=((-1*relativ_x)+(0*relativ_y))+y;
            if(grille[newx][newy].valeur==0){
               grille[newx][newy].valeur=4;
               grille[newx][newy].couleur= grille[i][j].couleur;
               grille[i][j].valeur=0;
               grille[i][j].couleur=0;
            }

            }
        }


    for(int i=x-2;i<x+3;i++){
        for(int j=y-2;j<y+3;j++){
            if(grille[i][j].valeur==4){
                grille[i][j].valeur=2;
                //grille[i][j].couleur=grille[x][y].couleur;
            }
        }
    }
  }
}

int Game::delete_line(){
    int counter= 0;
    int number_line_del;
    for(int i=0;i<20;i++){
        for(int j=1;j<11;j++){
            if(grille[i][j].valeur==grille[i][j+1].valeur && grille[i][j].valeur==1 && full_line==false){
                counter++;
            }
            if(counter>=10 && full_line==false){
               j=1;
               full_line=true;
               number_line.push_back(i);
            }
            if(full_line==true){
              grille[i][j].valeur=0;
              grille[i][j].couleur=0;

            }
        }
        counter=0;
        full_line=false;
    }

    number_line_del=number_line.size();
    deleted_lines=deleted_lines+number_line.size();

            while (number_line.size()>0){
            for(int i=number_line.front();i>0;i--){
                for(int j=11;j>=1;j--){
                    grille[i][j]=grille[i-1][j];
                }
            }
            number_line.erase(number_line.begin());
        }

            return number_line_del;
}

void Game::piece_fall(){
    if(piece_touch==true){
        this->calcul_points(delete_line());
        this->new_piece();
    }

    for(int i=20;i>=0;i--){
        for(int j=11;j>=0;j--){
            if((grille[i][j].valeur==2|| grille[i][j].valeur==3) && (grille[i+1][j].valeur==1)){
            piece_touch=true;
            }
        }
    }

    for(int i=20;i>=0;i--){
        for(int j=11;j>=0;j--){
            if(grille[i][j].valeur==2 || grille[i][j].valeur==3){
                if(piece_touch==true){
                   grille[i][j].valeur=1;
                }else {
                    grille[i+1][j]=grille[i][j];
                    grille[i][j].valeur=0;
                    grille[i][j].couleur=0;
                }
            }
    }
   }

}

bool Game::end_game(){
    for(int j=1;j<11;j++){
        if(grille[0][j].valeur==1){
            timerReference->stop();
            return true;
        }
    }
    return false;
}

int Game::setSpeed(int level) {
    switch (level) {
     case 1 :
        return 800;
    case 2 :
        return 600;
    case 3 :
        return 400;
    case 4 :
        return 300;
    default:
        return 100;
    }
}
