#ifndef BINGO_H
#define BINGO_H

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

class BingoCard {
private:
    vector<vector<int>> card;  // Cartão 5x5 com números únicos
    vector<vector<bool>> marked;  // Marcações dos números
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
