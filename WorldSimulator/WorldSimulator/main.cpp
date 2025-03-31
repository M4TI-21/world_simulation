#include <iostream>
#include <stdlib.h>
#include <vector>
#include <curses.h>
#include "defines.h"

using namespace std;

void initialize_menu(vector<vector<char>>& board) {

    string title = "World Simulation by Mateusz Hann - 203308";

    for (int i = 0; i < title.length(); i++) {
        board[0][i] = title[i];
    }

    for (int i = 0; i < WINDOW_W; i++) {
        board[1][i] = '~';
        board[WINDOW_H - 1][i] = '~';
    }
    for (int j = 1; j < WINDOW_H; j++) {
        board[j][5] = '|';
        board[j][WINDOW_W - 45] = '|';
    }
}

void print_game(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell;
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> board(WINDOW_H, vector<char>(WINDOW_W, ' '));
    initialize_menu(board);
    print_game(board);

    bool game_end = false;
    while (!game_end) {

    }
    return 0;
}