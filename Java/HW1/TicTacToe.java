import java.util.InputMismatchException;
import java.util.Scanner;

public class TicTacToe {
    private State[][] grid = new State[3][3];
    private boolean turn; // X: false, O: true

    private void reset() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                grid[i][j] = State.EMPTY;
            }
        }
        turn = false;
    }

    private Game check() {
        for (int i = 0; i < 3; ++i) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != State.EMPTY) {
                return Game.WIN;
            }
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != State.EMPTY) {
                return Game.WIN;
            }
        }
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != State.EMPTY) {
            return Game.WIN;
        }
        if (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[2][0] != State.EMPTY) {
            return Game.WIN;
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[i][j] == State.EMPTY) {
                    return Game.CONT;
                }
            }
        }
        return Game.DRAW;
    }

    private boolean set(int i, int j) throws IndexOutOfBoundsException {
        if (i < 0 || i > 2 || j < 0 || j > 2) {
            throw new IndexOutOfBoundsException("Error, input index is out of range. Retype it.");
        }
        if (grid[i][j] != State.EMPTY) {
            return false;
        }
        if (this.turn) {
            grid[i][j] = State.O;
        } else {
            grid[i][j] = State.X;
        }
        return true;
    }

    private void print_grid() {
        System.out.print("\033c"); // To clear termainal.
        System.out.println("+---+---+---+");
        for (int i = 0; i < 3; ++i) {
            System.out.print("| ");
            switch (grid[0][i]) {
                case EMPTY:
                    System.out.print("  ");
                    break;
                case X:
                    System.out.print("X ");
                    break;
                case O:
                    System.out.print("O ");
                    break;
                default:
                    break;
            }
        }
        System.out.println("|");
        System.out.println("+---+---+---+");
        for (int i = 0; i < 3; ++i) {
            System.out.print("| ");
            switch (grid[1][i]) {
                case EMPTY:
                    System.out.print("  ");
                    break;
                case X:
                    System.out.print("X ");
                    break;
                case O:
                    System.out.print("O ");
                    break;
                default:
                    break;
            }
        }
        System.out.println("|");
        System.out.println("+---+---+---+");
        for (int i = 0; i < 3; ++i) {
            System.out.print("| ");
            switch (grid[2][i]) {
                case EMPTY:
                    System.out.print("  ");
                    break;
                case X:
                    System.out.print("X ");
                    break;
                case O:
                    System.out.print("O ");
                    break;
                default:
                    break;
            }
        }
        System.out.println("|");
        System.out.println("+---+---+---+");
    }

    public static enum State {
        EMPTY, X, O
    };

    public static enum Game {
        CONT, WIN, DRAW
    };

    public TicTacToe() {
        reset();
    }

    public void game_handler() {
        Scanner sc = new Scanner(System.in);
        String input;
        int round = 0;
        int x, y;
        boolean restart = false;
        Game g;

        do {
            reset();
            round = 0;
            while (true) {
                print_grid();
                ++round;
                System.out.println("Round " + round);
                if (turn) {
                    System.out.println("Now is O's turn, enter location:");
                } else {
                    System.out.println("Now is X's turn, enter location:");
                }
                while (true) {
                    try {
                        x = sc.nextInt();
                        y = sc.nextInt();
                        if (!set(x, y)) {
                            System.err.println("Error, there is not empty. Retype it.");
                            continue;
                        }
                        break;
                    } catch (IndexOutOfBoundsException e) {
                        System.err.println(e);
                    } catch (InputMismatchException e2) {
                        System.err.println("Error, input type is illegal. Retype it.");
                        sc.next();
                    }
                }
                g = check();
                if (g == Game.WIN) {
                    print_grid();
                    if (turn) {
                        System.out.println("O is winner.");
                    } else {
                        System.out.println("X is winner.");
                    }
                    break;
                } else if (g == Game.DRAW) {
                    print_grid();
                    System.out.println("Draw!");
                    break;
                }
                turn = !turn;
            }
            System.out.println("Restart? (y/n)");
            input = sc.nextLine();
            input = sc.nextLine();
            if (input.equals("y") || input.equals("Y")) {
                restart = true;
            } else {
                restart = false;
            }
        } while (restart);
        System.out.println("Goodbye.");
        sc.close();
    }

    public static void main(String[] args) {
        TicTacToe t = new TicTacToe();
        t.game_handler();
    }
}
