// Task 5: Expanding a dynamic array by allocating a new block, copying, and releasing the old one.
// A new student joins after the marks have already been entered.

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of existing marks (1-10): ";
    cin >> n;
    if (n < 1 || n > 10) {
        cout << "Error: n must be between 1 and 10. No allocation performed.\n";
        return 0;
    }

    int* marks = new int[n];
    cout << "Enter " << n << " marks:\n";
    for (int i = 0; i < n; i++) {
        cout << "Mark " << (i + 1) << ": ";
        cin >> *(marks + i);
    }

    // 1. Allocate a second block of n + 1 integers, copy the original values, read the new mark
    int* bigger = new int[n + 1];
    for (int i = 0; i < n; i++) {
        *(bigger + i) = *(marks + i);
    }
    cout << "Enter the new student's mark: ";
    cin >> *(bigger + n);

    // 2. Release the old block; make the original pointer refer to the new block; update size
    delete[] marks;
    marks = bigger;
    bigger = nullptr;   // avoid keeping a second pointer to the same block
    n = n + 1;

    cout << "\nAll marks after adding the new student:\n";
    for (int i = 0; i < n; i++) {
        cout << *(marks + i) << " ";
    }
    cout << "\n";

    // 3. Release the final block exactly once
    delete[] marks;
    marks = nullptr;

    // Explanation (also discussed in the report):
    // Changing the variable n alone does not increase the old block's capacity because n is just
    // an int holding a count; it has no lasting connection to the size that was fixed the moment
    // new int[n] originally ran. The heap manager reserved exactly that many ints for that one
    // allocation, and that reservation is a fixed, separate block of memory that cannot grow in
    // place. Holding more elements therefore requires allocating a new, larger block and copying
    // the existing data into it, which is exactly what this program does; the old block is then
    // freed, and any other pointer still referring to it would become dangling.

    return 0;
}
