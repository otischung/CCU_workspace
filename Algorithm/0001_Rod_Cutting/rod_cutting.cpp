#include <algorithm>
#include <iostream>
#include <vector>

class Rod {
   private:
    std::vector<int> price;
    std::vector<int> table;
    std::vector<int> backtrack;

   public:
    Rod(std::vector<int> &p) : price(p) {
        table.resize(price.size(), 0);
        backtrack.resize(price.size(), 0);
    }
    int rod_cutting() {
        for (int length = 1; length < price.size(); ++length) {
            int max = -2147483648;
            int bestLength = 0;
            for (int subLength = 1; subLength <= length; ++subLength) {
                if (max < price[subLength] + table[length - subLength]) {
                    max = price[subLength] + table[length - subLength];
                    bestLength = subLength;
                }
            }
            table[length] = max;
            backtrack[length] = bestLength;
        }
        return table[price.size() - 1];
    }
    void print_table() {
        std::cout << "Table:\n";
        for (int i = 0; i < (int)table.size(); ++i) {
            std::cout << table[i] << '\t';
        }
        std::cout << "\nBacktrack:\n";
        for (int i = 0; i < (int)backtrack.size(); ++i) {
            std::cout << backtrack[i] << '\t';
        }
        std::cout << std::endl;
    }
};

int main(int argc, char **argv) {
    std::vector<int> price = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    Rod r(price);
    std::cout << r.rod_cutting() << std::endl;
    r.print_table();
    return 0;
}
