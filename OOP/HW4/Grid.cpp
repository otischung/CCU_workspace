#include "Grid.h"

#include <iostream>

// check if the grid size is greater than 1 and less than MAXSIZE
bool Grid::check_and_set_size(int &r, int &c) {
    bool ret = true;

    if (r < 1) {
        std::cerr << "Error, row " << r << " is less than 1, default to 1.\n";
        r = 1;
        ret = false;
    } else if (r > MAXSIZE) {
        std::cerr << "Error, row " << r << " is out of max range " << MAXSIZE
                  << ", default it to " << MAXSIZE << ".\n";
        r = MAXSIZE;
        ret = false;
    }
    if (c < 1) {
        std::cerr << "Error, col " << c << " is less than 1, default to 1.\n";
        c = 1;
        ret = false;
    } else if (c > MAXSIZE) {
        std::cerr << "Error, col " << c << " is out of max range " << MAXSIZE
                  << ", default it to " << MAXSIZE << ".\n";
        c = MAXSIZE;
        ret = false;
    }
    return ret;
}

// check vector creation/recreation
bool Grid::check_vector(int r, int c) {
    if ((int)grid.size() == r && (int)grid[0].size() == c && \
        (int)grid_show.size() == r && (int)grid_show[0].size() == c) {
        return true;
    } else {
        std::cerr << "Error, vector creation failed.\n";
        return false;
    }
}

// initialize the grid to all .
bool Grid::set_grid(int r, int c) {
    bool ret;

    ret = check_and_set_size(r, c);                   // 1 <= r, c <= MAXSIZE
    grid.assign(r, std::vector<int>(c, (int)EMPTY));  // I don't know why I need to add (int) here to avoid CE.
    grid_show.assign(r, std::vector<char>(c, '.'));
    ret &= check_vector(r, c);
    return ret;
}

// generate random exit
void Grid::set_exit() {
    e_row = rand() % grid.size();
    if (e_row == 0 || e_row == (int)grid.size() - 1) {
        // since the exit cannot be in a corner spot
        e_col = rand() % (grid[0].size() - 2) + 1;
    } else {
        e_col = rand() % 2;
        if (e_col) {  // if col == 1
            e_col = grid[0].size() - 1;
        }
    }
}

// generate specific exit
void Grid::set_exit(int er, int ec) {
    if ((er == 0 || er == (int)grid.size() - 1) && (ec == 0 || ec == (int)grid[0].size() - 1)) {
        std::cerr << "Error, this exit is at the corner spot, generating random exit.\n";
        set_exit();
        return;
    }
    if (((er > 0 && er < (int)grid.size() - 1) && (ec == 0 || ec == (int)grid[0].size() - 1)) ||
        ((er == 0 || er == (int)grid.size() - 1) && (ec > 0 && ec < (int)grid[0].size() - 1))) {
        e_row = er;
        e_col = ec;
    } else {
        std::cerr << "Error, this location (" << er << ", " << ec << ") is invalid, generating random exit.\n";
        set_exit();
    }
}

// set the blocks around edge
void Grid::set_edge_block() {
    wall = true;
    for (int i = 0; i < (int)grid.size(); ++i) {
        if (e_row == i && e_col == 0) {
            continue;
        }
        if (grid[i][0] == EMPTY || grid[i][0] == PATH) {
            grid[i][0] = BLOCK;
        }
    }
    for (int i = 0; i < (int)grid.size(); ++i) {
        if (e_row == i && e_col == (int)grid[0].size() - 1) {
            continue;
        }
        if (grid[i][grid[0].size() - 1] == EMPTY || grid[i][grid[0].size() - 1] == PATH) {
            grid[i][grid[0].size() - 1] = BLOCK;
        }
    }
    for (int i = 1; i < (int)grid[0].size() - 1; ++i) {
        if (e_row == 0 && e_col == i) {
            continue;
        }
        if (grid[0][i] == EMPTY || grid[0][i] == PATH) {
            grid[0][i] = BLOCK;
        }
    }
    for (int i = 1; i < (int)grid[0].size() - 1; ++i) {
        if (e_row == (int)grid.size() - 1 && e_col == i) {
            continue;
        }
        if (grid[grid.size() - 1][i] == EMPTY || grid[grid.size() - 1][i] == PATH) {
            grid[grid.size() - 1][i] = BLOCK;
        }
    }
}

