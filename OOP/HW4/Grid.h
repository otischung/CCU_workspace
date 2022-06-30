#pragma once
#include <vector>

class Grid {
   private:
    bool show_path;
    bool wall;
    int m_row, m_col, m_dir;
    int e_row, e_col;
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<char>> grid_show;
    static const int EMPTY = 0;  // render as .
    static const int PATH = 1;   // render as ' ' if TogglePath() is on, else, render as .
    static const int ITEM = 2;   // render as 0
    static const int BLOCK = 3;  // render as #
    static const int MAXSIZE = 40;  // the max grid size

    // check grid size below MAXSIZE
    bool check_and_set_size(int &r, int &c);
    // check vector creation/recreation
    bool check_vector(int r, int c);
    // initialize the grid to all .
    bool set_grid(int r, int c);
    // generate random exit
    void set_exit();
    // generate specific exit
    void set_exit(int er, int ec);
    // set the blocks around edge
    void set_edge_block();
    // clear the blocks around edge
    void clear_edge_block();
    // initialize the mover, return false if the mover is out of range.
    bool set_mover(int r, int c, int dir);
    // sync grid_show from the latest version of grid.
    void sync_grid(); 

   public:
    // public static class constants, for direction indicators.
    static const int NORTH = 0;
    static const int WEST = 1;
    static const int SOUTH = 2;
    static const int EAST = 3;

    // build 1 x 1 grid with mover in only square, facing east.
    Grid();
    /**********************************************************
     * build grid with r rows, c cols,
     * blocks around edge with random exit
     * and random mover position and direction
     **********************************************************/
    Grid(int r, int c);
    /**********************************************************
     * build empty grid with r rows, c cols, and
     * mover at row mr, col mc, and facing direction d
     **********************************************************/
    Grid(int r, int c, int mr, int mc, int d);
    /**********************************************************
     * build empty grid with r rows, c cols, and
     * mover at row mr, col mc, and facing direction d, and
     * exit at row er, col ec
     **********************************************************/
    Grid(int r, int c, int mr, int mc, int d, int er, int ec);

    // move forward s spaces, if possible.
    bool Move(int s);
    // toggle whether or not moved path is shown.
    void TogglePath();
    // turn the mover to the left
    void TurnLeft();
    // put down an item at the mover's position
    void PutDown();
    // put down an item at (r, c), if possible
    bool PutDown(int r, int c);
    // pick up item at current position
    bool PickUp();
    // put a block at (r, c), if possible
    bool PlaceBlock(int r, int c);
    // remove a block at (r, c), if there is a block
    bool RemoveBlock(int r, int c);
    // grow the grid by gr rows, gc columns, i.e., set row to current row + gr.
    bool Grow(int gr, int gc);

    // display the grid on screen
    void Display();

    /* Accessors */
    // check to see if space in front of mover is clear
    bool FrontIsClear() const;
    // check to see if space to right of mover is clear
    bool RightIsClear() const;
    // return row of the mover.
    int GetRow() const;
    // return cloumn of the mover.
    int GetCol() const;
    // return number of rows in the grid.
    int GetNumRows() const;
    // return number of columns int the grid.
    int GetNumCols() const;
};