#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <random>
#include <algorithm>
using namespace std;


class SudokuSolver {
public:
    // Helper function to check if a number can be placed in a cell
    bool isValidPlacement(const vector<vector<int>>& board, int number, int row, int col) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == number || board[i][col] == number ||
                board[row - row % 3 + i / 3][col - col % 3 + i % 3] == number) {
                return false;
            }
        }
        return true;
    }

    // Helper function to solve a board (backtracking)
    bool solveBoard(vector<vector<int>>& board) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    for (int num = 1; num <= 9; num++) {
                        if (isValidPlacement(board, num, row, col)) {
                            board[row][col] = num;
                            if (solveBoard(board)) return true;
                            board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    // Generate a fully solved board
    vector<vector<int>> generateSolvedBoard() {
        vector<vector<int>> board(9, vector<int>(9, 0));
        random_device rd;
        mt19937 gen(rd());
        vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int i = 0; i < 9; i++) {
            shuffle(numbers.begin(), numbers.end(), gen);
            for (int j = 0; j < 9; j++) {
                if (isValidPlacement(board, numbers[j], i, j)) {
                    board[i][j] = numbers[j];
                }
            }
        }

        solveBoard(board);
        return board;
    }

    // Generate a random valid Sudoku board
    vector<vector<int>> generateBoard(int clues = 30) {
        auto board = generateSolvedBoard();
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(0, 8);

        int cellsToRemove = 81 - clues;
        while (cellsToRemove > 0) {
            int row = dist(gen);
            int col = dist(gen);

            if (board[row][col] != 0) {
                board[row][col] = 0;
                cellsToRemove--;
            }
        }

        return board;
    }
};


vector<vector<int>> loadBoardFromFile(const string& filename) {
    ifstream infile(filename);
    vector<vector<int>> board(9, vector<int>(9));

    if (!infile) throw runtime_error("Could not open file: " + filename);

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            infile >> board[i][j];
        }
    }
    return board;
}

void saveBoardToFile(const string& filename, const vector<vector<int>>& board) {
    ofstream outfile(filename);

    if (!outfile) throw runtime_error("Could not write to file: " + filename);

    for (const auto& row : board) {
        for (const auto& cell : row) {
            outfile << cell << ' ';
        }
        outfile << '\n';
    }
}

bool compareBoards(const vector<vector<int>>& board1, const vector<vector<int>>& board2) {
    return board1 == board2;
}


void printComparison(const vector<vector<int>>& unsolved, const vector<vector<int>>& solved) {
    cout << "Unsolved Board                    Solved Board\n";
    cout << "---------------------             ---------------------\n";

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // Print unsolved board cell
            if (unsolved[row][col] == 0) {
                cout << ". ";
            } else {
                cout << unsolved[row][col] << " ";
            }

            if (col % 3 == 2 && col != 8) {
                cout << "| ";
            }
        }

        cout << "    -->     "; // Space between the boards

        for (int col = 0; col < 9; col++) {
            // Print solved board cell
            cout << solved[row][col] << " ";
            if (col % 3 == 2 && col != 8) {
                cout << "| ";
            }
        }

        cout << '\n';

        if (row % 3 == 2 && row != 8) {
            cout << "---------------------             ---------------------\n";
        }
    }

    cout << '\n';
}



int main() {
    SudokuSolver solver;
    string testDir = "tests";

    for (const auto& entry : filesystem::directory_iterator(testDir)) {
        string path = entry.path().string();

        if (path.ends_with(".in")) {
            string outFile = path.substr(0, path.size() - 3) + ".out";
            cout << "Processing: " << path << '\n';

            try {
                auto unsolvedBoard = loadBoardFromFile(path);
                auto solvedBoard = unsolvedBoard;

                if (solver.solveBoard(solvedBoard)) {
                    printComparison(unsolvedBoard, solvedBoard);
                } else {
                    cout << "This board cannot be solved.\n";
                }
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << '\n';
            }

            cout << "=======================================================\n\n";
        }
    }

    return 0;
}
