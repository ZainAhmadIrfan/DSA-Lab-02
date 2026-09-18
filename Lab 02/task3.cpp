// Task 3: Static (fixed-size) two-dimensional array accessed through a row pointer.
// A shop records sales for two branches across three days.

#include <iostream>
using namespace std;

int main() {
    const int ROWS = 2;   // branches
    const int COLS = 3;   // days
    int sales[ROWS][COLS];
    int (*rowPtr)[COLS] = sales;   // rowPtr points to a whole row of COLS ints

    // 1. Read the six non-negative values, row by row (branch by branch)
    cout << "Enter sales for " << ROWS << " branches across " << COLS << " days (row by row):\n";
    for (int r = 0; r < ROWS; r++) {
        cout << "Branch " << (r + 1) << ":\n";
        for (int c = 0; c < COLS; c++) {
            cout << "  Day " << (c + 1) << ": ";
            cin >> *(*(rowPtr + r) + c);
        }
    }

    // Display the two-row table
    cout << "\nSales table:\n";
    for (int r = 0; r < ROWS; r++) {
        cout << "Branch " << (r + 1) << ": ";
        for (int c = 0; c < COLS; c++) {
            cout << *(*(rowPtr + r) + c) << " ";
        }
        cout << "\n";
    }

    // 2. Branch totals (row totals) - separate loop, total reset per branch
    cout << "\nBranch totals:\n";
    for (int r = 0; r < ROWS; r++) {
        int branchTotal = 0;
        for (int c = 0; c < COLS; c++) {
            branchTotal += *(*(rowPtr + r) + c);
        }
        cout << "Branch " << (r + 1) << ": " << branchTotal << "\n";
    }

    // Day totals (column totals) - separate loop, total reset per day
    cout << "\nDay totals:\n";
    for (int c = 0; c < COLS; c++) {
        int dayTotal = 0;
        for (int r = 0; r < ROWS; r++) {
            dayTotal += *(*(rowPtr + r) + c);
        }
        cout << "Day " << (c + 1) << ": " << dayTotal << "\n";
    }

    return 0;
}
