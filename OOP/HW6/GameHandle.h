#pragma once
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

class Card;
class Cards;
class Player;
class Human;
class Dealer;
class Meek;
class Random;
class Game;

class Card {
   private:
    int rank, suit;

   public:
    static const int CLUB = 0;
    static const int DIAMOND = 1;
    static const int HEART = 2;
    static const int SPADE = 3;
    Card(int rank, int suit);
    int getRank();
    int getSuit();
    static int getRank(Card c);
    static int getSuit(Card c);
    static void printCard(Card c);
};

class Cards {
   private:
    int players;
    std::vector<Card> cards;

   public:
    Cards(int p = 2);
    void setup(int players);
    void shuffle();
    Card draw();
};

class Player {
   protected:
    Game *joinedGame;
    std::string name;
    int bankroll;
    int bet;
    bool win;
    bool is_bot;
    bool is_meek;
    bool is_random;

   public:
    int ace;
    int handPoints;
    int winCnt;
    std::vector<Card> hand;

    Player(std::string n, int ba, int be, bool bot, bool meek, bool random);
    virtual ~Player();
    virtual bool isBot();
    virtual bool isMeek();
    virtual bool isRandom();
    virtual std::string getName();
    void joinGame(Game *game);
    virtual void clearHand();
    virtual void setBet(int bet);
    virtual int getBet();
    void setBankroll(int num);
    virtual int getBankRoll();
    virtual void printBankroll();
    virtual void calPoints();
    virtual Card hit();
    virtual void strategy() = 0;
};

class Human : public Player {
   public:
    Human(std::string n, int ba);
    virtual ~Human();
    virtual void strategy();
};

class Dealer : public Player {
   public:
    Dealer();
    virtual ~Dealer();
    virtual void strategy();
};

class Meek : public Player {
   public:
    Meek(int ba);
    virtual ~Meek();
    virtual void strategy();
};

class Random : public Player {
   public:
    Random(int ba);
    virtual ~Random();
    virtual void setBet(int bet);
    virtual void strategy();
};

class Game {
   private:
    Cards *cards;
    std::vector<Player *> players;

   public:
    void joinPlayer(Player *p);
    Card draw();
    void GameHandle();
};
