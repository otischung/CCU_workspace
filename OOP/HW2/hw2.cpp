#include <time.h>

#include <fstream>
#include <iostream>
#include <string>

#define CHECK 0
#define VISA 1
#define MASTER 2
#define AMERICAN 3
#define DISCOVER 4

namespace hw2_time {
struct timespec start, end, diff;
}

class CreditCard {
   private:
    std::string numbers;

    int sumofDoubleEvenPlace(const std::string &cardNumber) {
        int num, sum, a, b;

        sum = 0;
        for (int i = cardNumber.length() - 2; i >= 0; i -= 2) {
            num = cardNumber.at(i) - '0';
            if (num < 0 || num > 9) {
                return false;
            }
            num <<= 1;
            if (num > 9) {
                b = num % 10;
                a = num / 10;
                num = a + b;
            }
            sum += num;
        }
        return sum;
    }

    int sumOfOddPlace(const std::string &cardNumber) {
        int sum, num;

        sum = 0;
        for (int i = cardNumber.length() - 1; i >= 0; i -= 2) {
            num = cardNumber.at(i) - '0';
            sum += num;
        }
        return sum;
    }

   public:
    CreditCard(std::string str) : numbers(str) {}
    CreditCard() {}

    void input(std::string str) {
        numbers = str;
    }

    int gen_or_check() {
        if (numbers == "004") {
            return VISA;
        } else if (numbers == "005") {
            return MASTER;
        } else if (numbers == "0037") {
            return AMERICAN;
        } else if (numbers == "006") {
            return DISCOVER;
        } else {
            return CHECK;
        }
    }

    int card_type(const std::string &cardNumber) {
        int prefix;

        if (cardNumber.at(0) == '4' && (cardNumber.length() == 13 || cardNumber.length() == 16)) {
            // 4xxx xxxx xxxx x(xxx)
            return VISA;
        } else if (cardNumber.at(0) == '5' && cardNumber.at(1) - '0' >= 1 && cardNumber.at(1) - '0' <= 5 && cardNumber.length() == 16) {
            // (51-55)xx xxxx xxxx xxxx
            return MASTER;
        } else if (cardNumber.at(0) == '3' && (cardNumber.at(1) == '4' || cardNumber.at(1) == '7') && cardNumber.length() == 15) {
            // (34|37)xx xxxx xxxx xxx
            return AMERICAN;
        } else if (cardNumber.at(0) == '6' && cardNumber.length() >= 16 && cardNumber.length() <= 19) {
            prefix = stoi(cardNumber.substr(0, 4));
            if (prefix == 6011) {
                return DISCOVER;
            }
            prefix = stoi(cardNumber.substr(0, 3));
            if (prefix >= 644 && prefix <= 649) {
                return DISCOVER;
            }
            prefix = stoi(cardNumber.substr(0, 2));
            if (prefix == 65) {
                return DISCOVER;
            }
            prefix = stoi(cardNumber.substr(0, 6));
            if (prefix >= 622126 && prefix <= 622925) {
                return DISCOVER;
            }
            return 0;
        } else {
            return 0;
        }
    }

    void print_card_type(const int card_type) {
        switch (card_type) {
            case VISA:
                std::cout << "Visa";
                break;

            case MASTER:
                std::cout << "MasterCard";
                break;

            case AMERICAN:
                std::cout << "American Express";
                break;

            case DISCOVER:
                std::cout << "Discover";
                break;

            default:
                std::cout << "Unknown type";
                break;
        }
    }

    bool isValid(const std::string &cardNumber) {
        int first, second;

        if (!card_type(cardNumber)) {
            return false;
        }
        first = sumofDoubleEvenPlace(cardNumber);
        second = sumOfOddPlace(cardNumber);
        if ((first + second) % 10 != 0) {
            return false;
        }
        return true;
    }

