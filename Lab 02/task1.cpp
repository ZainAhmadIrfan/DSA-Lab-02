// Task 1: Static (fixed-size) one-dimensional array accessed through a pointer.
// A shop records the number of items sold over five days.

#include <iostream>
using namespace std;

int main() {
    const int SIZE = 5;
    int sales[SIZE];      // fixed-size local array
    int* p = sales;       // p points to sales[0]; p is never moved after this

    // 1. Read five non-negative values through *(p + i)
    cout << "Enter " << SIZE << " non-negative sales values (one per day):\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Day " << (i + 1) << ": ";
        cin >> *(p + i);
    }

    // Display the values and the total using pointer notation
    int total = 0;
    cout << "\nOriginal sales:\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Day " << (i + 1) << ": " << *(p + i) << "\n";
        total += *(p + i);
    }
    cout << "Total: " << total << "\n";

    // 2
    *(p + 2) += 2;

    // Display the updated values and updated total
    int updatedTotal = 0;
    cout << "\nUpdated sales (Day 3 increased by 2):\n";
    for (int i = 0; i < SIZE; i++) {
        cout << "Day " << (i + 1) << ": " << *(p + i) << "\n";
        updatedTotal += *(p + i);
    }
    cout << "Updated total: " << updatedTotal << "\n";

    return 0;
}
