#ifndef CUBE_H
#define CUBE_H

// autor : Alexis

class Cube          // Cube class
{
public:
    // Constructor
    Cube();

    // Destructor
    virtual ~Cube();

    // Display method
    void drawCube(int x, int z,int color) const; // IN : position and color

};

#endif // CUBE_H
