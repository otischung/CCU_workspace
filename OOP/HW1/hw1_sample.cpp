/* Sample Program - Average
 * This program computes the average of a set of non-negative integers. It has many
 * deficiencies and is meant only as simple first illustractio of a C++ program.
 */
#include <iostream>

int main() {
    int number;  // The number of scores read.
    int sum;     // The summation of all the scores read.
    int grade;   // Holds each individual score as it is read from the keyboard.
    float average;  // Holds the computed average.

    number = 0;  // Initialize number and sum to 0 before starting.
    sum = 0;

    std::cin >> grade;  // Get the first user input.
    // Loop as long as the input was non-negative.
    while (grade >= 0 && grade <= 100) {
        sum += grade;  // Add new score into sum
        ++number;      // and count one more grade

        std::cin >> grade;  // Now get the next input.
    }

    // When done reading scores, compute average and display.
    if (number > 0) {
        average = (float)sum / number;
    } else {
        average = 0;
    }
    std::cout << average;

    // While done, exit the program.
    return 0;
}