    std::string fake_one(int brand) {
        std::string cardNumber;
        int odd, even;

        clock_gettime(CLOCK_MONOTONIC, &hw2_time::start);
        switch (brand) {
            case VISA:  // 4xxx xxxx xxxx x(xxx)
                cardNumber.push_back('4');
                for (int i = 0; i < 14; ++i) {
                    cardNumber.push_back(rand() % 10 + '0');
                }
                break;

            case MASTER:  // (51-55)xx xxxx xxxx xxxx
                cardNumber.push_back('5');
                cardNumber.push_back(rand() % 5 + '1');
                for (int i = 0; i < 13; ++i) {
                    cardNumber.push_back(rand() % 10 + '0');
                }
                break;

            case AMERICAN:  // (34|37)xx xxxx xxxx xxx
                if (rand() % 2) {
                    cardNumber.append("34");
                } else {
                    cardNumber.append("37");
                }
                for (int i = 0; i < 12; ++i) {
                    cardNumber.push_back(rand() % 10 + '0');
                }
                break;

            case DISCOVER:  // 6011 xxxx xxxx xxxx (Only use this rule in this generator)
                cardNumber.append("6011");
                for (int i = 0; i < 11; ++i) {
                    cardNumber.push_back(rand() % 10 + '0');
                }
                break;
        }
        cardNumber.push_back('0');
        odd = sumOfOddPlace(cardNumber);
        even = sumofDoubleEvenPlace(cardNumber);
        if ((odd + even) % 10) {
            cardNumber.pop_back();
            cardNumber.push_back(10 - ((odd + even) % 10) + '0');
        }
        clock_gettime(CLOCK_MONOTONIC, &hw2_time::end);
        hw2_time::diff.tv_sec = hw2_time::end.tv_sec - hw2_time::start.tv_sec;
        hw2_time::diff.tv_nsec = hw2_time::end.tv_nsec - hw2_time::start.tv_nsec;
        if (hw2_time::diff.tv_nsec < 0) {
            --hw2_time::diff.tv_sec;
            hw2_time::diff.tv_nsec += 1000000000;
        }

        if (!isValid(cardNumber)) {  // Self check.
            std::cerr << "Generator error.\n";
            cardNumber = "";
        }
        return cardNumber;
    }
};

int main(int argc, char *argv[]) {
    CreditCard c;
    std::string input, fakecard;
    std::fstream fp;
    int card_type;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [filename]\n";
        exit(1);
    }
    fp.open(argv[1], std::ios::in);
    if (!fp) {
        std::cerr << "Open file: " << argv[1] << " error.\n";
        exit(1);
    }
    srand(time(NULL));
    while (std::getline(fp, input), !fp.eof()) {
        c.input(input);
        card_type = c.gen_or_check();
        if (card_type) {  // Generate.
            std::cout << "Generated a valid ";
            c.print_card_type(card_type);
            std::cout << " card: ";
            // clock_gettime(CLOCK_MONOTONIC, &hw2_time::start);
            fakecard = c.fake_one(card_type);
            // clock_gettime(CLOCK_MONOTONIC, &hw2_time::end);
            // hw2_time::diff.tv_sec = hw2_time::end.tv_sec - hw2_time::start.tv_sec;
            // hw2_time::diff.tv_nsec = hw2_time::end.tv_nsec - hw2_time::start.tv_nsec;
            // if (hw2_time::diff.tv_nsec < 0) {
            //     --hw2_time::diff.tv_sec;
            //     hw2_time::diff.tv_nsec += 1000000000;
            // }
            std::cout << fakecard;
            std::cout << "; Timing: " << hw2_time::diff.tv_sec * 1000000000 + hw2_time::diff.tv_nsec << " ns\n";
        } else {  // Check.
            card_type = c.card_type(input);
            if (c.isValid(input)) {
                std::cout << input << ": a valid ";
            } else {
                std::cout << input << ": an invalid ";
            }
            c.print_card_type(card_type);
            std::cout << " card\n";
        }  // end of card_type = c.gen_or_check();.
    }
    fp.close();
    return EXIT_SUCCESS;
}