// clear the blocks around edge
void Grid::clear_edge_block() {
    for (int i = 0; i < (int)grid.size(); ++i) {
        if (grid[i][0] == BLOCK) {
            grid[i][0] = EMPTY;
        }
    }
    for (int i = 0; i < (int)grid.size(); ++i) {
        if (grid[i][grid[0].size() - 1] == BLOCK) {
            grid[i][grid[0].size() - 1] = EMPTY;
        }
    }
    for (int i = 1; i < (int)grid[0].size() - 1; ++i) {
        if (grid[0][i] == BLOCK) {
            grid[0][i] = EMPTY;
        }
    }
    for (int i = 1; i < (int)grid[0].size() - 1; ++i) {
        if (grid[grid.size() - 1][i] == BLOCK) {
            grid[grid.size() - 1][i] = EMPTY;
        }
    }
}

// initialize the mover, return false if the mover is out of range.
bool Grid::set_mover(int r, int c, int dir) {
    if (r >= (int)grid.size() || c >= (int)grid[0].size()) {
        std::cerr << "Error, row " << r << " or col " << c
                  << " is out of range.\n";
        std::cerr << "Max row: " << grid.size() - 1
                  << "; Max col: " << grid[0].size() << '\n';
        std::cerr << "Ignoring.\n";
        m_dir = dir % 4;
        return false;
    }
    m_row = r;
    m_col = c;
    m_dir = dir % 4;
    grid[m_row][m_col] = PATH;
    return true;
}

// sync grid_show from the latest version of grid.
void Grid::sync_grid() {
    for (int i = 0; i < (int)grid.size(); ++i) {
        for (int j = 0; j < (int)grid[i].size(); ++j) {
            switch (grid[i][j]) {
                case EMPTY:
                    grid_show[i][j] = '.';
                    break;
                case PATH:
                    if ((bool)show_path) {
                        grid_show[i][j] = ' ';
                    } else {
                        grid_show[i][j] = '.';
                    }
                    break;
                case ITEM:
                    grid_show[i][j] = '0';
                    break;
                case BLOCK:
                    grid_show[i][j] = '#';
                    break;
                default:
                    break;
            }
        }
    }
    if (grid[m_row][m_col] == ITEM) {
        grid_show[m_row][m_col] = '@';
    } else {
        switch (m_dir) {
            case Grid::NORTH:
                grid_show[m_row][m_col] = '^';
                break;
            case Grid::WEST:
                grid_show[m_row][m_col] = '<';
                break;
            case Grid::SOUTH:
                grid_show[m_row][m_col] = 'v';
                break;
            case Grid::EAST:
                grid_show[m_row][m_col] = '>';
                break;
            default:
                break;
        }
    }
}

// build 1 x 1 grid with mover in only square, facing east.
Grid::Grid() : show_path(true), wall(false) {
    std::cout << "1 parameter constructor is called." << std::endl;
    set_grid(1, 1);
    set_mover(0, 0, EAST);
}

/**********************************************************
 * build grid with r rows, c cols,
 * blocks around edge with random exit
 * and random mover position and direction
 **********************************************************/
Grid::Grid(int r, int c) : show_path(true), wall(true) {
    std::cout << "2 parameters constructor is called." << std::endl;
    if (r < 3) {
        std::cerr << "Warning: This constructor will always create grid no less than 3*3.\nDefault your row to 3.\n";
        r = 3;
    }
    if (c < 3) {
        std::cerr << "Warning: This constructor will always create grid no less than 3*3.\nDefault your col to 3.\n";
        c = 3;
    }
    set_grid(r, c);
    set_exit();
    set_edge_block();
    set_mover(rand() % (r - 2) + 1, rand() % (r - 2) + 1, rand() % 4);
}

/**********************************************************
 * build empty grid with r rows, c cols, and
 * mover at row mr, col mc, and facing direction d
 **********************************************************/
