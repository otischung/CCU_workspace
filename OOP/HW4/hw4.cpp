#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Grid.h"

int main() {
    srand(time(NULL));
    // set up the initial grid
    Grid g(9, 15, 2, 13, Grid::WEST);
    g.PutDown(2, 1);
    std::cout << "/*********** A ***********/\n";
    for (int i = 0; i < 7; ++i) {
        g.PlaceBlock(i, 11);
        g.PlaceBlock(i, 7);
        g.PlaceBlock(i, 3);
        g.PlaceBlock(i + 2, 5);
        g.PlaceBlock(i + 2, 9);
    }
    g.Display();

    // now start moving
    std::cout << "/*********** B ***********/\n";
    g.TurnLeft();
    g.Move(5);
    g.Display();

    std::cout << "/*********** C ***********/\n";
    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(1);
    g.Display();

    std::cout << "*********** D ***********/\n";
    g.Move(2);
    g.Display();

    std::cout << "/*********** E ***********/\n";
    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(6);
    g.Display();

    std::cout << "/*********** F ***********/\n";
    g.PutDown();
    g.Display();

    std::cout << "/*********** G ***********/\n";
    g.TurnLeft();
    g.Move(2);
    g.Display();

    std::cout << "/*********** H ***********/\n";
    g.TurnLeft();
    g.Move(6);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();

    std::cout << "/*********** I ***********/\n";
    g.Move(2);
    g.Display();

    std::cout << "/*********** J ***********/\n";
    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(6);
    g.Display();

    std::cout << "/*********** K ***********/\n";
    g.PutDown();
    g.Display();

    std::cout << "/*********** L ***********/\n";
    g.TurnLeft();
    g.Move(2);
    g.Display();

    std::cout << "/*********** M ***********/\n";
    g.TurnLeft();
    g.Move(6);
    g.Display();

    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();

    std::cout << "/*********** N ***********/\n";
    g.Move(3);
    g.Display();

    std::cout << "/*********** O ***********/\n";
    g.TurnLeft();
    g.TurnLeft();
    g.TurnLeft();
    g.Move(5);
    g.Display();

    std::cout << "/*********** P ***********/\n";
    g.PickUp();
    g.Display();

    std::cout << "/*********** Q ***********/\n";
    g.TurnLeft();
    g.Move(1);
    g.Display();

    std::cout << "/*********** R ***********/\n";
    g.TogglePath();
    g.Display();

    std::cout << "/*********** S ***********/\n";
    g.TogglePath();
    g.Display();

    return 0;
}
