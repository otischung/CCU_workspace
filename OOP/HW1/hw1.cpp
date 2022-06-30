#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
    int number;      // The number of scores read.
    int sum;         // The summation of all the scores read.
    int grade;       // Holds each individual score as it is read from the keyboard.
    double average;  // Holds the computed average.
    std::string input;

    number = 0;  // Initialize number and sum to 0 before starting.
    sum = 0;
    while (true) {
        std::cout << "Please input your score:\n";
        std::getline(std::cin, input);
        if (std::regex_search(input, std::regex("[^\\d\\+\\-]"))) {
            std::cout << "illegal input, ending the program...\n";
            exit(1);
        }
        std::stringstream input_stream(input);
        input_stream >> grade;
        if (grade == -1) {
            break;
        } else if (grade < 0 || grade > 100) {
            std::cout << "illegal input, ending the program...\n";
            exit(1);
        } else {
            sum += grade;
            ++number;
        }
    }
    average = (double)sum / number;
    std::cout << std::fixed << std::setprecision(2) << "The average is " << average << ".\n";
    return 0;
}
