// Task 2: Dynamic one-dimensional array sized at runtime.
// A teacher does not know the number of students until the program runs.

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of students (1-10): ";
    cin >> n;

    // Validate n before allocating anything
    if (n < 1 || n > 10) {
        cout << "Error: n must be between 1 and 10. No allocation or mark input performed.\n";
        return 0;
    }

    // 1. Allocate and read n marks (0-100) using pointer notation
    int* marks = new int[n];
    cout << "Enter " << n << " marks (0-100):\n";
    for (int i = 0; i < n; i++) {
        cout << "Student " << (i + 1) << ": ";
        cin >> *(marks + i);
    }

    // 2. Display marks, total, average and pass count using pointer notation
    cout << "\nMarks:\n";
    int total = 0;
    int passCount = 0;
    for (int i = 0; i < n; i++) {
        cout << "Student " << (i + 1) << ": " << *(marks + i) << "\n";
        total += *(marks + i);
        if (*(marks + i) >= 50) passCount++;
    }

    double average = static_cast<double>(total) / n;  // keeps the fractional part

    cout << "Total: " << total << "\n";
    cout << "Average: " << average << "\n";
    cout << "Pass count (>= 50): " << passCount << "\n";

    // 3. Release the array
    delete[] marks;
    marks = nullptr;

    return 0;
}
