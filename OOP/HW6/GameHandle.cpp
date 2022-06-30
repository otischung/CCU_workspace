#include "GameHandle.h"

Card::Card(int rank, int suit) : rank(rank), suit(suit) {}

int Card::getRank() {
    return rank;
}

int Card::getSuit() {
    return suit;
}

int Card::getRank(Card c) {
    return c.rank;
}

int Card::getSuit(Card c) {
    return c.suit;
}

void Card::printCard(Card c) {
    std::cout << "[";
    switch (c.getRank()) {
        case 11:
            std::cout << "J";
            break;
        case 12:
            std::cout << "Q";
            break;
        case 13:
            std::cout << "K";
            break;
        default:
            std::cout << c.getRank();
            break;
    }
    switch (c.getSuit()) {
        case Card::CLUB:
            std::cout << " ♣";
            break;
        case Card::DIAMOND:
            std::cout << " ♦";
            break;
        case Card::HEART:
            std::cout << " ♥";
            break;
        case Card::SPADE:
            std::cout << " ♠";
            break;
        default:
            break;
    }
    std::cout << "] ";
}

/////////////////////////////////////////////////////////////////////////////////////

Cards::Cards(int p) {
    setup(p);
}

void Cards::setup(int players) {
    this->players = players;
    cards.clear();
    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < players; ++k) {
                cards.emplace_back(Card(i, j));
            }
        }
    }
    shuffle();
}

void Cards::shuffle() {
    // https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
    std::random_device rd;
    auto rng = std::default_random_engine{rd()};
    std::shuffle(std::begin(cards), std::end(cards), rng);
}

Card Cards::draw() {
    Card card = cards[cards.size() - 1];
    cards.pop_back();
    return card;
}

/////////////////////////////////////////////////////////////////////////////////////

Player::Player(std::string n, int ba, int be, bool bot, bool meek, bool random) : name(n), bankroll(ba), bet(be), win(false), is_bot(bot), is_meek(meek), is_random(random), ace(0), handPoints(0), winCnt(0) {}

Player::~Player() {}

bool Player::isBot() {
    return is_bot;
}

bool Player::isMeek() {
    return is_meek;
}

bool Player::isRandom() {
    return is_random;
}

std::string Player::getName() {
    return name;
}

void Player::joinGame(Game *game) {
    joinedGame = game;
}

void Player::clearHand() {
    hand.clear();
    ace = 0;
    handPoints = 0;
}

void Player::setBet(int bet) {
    this->bet = bet;
}

int Player::getBet() {
    return bet;
}

void Player::setBankroll(int num) {
    bankroll += num;
}

int Player::getBankRoll() {
    return bankroll;
}

void Player::printBankroll() {
    std::cout << name << "\t$" << bankroll << '\n';
}

void Player::calPoints() {
    int rank;

    ace = 0;
    handPoints = 0;
    for (int i = 0; i < (int)hand.size(); ++i) {
        rank = Card::getRank(hand[i]);
        if (rank == 1) {
            ++ace;
            rank = 11;
        } else if (rank > 10) {
            rank = 10;
        }
        handPoints += rank;
    }
    while (ace && handPoints > 21) {
        --ace;
        handPoints -= 10;
    }
}

Card Player::hit() {
    return joinedGame->draw();
}

/////////////////////////////////////////////////////////////////////////////////////

Human::Human(std::string n, int ba) : Player(n, ba, 0, false, false, false) {}

Human::~Human() {}