Grid::Grid(int r, int c, int mr, int mc, int d) : show_path(true), m_row(0), m_col(0) {
    std::cout << "5 parameters constructor is called." << std::endl;
    if (r == 1 || r == 2 || c == 1 || c == 2) {
        wall = false;
        set_grid(r, c);
        if (mr < 0) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to 0.\n";
            mr = 0;
        } else if (mr > r - 1) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to " << r - 1 << ".\n";
            mr = r - 1;
        }
        if (mc < 0) {
            std::cerr << "Warning: col of mover: " << mc << " is out of range, default col to 0.\n";
            mc = 0;
        } else if (mc > c - 1) {
            std::cerr << "Warning: row of mover: " << mc << " is out of range, default col to " << c - 1 << ".\n";
            mc = c - 1;
        }
        set_mover(mr, mc, d);
    } else {
        wall = true;
        set_grid(r, c);
        set_exit();
        set_edge_block();
        // the mover will never set at the exit (edge).
        if (mr < 1) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to 1.\n";
            mr = 1;
        } else if (mr > r - 2) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to " << r - 2 << ".\n";
            mr = r - 2;
        }
        if (mc < 1) {
            std::cerr << "Warning: col of mover: " << mc << " is out of range, default col to 1.\n";
            mc = 1;
        } else if (mc > c - 2) {
            std::cerr << "Warning: row of mover: " << mc << " is out of range, default col to " << c - 2 << ".\n";
            mc = c - 2;
        }
        set_mover(mr, mc, d);
    }
}

/**********************************************************
 * build empty grid with r rows, c cols, and
 * mover at row mr, col mc, and facing direction d, and
 * exit at row er, col ec
 **********************************************************/
Grid::Grid(int r, int c, int mr, int mc, int d, int er, int ec) : show_path(true), m_row(0), m_col(0) {
    std::cout << "7 parameters constructor is called." << std::endl;
    set_grid(r, c);
    set_exit(er, ec);
    set_edge_block();
    if (r == 1 || r == 2 || c == 1 || c == 2) {
        wall = false;
        set_grid(r, c);
        if (mr < 0) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to 0.\n";
            mr = 0;
        } else if (mr > r - 1) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to " << r - 1 << ".\n";
            mr = r - 1;
        }
        if (mc < 0) {
            std::cerr << "Warning: col of mover: " << mc << " is out of range, default col to 0.\n";
            mc = 0;
        } else if (mc > c - 1) {
            std::cerr << "Warning: row of mover: " << mc << " is out of range, default col to " << c - 1 << ".\n";
            mc = c - 1;
        }
        set_mover(mr, mc, d);
    } else {
        wall = true;
        set_grid(r, c);
        set_exit();
        set_edge_block();
        // the mover will never set at the exit (edge).
        if (mr < 1) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to 1.\n";
            mr = 1;
        } else if (mr > r - 2) {
            std::cerr << "Warning: row of mover: " << mr << " is out of range, default row to " << r - 2 << ".\n";
            mr = r - 2;
        }
        if (mc < 1) {
            std::cerr << "Warning: col of mover: " << mc << " is out of range, default col to 1.\n";
            mc = 1;
        } else if (mc > c - 2) {
            std::cerr << "Warning: row of mover: " << mc << " is out of range, default col to " << c - 2 << ".\n";
            mc = c - 2;
        }
        set_mover(mr, mc, d);
    }
}

