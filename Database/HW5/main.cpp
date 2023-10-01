#include "shell.hpp"

// B+ tree
otis::B_Plus_Tree<int> *BTree = nullptr;

void signalHandler(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received. Exiting\n";
    delete BTree;
    BTree = nullptr;
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    int input = 0;
    std::size_t order = 0;

    // register signal SIGINT and signal handler
    signal(SIGINT, signalHandler);

    // Read the argument first.
    if (argc >= 2) {
        std::cout << "Read command from argument.\n";
        std::cout << "The order is " << argv[1] << ".\n";
        input = atoi(argv[1]);
        if (input < 1) {
            std::cerr << "\x1B[31mError, order " << input << " is illegal. Aborted.\x1B[0m\n";
            return EXIT_FAILURE;
        }
        order = input;  // Type convertion.

        // Get starting timepoint
        auto start = std::chrono::high_resolution_clock::now();

        // Create B+ tree
        BTree = new otis::B_Plus_Tree<int>(order);

        // Insert the data
        for (int i = 2; i < argc; ++i) {
            input = atoi(argv[i]);
            std::cout << "Insert key " << input << ":\n";
            BTree->insert_value(input);
            BTree->print_data();
        }

        // Get ending timepoint
        auto stop = std::chrono::high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get duration. To cast it to proper unit
        // use duration cast method
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "Time taken: " << duration.count() << " microseconds\n\n";

        std::cout << "You can type help or h to get command.\n\n";

        shell(&BTree);
    } else {
        std::cout << "Welcome to B+ Tree. You can type help or h to get command.\n\n";
        shell(&BTree);
    }

    return EXIT_SUCCESS;
}
