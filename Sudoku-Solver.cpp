#include <iostream>
#include <vector>
#include <unordered_set>

#define N 9

using namespace std;

// Data structures for tracking the existing numbers in rows, columns, and subgrids
vector<unordered_set<int>> rows(N), cols(N), boxes(N);

// Function to print the Sudoku grid
void printGrid(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to find the index of the subgrid box from the row and column
int getBoxIndex(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}

// Function to check if a number can be placed at grid[row][col]
bool isSafe(int num, int row, int col) {
    int boxIndex = getBoxIndex(row, col);
    // Check if num is already in the row, column, or subgrid
    if (rows[row].count(num) || cols[col].count(num) || boxes[boxIndex].count(num)) {
        return false;
    }
    return true;
}

// Function to place the number and update the data structures
void placeNumber(int num, int row, int col, vector<vector<int>>& grid) {
    grid[row][col] = num;
    rows[row].insert(num);
    cols[col].insert(num);
    boxes[getBoxIndex(row, col)].insert(num);
}

// Function to remove a number (backtrack)
void removeNumber(int num, int row, int col, vector<vector<int>>& grid) {
    grid[row][col] = 0;
    rows[row].erase(num);
    cols[col].erase(num);
    boxes[getBoxIndex(row, col)].erase(num);
}

// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& grid, int row, int col) {
    // If we reached the last cell, return true
    if (row == N - 1 && col == N) {
        return true;
    }

    // Move to the next row if we are at the end of a column
    if (col == N) {
        row++;
        col = 0;
    }

    // If the current cell is not empty, move to the next cell
    if (grid[row][col] != 0) {
        return solveSudoku(grid, row, col + 1);
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(num, row, col)) {
            placeNumber(num, row, col, grid);

            // Recursively try to solve the rest of the grid
            if (solveSudoku(grid, row, col + 1)) {
                return true;
            }

            // If the number can't solve the puzzle, backtrack
            removeNumber(num, row, col, grid);
        }
    }

    // Trigger backtracking
    return false;
}

// Initialize the data structures based on the initial grid state
void initializeSets(const vector<vector<int>>& grid) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int num = grid[row][col];
            if (num != 0) {
                rows[row].insert(num);
                cols[col].insert(num);
                boxes[getBoxIndex(row, col)].insert(num);
            }
        }
    }
}

int main() {
    // Example Sudoku grid (0 represents empty cells)
    vector<vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    // Initialize sets with the given grid
    initializeSets(grid);

    // Solve the Sudoku and print the result
    if (solveSudoku(grid, 0, 0)) {
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}