void Human::strategy() {
    std::string yn;
    bool cont = true;
    while (cont) {
        std::cout << name << "'s current hand: ";
        for (int i = 0; i < (int)hand.size(); ++i) {
            Card::printCard(hand[i]);
        }
        calPoints();
        std::cout << '(' << handPoints << " points)\n";
        std::cout << std::endl;
        if (handPoints > 21) {
            std::cout << name << " busts at " << handPoints << ".\n";
            win = false;
            break;
        }
        std::cout << "Would you like to draw another card (Y or N): ";
        std::cin >> yn;
        if (yn == "Y" || yn == "y") {
            std::cout << name << " chooses to hit.\n";
            hand.emplace_back(hit());
            cont = true;
        } else {
            std::cout << name << " chooses to stand.\n";
            cont = false;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////

Dealer::Dealer() : Player("Dealer", 10000, 0, true, false, false) {}

Dealer::~Dealer() {}

void Dealer::strategy() {
    bool cont = true;
    while (cont) {
        std::cout << name << "'s currents hand: ";
        for (int i = 0; i < (int)hand.size(); ++i) {
            Card::printCard(hand[i]);
        }
        calPoints();
        std::cout << '(' << handPoints << " points)\n";
        std::cout << std::endl;
        if (handPoints > 21) {
            std::cout << name << " busts at " << handPoints << ".\n";
            win = false;
            break;
        }
        if (handPoints < 17) {
            std::cout << name << " chooses to hit.\n";
            hand.emplace_back(hit());
            cont = true;
        } else {
            std::cout << name << " chooses to stand.\n";
            cont = false;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////

Meek::Meek(int ba) : Player("Meek", ba, 2, true, true, false) {}

Meek::~Meek() {}

void Meek::strategy() {
    bool cont = true;
    bool clubSeven = false;

    while (cont) {
        std::cout << name << "'s current hand: ";
        for (int i = 0; i < (int)hand.size(); ++i) {
            Card::printCard(hand[i]);
            if (Card::getSuit(hand[i]) == Card::CLUB && Card::getRank(hand[i]) == 7) {
                clubSeven = true;
            }
        }
        calPoints();
        std::cout << '(' << handPoints << " points)\n";
        std::cout << std::endl;
        if (handPoints > 21) {
            std::cout << name << " bust at " << handPoints << ".\n";
            win = false;
            break;
        }
        if (clubSeven) {
            std::cout << name << " has club 7 so it chooses to hit.\n";
            hand.emplace_back(hit());
            cont = true;
        } else {
            if (handPoints & 1) {  // odd number
                std::cout << name << " chooses to stand.\n";
                cont = false;
            } else {  // even number
                std::cout << name << " chooses to hit.\n";
                hand.emplace_back(hit());
                cont = true;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////

Random::Random(int ba) : Player("Random", ba, 0, true, false, true) {}

Random::~Random() {}

void Random::setBet(int bet) {
    if (this->bankroll <= 1) {
        this->bet = 1;
    } else {
        this->bet = rand() % (this->bankroll / 2) + 1;
    }
}

void Random::strategy() {
    bool cont = true;
    while (cont) {
        std::cout << name << "'s currents hand: ";
        for (int i = 0; i < (int)hand.size(); ++i) {
            Card::printCard(hand[i]);
        }
        calPoints();
        std::cout << '(' << handPoints << " points)\n";
        std::cout << std::endl;
        if (handPoints > 21) {
            std::cout << name << " busts at " << handPoints << ".\n";
            win = false;
            break;
        }
        if (handPoints <= 9) {
            std::cout << name << " chooses to hit.\n";
            hand.emplace_back(hit());
            cont = true;
        } else if (handPoints >= 10 && handPoints <= 12) {
            if ((rand() % 5) < 4) {
                std::cout << name << " chooses to hit.\n";
                hand.emplace_back(hit());
                cont = true;
            } else {
                std::cout << name << " chooses to stand.\n";
                cont = false;
            }
        } else if (handPoints >= 13 && handPoints <= 15) {
            if ((rand() % 10) < 7) {
                std::cout << name << " chooses to hit.\n";
                hand.emplace_back(hit());
                cont = true;
            } else {
                std::cout << name << " chooses to stand.\n";
                cont = false;
            }
        } else if (handPoints >= 16 && handPoints <= 18) {
            if (rand() % 2) {
                std::cout << name << " chooses to hit.\n";
                hand.emplace_back(hit());
                cont = true;
            } else {
                std::cout << name << " chooses to stand.\n";
                cont = false;
            }
        } else {
            std::cout << name << " chooses to stand.\n";
            cont = false;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////

void Game::joinPlayer(Player *p) {
    players.emplace_back(p);
}

Card Game::draw() {
    return cards->draw();
}

void Game::GameHandle() {
    int playerCnt = 0;
    int bankroll;
    int bet;
    bool negBalance = false;
    std::string name;
    std::string restart = "N";
    Dealer *d = new Dealer();

    srand(time(NULL));

    // Check numbers of players, cannot less than 1.
    std::cout << "Welcome to play blackjack!!!\n";
    std::cout << "How many players you want to create: ";
    while (std::cin >> playerCnt, std::cin.fail()) {
        // https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/
        std::cerr << "Invalid input, try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (playerCnt < 1) {
        std::cerr << "Warning: " << playerCnt << " is less than 1, default to 1.\n";
        playerCnt = 1;
    }
    cards = new Cards(playerCnt + 1);
    d->joinGame(this);
    joinPlayer(d);

    // Specify the type of players and their bankroll.
    std::cout << "Please enter the name or the type of bots.\n";
    std::cout << "There are two types of bots, which is Meek and Random.\n";
    std::cout << "If you want to create bot, just enter the type of bot.\n\n";
    for (int i = 1; i <= playerCnt; ++i) {
        std::cout << "Name: ";
        std::cin >> name;
        if (name == "Meek" || name == "meek") {
            std::cout << "Create Meek bot.\n";
            std::cout << "Please enter Meek's bankroll: ";
            while (std::cin >> bankroll, std::cin.fail()) {
                std::cerr << "Invalid input, try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (bankroll < 1) {
                std::cerr << "Warning: Your bankroll is less than 1. Default to 1.\n";
                bankroll = 1;
            }
            Meek *m = new Meek(bankroll);
            m->joinGame(this);
            joinPlayer(m);
        } else if (name == "Random" || name == "random") {
            std::cout << "Create Random bot.\n";
            std::cout << "Please enter Random's bankroll: ";
            while (std::cin >> bankroll, std::cin.fail()) {
                std::cerr << "Invalid input, try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (bankroll < 1) {
                std::cerr << "Warning: Your bankroll is less than 1. Default to 1.\n";
                bankroll = 1;
            }
            Random *r = new Random(bankroll);
            r->joinGame(this);
            joinPlayer(r);
        } else {
            std::cout << "Create " << name << " human player.\n";
            std::cout << "Please enter " << name << "'s bankroll: ";
            while (std::cin >> bankroll, std::cin.fail()) {
                std::cerr << "Invalid input, try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            if (bankroll < 1) {
                std::cerr << "Warning: Your bankroll is less than 1. Default to 1.\n";
                bankroll = 1;
            }
            Human *h = new Human(name, bankroll);
            h->joinGame(this);
            joinPlayer(h);
        }
    }
    std::cout << "\nThe initial bankroll is listed below.\n";
    for (int i = 0; i < (int)players.size(); ++i) {
        players[i]->printBankroll();
    }

    // Game loop.
    while (true) {
        // Set players' bet.
        std::cout << "\nOkay, time for betting.\n";
        std::cout << "--------------------------------\n";
        for (int i = 0; i < (int)players.size(); ++i) {
            if (players[i]->isBot()) {
                if (players[i]->isRandom()) {
                    players[i]->setBet(0);
                } else if (players[i]->isMeek() && players[i]->winCnt == 3) {
                    players[i]->setBet(players[i]->getBet() << 1);
                    players[i]->winCnt = 0;
                } else {
                    continue;
                }
            } else {
                std::cout << players[i]->getName() << ": how much would you like to bet? ";
                while (std::cin >> bet, std::cin.fail()) {
                    std::cerr << "Invalid input, try again: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                if (bet < 1) {
                    std::cerr << "Warning: Your bet is less than 1. Default to 1.\n";
                    bet = 1;
                }
                players[i]->setBet(bet);
            }
        }

        // Show everyone's bet.
        std::cout << "--------------------------------\n";
        for (int i = 1; i < (int)players.size(); ++i) {
            std::cout << players[i]->getName() << " bets $" << players[i]->getBet() << '\n';
        }
        std::cout << std::endl;

        // Draw two cards.
        for (int i = 0; i < (int)players.size(); ++i) {
            players[i]->hand.emplace_back(draw());
        }
        for (int i = 0; i < (int)players.size(); ++i) {
            players[i]->hand.emplace_back(draw());
        }

        std::cout << "The initial starting cards are:\n";
        std::cout << "--------------------------------\n";
        for (int i = 0; i < (int)players.size(); ++i) {
            std::cout << players[i]->getName() << "'s current hand: ";
            std::cout << "[??] ";
            Card::printCard(players[i]->hand[1]);
            std::cout << '\n';
        }
        std::cout << std::endl;

        // Strategy
        for (int i = 1; i < (int)players.size(); ++i) {
            std::cout << players[i]->getName() << "'s turn:\n";
            std::cout << "--------------------------------\n";
            players[i]->strategy();
            std::cout << std::endl;
        }

        // Dealer's stage
        std::cout << players[0]->getName() << "'s turn:\n";
        std::cout << "--------------------------------\n";
        players[0]->strategy();
        std::cout << std::endl;

        // Calculate result
        std::cout << "Let's see how it turned out:\n";
        std::cout << "--------------------------------\n";
        for (int i = 1; i < (int)players.size(); ++i) {
            if (players[i]->handPoints <= 21) {
                if (players[i]->handPoints > players[0]->handPoints || players[0]->handPoints > 21) {
                    std::cout << "Yowzah! " << players[i]->getName() << " wins $" << players[i]->getBet() << '\n';
                    players[i]->setBankroll(players[i]->getBet());
                    players[0]->setBankroll(-(players[i]->getBet()));
                    ++(players[i]->winCnt);
                } else if (players[i]->handPoints == players[0]->handPoints) {
                    std::cout << "Wow! " << players[i]->getName() << " draws, return the bet $" << players[i]->getBet() << '\n';
                    players[i]->winCnt = 0;
                } else {
                    std::cout << "Ouch! " << players[i]->getName() << " loses $" << players[i]->getBet() << '\n';
                    players[i]->setBankroll(-(players[i]->getBet()));
                    players[0]->setBankroll(players[i]->getBet());
                    players[i]->winCnt = 0;
                }
            } else {
                std::cout << "Ouch! " << players[i]->getName() << " loses $" << players[i]->getBet() << '\n';
                players[i]->setBankroll(-(players[i]->getBet()));
                players[0]->setBankroll(players[i]->getBet());
                players[i]->winCnt = 0;
            }
        }
        std::cout << std::endl;

        // Calculate remaining bankroll
        std::cout << "The standings so far:\n";
        std::cout << "--------------------------------\n";
        for (int i = 0; i < (int)players.size(); ++i) {
            players[i]->printBankroll();
            if (players[i]->getBankRoll() < 0) {
                negBalance |= true;
            }
            players[i]->clearHand();
        }
        if (negBalance) {
            std::cout << "Bankrupt!!! Game end.\n";
            break;
        }
        std::cout << std::endl;

        // Ask for another round.
        std::cout << "Another round? (Y or N): ";
        std::cin >> restart;
        if (restart == "Y" || restart == "y") {
            cards->setup(playerCnt);
            std::cout << std::endl;
        } else {
            std::cout << "Goodbye." << std::endl;
            break;
        }
    }

    // End game, clear memory.
    for (int i = 0; i < (int)players.size(); ++i) {
        delete players[i];
    }
    players.clear();
    delete cards;
}
