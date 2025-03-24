#ifndef BINGO_H
#define BINGO_H

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <random>
#include <cstdlib> 

using namespace std;

class BingoCard {
private:
    vector<vector<int>> card;  // Cartao 5x5 com numeros unicos
    vector<vector<bool>> marked;  // Marcacao dos numeros
public:
    BingoCard(set<int>& availableNumbers);
    void markNumber(int num);
    bool checkBingo() const;
    void printCard() const;
};

class BingoGame {
private:
    vector<BingoCard> cards;
    set<int> drawnNumbers;
    vector<int> numberPool;
public:
    BingoGame();
    void drawNumber();
    void playGame();
};

#endif
