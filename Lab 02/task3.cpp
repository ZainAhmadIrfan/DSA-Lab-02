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

    // 3. Explanation (also discussed in the report):
    // rowPtr + 1 points to the next whole row of the array, i.e. the address of sales[1][0],
    // treated as a block of COLS (3) ints. Advancing rowPtr by 1 therefore moves the address
    // forward by sizeof(int[3]) = 3 * sizeof(int) bytes, whereas advancing a plain int* by 1
    // only moves it forward by sizeof(int) bytes (one integer). rowPtr's step is 3 times larger
    // because the compiler must know the row length in order to skip a whole row at a time.
    //
    // int** p = sales; must not be used: sales is a genuine 2D array, stored as ONE contiguous
    // block of ROWS*COLS ints, and its name decays to a pointer to its first row (int(*)[COLS]),
    // not to a pointer-to-pointer. An int** is meant to point at a separately stored int*, which
    // does not exist here. The declaration would not even compile due to the type mismatch, and
    // forcing it with a cast would misinterpret the row-major layout and produce wrong addresses.

    return 0;
}
