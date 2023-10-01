#pragma once
#include "B_plus_tree.hpp"

// System command
void system_command(std::stringstream &inputStream, std::string &command) {
    getline(inputStream, command);
    while (isspace(command[0])) {
        command.erase(0, 1);
    }
    system(command.c_str());
    return;
}

// Help function
void help() {
    std::cout << "Usage: [ACTIONS] [VALUE1] [VALUE2] ...\n\n";
    std::cout << "The following actions may be given as the first argument.\n";
    std::cout << "\\! [shell command]\t\t\tUse the system shell.\n";
    std::cout << "c,  create [VALUE]\t\t\tCreate new B+ tree with order VALUE.\n";
    std::cout << "dd, delete_all\t\t\t\tDelete the hole B+ tree.\n";
    std::cout << "h,  help\t\t\t\tGet help page.\n";
    std::cout << "i,  insert [VALUE1] [VALUE2] ...\tInsert multiple values into B+ tree.\n";
    std::cout << "d,  delete [VALUE1] [VALUE2] ...\tDelete multiple values from B+ tree.\n";
    std::cout << "f,  find   [VALUE1] [VALUE2] ...\t\tDetermine if the value is in the B+ tree or not.\n";
    std::cout << "s,  show\t\t\t\tShow the B+ tree.\n";
    std::cout << "sd, show_debug\t\t\t\tShow the B+ tree and the debug message.\n";
    std::cout << "q,  exit, EOF, ^C\t\t\tExit the program.\n";
    return;
}

// Check if there is a tree. Return true if there contains a tree.
bool contain_tree(otis::B_Plus_Tree<int> **BTree) {
    if (*BTree == nullptr) {
        return false;
    }
    return true;
}

