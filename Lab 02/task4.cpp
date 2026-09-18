// Task 4: Dynamic two-dimensional array (array of row pointers) sized at runtime.
// A teacher records marks for a group whose number of students and subjects are entered at runtime.

#include <iostream>
using namespace std;

int main() {
    int rows, cols;

    // Read and validate rows and cols BEFORE any allocation
    cout << "Enter number of students, rows (1-10): ";
    cin >> rows;
    if (rows < 1 || rows > 10) {
        cout << "Error: number of students must be between 1 and 10. No allocation performed.\n";
        return 0;
    }

    cout << "Enter number of subjects, cols (1-10): ";
    cin >> cols;
    if (cols < 1 || cols > 10) {
        cout << "Error: number of subjects must be between 1 and 10. No allocation performed.\n";
        return 0;
    }

    // Allocate an array of row pointers, then allocate each row separately
    int** marks = new int*[rows];
    for (int r = 0; r < rows; r++) {
        marks[r] = new int[cols];
    }

    // Read marks (0-100), using *(*(marks + r) + c) for input
    cout << "Enter marks (0-100) for " << rows << " student(s) and " << cols << " subject(s):\n";
    for (int r = 0; r < rows; r++) {
        cout << "Student " << (r + 1) << ":\n";
        for (int c = 0; c < cols; c++) {
            cout << "  Subject " << (c + 1) << ": ";
            cin >> *(*(marks + r) + c);
        }
    }

    // Display the matrix using pointer notation
    cout << "\nMarks matrix:\n";
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout << *(*(marks + r) + c) << " ";
        }
        cout << "\n";
    }

    // Calculate each student's total; keep the first student on a tie
    int bestTotal = 0;
    int bestStudent = 1;
    cout << "\nStudent totals:\n";
    for (int r = 0; r < rows; r++) {
        int studentTotal = 0;
        for (int c = 0; c < cols; c++) {
            studentTotal += *(*(marks + r) + c);
        }
        cout << "Student " << (r + 1) << ": " << studentTotal << "\n";

        if (r == 0 || studentTotal > bestTotal) {   // strictly greater keeps the first student on a tie
            bestTotal = studentTotal;
            bestStudent = r + 1;
        }
    }

    cout << "\nHighest total: Student " << bestStudent << " with total " << bestTotal << "\n";

    // Release memory: every row first, then the row-pointer array
    for (int r = 0; r < rows; r++) {
        delete[] marks[r];
    }
    delete[] marks;
    marks = nullptr;

    // Explanation (also discussed in the report):
    // If only "delete[] marks;" were executed (without first deleting each marks[r]), the array
    // of row pointers itself would be freed, but the 'rows' separately allocated integer blocks
    // that those pointers pointed to would NOT be freed. Their addresses are lost the instant the
    // pointer array is deleted, so that heap memory can never be released again - a memory leak.
    //
    // Memory sketch for 2 students x 3 subjects (see report for the drawn version):
    //
    //   marks (int**, local variable)
    //     |
    //     v
    //   [ marks[0] | marks[1] ]        <- heap: array of 2 row pointers
    //        |          |
    //        v          v
    //   marks[0] -> [ m00 | m01 | m02 ]   <- heap: row 0, 3 ints
    //   marks[1] -> [ m10 | m11 | m12 ]   <- heap: row 1, 3 ints
    //
    //   marks        = address of the row-pointer array
    //   marks[0]     = address of row 0's first int (also written *marks)
    //   marks[0][0]  = the mark value of student 1, subject 1 (also written **marks)

    return 0;
}
