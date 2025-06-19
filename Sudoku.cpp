#include <bits/stdc++.h>
using namespace std;

// Pretty print the board
void printBoard(const vector<vector<int>>& board, const string& label) {
    cout << "\n========================================\n";
    cout << label << "\n";
    cout << "========================================\n\n";

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Validity check
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < 9; x++)
        if (board[row][x] == num || board[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++)
        for (int j = startCol; j < startCol + 3; j++)
            if (board[i][j] == num)
                return false;

    return true;
}

// Backtracking
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solveSudoku(board))
                            return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Try to load input as 81-character string
bool parseStreamInput(const string& line, vector<vector<int>>& board) {
    string cleaned;
    for (char c : line) {
        if (isdigit(c)) cleaned += c;
    }

    if (cleaned.size() != 81) return false;

    int index = 0;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            board[i][j] = cleaned[index++] - '0';

    return true;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Could not open input.txt file.\n";
        return 1;
    }

    vector<vector<int>> board(9, vector<int>(9));
    string line;
    vector<string> lines;
    while (getline(inputFile, line)) {
        if (!line.empty())
            lines.push_back(line);
    }
    inputFile.close();

    bool parsed = false;

    if (lines.size() == 1) {
        parsed = parseStreamInput(lines[0], board);
    }

    if (!parsed && lines.size() == 9) {
        for (int i = 0; i < 9; i++) {
            stringstream ss(lines[i]);
            for (int j = 0; j < 9; j++) {
                ss >> board[i][j];
            }
        }
        parsed = true;
    }

    if (!parsed) {
        cerr << "Error: Invalid input format in input.txt\n";
        return 1;
    }

    printBoard(board, "INPUT SUDOKU");

    if (solveSudoku(board)) {
        printBoard(board, "SOLVED SUDOKU");
    } else {
        cout << "No solution exists for the given Sudoku.\n";
    }

    return 0;
}
