#include "Bingo1.h"

BingoCard::BingoCard(set<int>& availableNumbers) : card(5, vector<int>(5)), marked(5, vector<bool>(5, false)) {
    vector<int> columnNumbers;
    
    for (int col = 0; col < 5; ++col) {
        columnNumbers.clear();
        for (int i = 0; i < 15; ++i) {
            int num = col * 15 + i + 1;
            if (availableNumbers.count(num)) columnNumbers.push_back(num);
        }
        shuffle(columnNumbers.begin(), columnNumbers.end(), default_random_engine(random_device{}()));

        for (int row = 0; row < 5; ++row) {
            if (row == 2 && col == 2) {
                card[row][col] = 0; // Espaço livre
                marked[row][col] = true;
            } else {
                card[row][col] = columnNumbers[row];
                availableNumbers.erase(columnNumbers[row]); // Remove para evitar repetição entre cartões
            }
        }
    }
}

void BingoCard::markNumber(int num) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (card[i][j] == num) marked[i][j] = true;
}

bool BingoCard::checkBingo() const {
    for (int i = 0; i < 5; ++i)
        if (all_of(marked[i].begin(), marked[i].end(), [](bool v) { return v; })) return true;

    for (int i = 0; i < 5; ++i) {
        bool columnBingo = true;
        for (int j = 0; j < 5; ++j)
            if (!marked[j][i]) columnBingo = false;
        if (columnBingo) return true;
    }

    bool diagonal1 = true, diagonal2 = true;
    for (int i = 0; i < 5; ++i) {
        if (!marked[i][i]) diagonal1 = false;
        if (!marked[i][4 - i]) diagonal2 = false;
    }

    return diagonal1 || diagonal2;
}

void BingoCard::printCard() const {
    cout << "B  I  N  G  O\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (card[i][j] == 0) 
                cout << " *  ";  // Espaço livre no centro
            else if (marked[i][j]) 
                cout << "[X] ";  // Número marcado
            else 
                cout << (card[i][j] < 10 ? " " : "") << card[i][j] << "  ";  // Número normal
        }
        cout << endl;
    }
    cout << endl;
}

BingoGame::BingoGame() {
    for (int i = 1; i <= 75; ++i) numberPool.push_back(i);
    shuffle(numberPool.begin(), numberPool.end(), default_random_engine(random_device{}()));

    set<int> availableNumbers(numberPool.begin(), numberPool.end());
    for (int i = 0; i < 3; ++i)
        cards.emplace_back(availableNumbers);
}

void BingoGame::drawNumber() {
    if (numberPool.empty()) {
        cout << "Todos os números já foram sorteados!" << endl;
        return;
    }

    int num = numberPool.back();
    numberPool.pop_back();
    drawnNumbers.insert(num);
    cout << "Numero sorteado: " << num << endl;

    for (auto& card : cards) {
        card.markNumber(num);
        card.printCard();
        if (card.checkBingo()) {
            cout << "BINGO!" << endl;
            exit(0);
        }
    }
}

void BingoGame::playGame() {
    while (!numberPool.empty()) {
        cout << "Deseja sortear um número? (S/N): ";
        char escolha;
        cin >> escolha;

        if (escolha == 'N' || escolha == 'n') {
            cout << "Jogo encerrado." << endl;
            return;
        } else if (escolha != 'S' && escolha != 's') {
            cout << "Opção inválida! Digite S para continuar ou N para sair." << endl;
            continue;
        }

        drawNumber();
    }

    cout << "Fim do jogo! Todos os números foram sorteados." << endl;
}