// move forward s spaces, if possible.
bool Grid::Move(int s) {
    switch (m_dir) {
        case Grid::NORTH:
            if (m_row - s < 0) {
                std::cerr << "Error, moving out of range.\n";
                return false;
            }
            for (int i = m_row; i >= m_row - s; --i) {
                if (grid[i][m_col] == BLOCK) {
                    std::cerr << "Error, there is a block in the path.\n";
                    return false;
                }
            }
            for (int i = m_row; i >= m_row - s; --i) {
                if (grid[i][m_col] == EMPTY) {
                    grid[i][m_col] = PATH;
                }
            }
            m_row -= s;
            return true;
        case Grid::WEST:
            if (m_col - s < 0) {
                std::cerr << "Error, moving out of range.\n";
                return false;
            }
            for (int i = m_col; i >= m_col - s; --i) {
                if (grid[m_row][i] == BLOCK) {
                    std::cerr << "Error, there is a block in the path.\n";
                    return false;
                }
            }
            for (int i = m_col; i >= m_col - s; --i) {
                if (grid[m_row][i] == EMPTY) {
                    grid[m_row][i] = PATH;
                }
            }
            m_col -= s;
            return true;
        case Grid::SOUTH:
            if (m_row + s > (int)grid.size() - 1) {
                std::cerr << "Error, moving out of range.\n";
                return false;
            }
            for (int i = m_row; i <= m_row + s; ++i) {
                if (grid[i][m_col] == BLOCK) {
                    std::cerr << "Error, there is a block in the path.\n";
                    return false;
                }
            }
            for (int i = m_row; i <= m_row + s; ++i) {
                if (grid[i][m_col] == EMPTY) {
                    grid[i][m_col] = PATH;
                }
            }
            m_row += s;
            return true;
        case Grid::EAST:
            if (m_col + s > (int)grid[0].size() - 1) {
                std::cerr << "Error, moving out of range.\n";
                return false;
            }
            for (int i = m_col; i <= m_col + s; ++i) {
                if (grid[m_row][i] == BLOCK) {
                    std::cerr << "Error, there is a block in the path.\n";
                    return false;
                }
            }
            for (int i = m_col; i <= m_col + s; ++i) {
                if (grid[m_row][i] == EMPTY) {
                    grid[m_row][i] = PATH;
                }
            }
            m_col += s;
            return true;
        default:
            return false;
    }
}

// toggle whether or not moved path is shown.
void Grid::TogglePath() {
    show_path = !show_path;
}

// turn the mover to the left
void Grid::TurnLeft() {
    ++m_dir;
    m_dir %= 4;
}

// put down an item at the mover's position
void Grid::PutDown() {
    grid[m_row][m_col] = ITEM;
}

// put down an item at (r, c), if possible
bool Grid::PutDown(int r, int c) {
    if (r < 0 || r > (int)grid.size() - 1) {
        throw std::out_of_range("Error, r is out of range. Ignoring");
        return false;
    }
    if (c < 0 || c > (int)grid[0].size() - 1) {
        throw std::out_of_range("Error, c is out of range. Ignoring");
        return false;
    }
    if (grid[r][c] == ITEM) {
        std::cerr << "Error, there is already an item at row " << r << " and col " << c << ".\n";
        return false;
    }
    if (grid[r][c] == BLOCK) {
        std::cerr << "Error, there is already a block at row " << r << " and col " << c << ".\n";
        return false;
    }
    grid[r][c] = ITEM;
    return true;
}

// pick up item at current position
bool Grid::PickUp() {
    if (grid[m_row][m_col] == ITEM) {
        grid[m_row][m_col] = EMPTY;
        return true;
    } else {
        std::cerr << "Error, there is no item at the current mover position (row, col) = ("
                  << m_row << ", " << m_col << ")\n";
        return false;
    }
}

// put a block at (r, c), if possible
bool Grid::PlaceBlock(int r, int c) {
    if (r < 0 || r > (int)grid.size() - 1) {
        throw std::out_of_range("Error, r is out of range. Ignoring");
        return false;
    }
    if (c < 0 || c > (int)grid[0].size() - 1) {
        throw std::out_of_range("Error, c is out of range. Ignoring");
        return false;
    }
    switch (grid[r][c]) {
        case EMPTY:
            grid[r][c] = BLOCK;
            return true;
        case ITEM:
            std::cerr << "Error, there is an item at row: " << r << ", col: " << c << ".\n";
            return false;
        case BLOCK:
            std::cerr << "Error, there is a block at row: " << r << ", col: " << c << ".\n";
            return false;
        default:
            break;
    }
    if (r == m_row && c == m_col) {
        std::cerr << "Error, The mover is at row: " << r << ", col: " << c << ".\n";
    }
    return false;
}

// remove a block at (r, c), if there is a block
bool Grid::RemoveBlock(int r, int c) {
    if (r < 0 || r > (int)grid.size() - 1) {
        throw std::out_of_range("Error, r is out of range. Ignoring");
        return false;
    }
    if (c < 0 || c > (int)grid[0].size() - 1) {
        throw std::out_of_range("Error, c is out of range. Ignoring");
        return false;
    }
    if (grid[r][c] == BLOCK) {
        grid[r][c] = EMPTY;
        return true;
    }
    return false;
}

