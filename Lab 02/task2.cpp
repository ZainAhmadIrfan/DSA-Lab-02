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

    // Explanation (also discussed in the report):
    // 'marks' (the pointer variable) and the allocated block of n ints are two different objects.
    // 'marks' is a local variable that only stores an address; the block on the heap is the
    // memory new int[n] reserved. delete[] frees the heap block; setting marks = nullptr merely
    // changes what address the local variable holds afterwards - it does not undo the deletion,
    // and it has no effect on any other pointer that might still hold a copy of the old address.
    //
    // int marks[n]; is not a standard fixed-size array declaration when n is a runtime variable
    // because C++ requires the size of a built-in (automatic) array to be a compile-time constant,
    // so the compiler can reserve a fixed amount of stack space before the program even runs.
    // new int[n] instead requests memory from the heap while the program is running, so n may be
    // any value computed at runtime.

    return 0;
}
