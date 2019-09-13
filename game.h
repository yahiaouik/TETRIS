#ifndef GAME_H
#define GAME_H
#include <QWidget>
#include <QMainWindow>
#include <vector>
using namespace std;

//autor : Kenza

class Game                              // Game class (tetris logic part)
{

public:
    struct cube_logique{                // Logic struct of a cell
        int valeur;                     // Cell value
        int couleur;                    // Cell color
    };

private:
    cube_logique grille[21][12];        // Tetris logic grid
    bool full_line=false;               //
    bool piece_touch;                   // Does the piece touch the ground ?
    bool able_to_turn_right=true;       // Can move to the right ?
    bool able_to_turn_left=true;        // Can move to the left ?
    vector<int> number_line;            // Numbers of line to delete
    int deleted_lines=0;                // Number of deleted lines
    int points=0;                       // Points of the player
    int _level=1;                       // Level
    QTimer* timerReference;             // Reference to the timer

public:
    Game(QTimer*);                      // Constructor IN : QTimer reference
    void piece_fall();                  // Make piece fall
    void turn_piece_right();            // Move piece to the right
    void turn_piece_left();             // Move piece to the left
    void rotate_piece();                // Rotate piece
    void new_piece();                   // Create new piece and add it to the grid
    void create_line();                 // Create the line piece
    void create_cube();                 // Create the cube piece
    void create_z();                    // Create the z piece
    void create_j();                    // Create the j piece
    void create_s();                    // Create the s piece
    void create_l();                    // Create the l piece
    void create_t();                    // Create the t piece
    void calcul_points(int lines);      // Compute points

    int get_point(){return this->points;}                           // Get points       OUT : points
    int calcul_level(){return ((this->deleted_lines/2)+1);}         // Compute level    OUT : level
    int delete_line();                                              // Delete line      OUT : Number of lines deleted
    bool end_game();                                                // Test and apply the end of the game   OUT : bool if the game is end
    int setSpeed(int level);                                        // Set the game speed                   IN : level OUT : speed

    cube_logique (*get_grille())[12]{return this->grille;}          // Get the grid




};

#endif // GAME_H