// grow the grid by gr rows, gc columns, i.e., set row to current row + gr.
bool Grid::Grow(int gr, int gc) {
    bool ret = true;
    int set_row, set_col;

    if (gr < 0) {
        std::cerr << "Error, " << gr << " is less than 0. Set to 0.\n";
        gr = 0;
        ret = false;
    }
    if (gc < 0) {
        std::cerr << "Error, " << gc << " is less than 0. Set to 0.\n";
        gc = 0;
        ret = false;
    }

    set_row = (int)grid.size() + gr;
    set_col = (int)grid[0].size() + gc;

    if (set_row > MAXSIZE) {
        std::cerr << "Error, current row: " << grid.size() << " + " << gr << " is greater than " << MAXSIZE << ". Set to " <<  MAXSIZE << ".\n";
        set_row = MAXSIZE;
        ret = false;
    }
    if (set_col > MAXSIZE) {
        std::cerr << "Error, current col: " << grid[0].size() << " + " << gc << " is greater than " << MAXSIZE << ". Set to " <<  MAXSIZE << ".\n";
        set_col = MAXSIZE;
        ret = false;
    }

    if (wall) {
        if (e_row == (int)grid.size() - 1) {  // bottom of the grid
            e_row += gr;
        } else if (e_col == (int)grid[0].size() - 1) {  // right of the grid
            e_col += gc;
        }
        clear_edge_block();
    }
    
    ret &= check_and_set_size(set_row, set_col);  // This function's params are passed by reference.
    grid.resize(set_row, std::vector<int>(set_col, (int)EMPTY));
    for (int i = 0; i < (int)grid.size(); ++i) {
        grid[i].resize(set_col, (int)EMPTY);
    }
    grid_show.resize(set_row, std::vector<char>(set_col, '.'));
    for (int i = 0; i < (int)grid_show.size(); ++i) {
        grid_show[i].resize(set_col, '.');
    }
    ret &= check_vector(set_row, set_col);
    if (wall) {
        set_edge_block();
    }
    return ret;
}

// display the grid on screen
void Grid::Display() {
    sync_grid();  // because of this function, Display() can't be const.
    for (int i = 0; i < (int)grid_show.size(); ++i) {
        for (int j = 0; j < (int)grid_show[0].size(); ++j) {
            std::cout << grid_show[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

// check to see if space in front of mover is clear
bool Grid::FrontIsClear() const {
    switch (m_dir) {
        case NORTH:
            if (m_row == 0) {
                return false;
            }
            if (grid[m_row - 1][m_col] == BLOCK) {
                return false;
            }
            return true;
        case WEST:
            if (m_col == 0) {
                return false;
            }
            if (grid[m_row][m_col - 1] == BLOCK) {
                return false;
            }
            return true;
        case SOUTH:
            if (m_row == (int)grid.size() - 1) {
                return false;
            }
            if (grid[m_row + 1][m_col] == BLOCK) {
                return false;
            }
            return true;
        case EAST:
            if (m_col == (int)grid[0].size() - 1) {
                return false;
            }
            if (grid[m_row][m_col + 1] == BLOCK) {
                return false;
            }
            return true;
        default:
            return false;
    }
}

// check to see if space to right of mover is clear
bool Grid::RightIsClear() const {
    switch (m_dir) {
        case WEST:
            if (m_row == 0) {
                return false;
            }
            if (grid[m_row - 1][m_col] == BLOCK) {
                return false;
            }
            return true;
        case SOUTH:
            if (m_col == 0) {
                return false;
            }
            if (grid[m_row][m_col - 1] == BLOCK) {
                return false;
            }
            return true;
        case EAST:
            if (m_row == (int)grid.size() - 1) {
                return false;
            }
            if (grid[m_row + 1][m_col] == BLOCK) {
                return false;
            }
            return true;
        case NORTH:
            if (m_col == (int)grid[0].size() - 1) {
                return false;
            }
            if (grid[m_row][m_col + 1] == BLOCK) {
                return false;
            }
            return true;
        default:
            return false;
    }
}

// return row of the mover.
int Grid::GetRow() const {
    return m_row;
}

// return cloumn of the mover.
int Grid::GetCol() const {
    return m_col;
}

// return number of rows in the grid.
int Grid::GetNumRows() const {
    return grid.size();
}

// return number of columns int the grid.
int Grid::GetNumCols() const {
    return grid[0].size();
}