// Create B+ tree
void create_tree(otis::B_Plus_Tree<int> **BTree, std::stringstream &inputStream) {
    int input;

    // Check if there already contains a tree.
    if (contain_tree(BTree)) {
        std::cerr << "\x1B[31mError, there is already have a tree with order " << (*BTree)->get_capacity() / 2 << ".\x1B[0m\n";
        return;
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    inputStream >> input;
    if (inputStream.fail() || input < 1) {
        std::cerr << "\x1B[31mInvalid input, try again.\x1B[0m\n";
        inputStream.clear();
        inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cout << "Create B+ tree with order: " << input << ". Success.\n";
    *BTree = new otis::B_Plus_Tree<int>(input);


    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " microseconds\n\n";
    return;
}

// Delete the whole B+ tree.
void delete_tree(otis::B_Plus_Tree<int> **BTree) {
    if (!contain_tree(BTree)) {
        std::cerr << "\x1B[31mError, there is no tree. Ignored.\x1B[0m\n";
        return;
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    delete *BTree;
    *BTree = nullptr;
    std::cout << "Delete whole tree. Success.\n";

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " microseconds\n\n";
    return;
}

// Insert function
void insert_data(otis::B_Plus_Tree<int> **BTree, std::stringstream &inputStream) {
    int input;

    // Check if there already contains a tree.
    if (!contain_tree(BTree)) {
        std::cerr << "\x1B[31mError, there is no tree exists. Create a tree with 'create' or 'c' [ORDER] first.\x1B[0m\n";
        return;
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    while (inputStream >> input) {
        if (inputStream.fail()) {
            std::cerr << "\x1B[31mInvalid input, try again.\x1B[0m\n";
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Insert key " << input << ": ";
        (*BTree)->insert_value(input) ? std::cout << "Success.\n\n" : std::cerr << "Duplicate. Ignored\n\n";
    }

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " microseconds\n\n";
    return;
}

// Delete function
void delete_data(otis::B_Plus_Tree<int> **BTree, std::stringstream &inputStream) {
    int input;

    // Check if there already contains a tree.
    if (!contain_tree(BTree)) {
        std::cerr << "\x1B[31mError, there is no tree exists. Create a tree with 'create' or 'c' [ORDER] first.\x1B[0m\n";
        return;
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    while (inputStream >> input) {
        if (inputStream.fail()) {
            std::cerr << "\x1B[31mInvalid input, try again.\x1B[0m\n";
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "Delete key " << input << ": ";
        (*BTree)->delete_value(input) ? std::cout << "Success.\n\n" : std::cerr << "Error, " << input << " is not found.\n\n";
    }

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " microseconds\n\n";
}

// Find funtion
void find(otis::B_Plus_Tree<int> **BTree, std::stringstream &inputStream) {
    int input;

    // Check if there already contains a tree.
    if (!contain_tree(BTree)) {
        std::cerr << "\x1B[31mError, there is no tree exists. Create a tree with 'create' or 'c' [ORDER] first.\x1B[0m\n";
        return;
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    while (inputStream >> input) {
        if (inputStream.fail()) {
            std::cerr << "\x1B[31mInvalid input, try again.\x1B[0m\n";
            inputStream.clear();
            inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << input << ": ";
        (*BTree)->contains_value(input) ? std::cout << "True.\n\n" : std::cout << "False.\n\n";
    }

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken: " << duration.count() << " microseconds\n\n";
    return;
}

// Show function
void show(otis::B_Plus_Tree<int> **BTree, bool show_debug_msg) {
    // Check if there already contains a tree.
    if (!contain_tree(BTree)) {
        std::cerr << "\x1B[31mError, there is no tree exists. Create a tree with 'create' or 'c' [ORDER] first.\x1B[0m\n";
        return;
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    (*BTree)->print_data(show_debug_msg);
    std::cout << '\n';

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
}

// Important: We need to pass by reference to avoid double free error. (Call destructor two times)
void shell(otis::B_Plus_Tree<int> **BTree) {
    std::string ins, action, command;

    std::cout << "\n> ";
    std::cout.flush();
    while (getline(std::cin, ins)) {
        if (ins.length() == 0) {
            std::cout << "\n> ";
            std::cout.flush();
            continue;
        }
        // Turn the input string to a stream
        std::stringstream inputStream(ins);
        // The first word is action.
        inputStream >> action;

        // Action: system command
        if (!strcasecmp(action.c_str(), "\\!")) {
            system_command(inputStream, command);
        }
        // Action: help
        else if (!strcasecmp(action.c_str(), "help") || !strcasecmp(action.c_str(), "h")) {
            help();
        }
        // Action: create
        else if (!strcasecmp(action.c_str(), "create") || !strcasecmp(action.c_str(), "c")) {
            create_tree(BTree, inputStream);
        }
        // Action: delete all
        else if (!strcasecmp(action.c_str(), "delete_all") || !strcasecmp(action.c_str(), "dd")) {
            delete_tree(BTree);
        }
        // Action: insert
        else if (!strcasecmp(action.c_str(), "insert") || !strcasecmp(action.c_str(), "i")) {
            insert_data(BTree, inputStream);
        }
        // Action: delete
        else if (!strcasecmp(action.c_str(), "delete") || !strcasecmp(action.c_str(), "d")) {
            delete_data(BTree, inputStream);
        }
        // Action find element
        else if (!strcasecmp(action.c_str(), "find") || !strcasecmp(action.c_str(), "f")) {
            find(BTree, inputStream);
        }
        // Action: display tree
        else if (!strcasecmp(action.c_str(), "show") || !strcasecmp(action.c_str(), "s")) {
            inputStream.clear();
            show(BTree, false);
        }
        // Action: display tree and show the debug message
        else if (!strcasecmp(action.c_str(), "show_debug") || !strcasecmp(action.c_str(), "sd")) {
            inputStream.clear();
            show(BTree, true);
        }
        // Action: exit
        else if (!strcasecmp(action.c_str(), "exit") || !strcasecmp(action.c_str(), "q")) {
            std::cout << "Goodbye.\n";
            return;
        } else {
            std::cerr << action << ": Command not found.\n";
        }
        std::cout << "\n> ";
        std::cout.flush();
    }

    delete *BTree;
    *BTree = nullptr;
    std::cout << "Detect EOF. Exiting.\n";
    return;
}
