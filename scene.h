#ifndef SCENE_H
#define SCENE_H
#include "mainwindow.h"
#include "game.h"
#include "cube.h"
#include <QGLWidget>

class Scene : public QGLWidget  // Scene class (tetris graphic part)
{
    Q_OBJECT

private :
    Game* game;                                 // Game
    QTimer *timer_fall;                         // Timer for the falling piece
    boolean buffer=true;                        // OpenGL buffer
    Game::cube_logique (*pointeur)[12];         // Grid Reference
public:
    Scene (QWidget * parent=nullptr);                                                   // Constuctor autor: Kenza
    void initializeGL();                                                                // Initialize GL autor : Alexis
    void resizeGL(int width, int height);                                               // Resize GL IN : Size autor : Alexis
    void paintGL();                                                                     // Paint GL autor : Alexis
    void get_coord(Game::cube_logique (*pointeur)[12]);                                 // autor: Kenza
    void set_pointeur(Game::cube_logique (*pointeur)[12]) {this->pointeur=pointeur;}    //autor: Kenza
    Game* getGame(){return game;}                                                       // Get Game IN : game autor: Kenza
    void NewGame();                                                                     // Create new game autor: Kenza
    void runPieceFall(bool val);                                                        // Run the piece fall   IN : run or not ? autor: Kenza


public slots:
    void fall_piece(){this->game->piece_fall();}                                        // Make the piece fall autor : Alexis
    void move_piece(int data);                                                          // Call piece_fall of the game   IN : data (int value depending on the action) autor: Kenza

};

#endif // INTERFACE_H
