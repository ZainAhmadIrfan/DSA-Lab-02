// Task 6: Corrected version of the buggy fragment.

#include <iostream>
using namespace std;

int main() {
    int n = 3;
    int* values = new int[n];

    // Fix 1: loop bound corrected to i < n (valid indices are 0..n-1)
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; i++)
        cin >> values[i];

    // Display all three integers WHILE the memory is still valid (before delete)
    cout << "Values: ";
    for (int i = 0; i < n; i++)
        cout << values[i] << " ";
    cout << "\n";

    // Fix 2: use delete[] to match new[]
    delete[] values;
    // Fix 3: reset the pointer after release so it can no longer be dereferenced by mistake
    values = nullptr;

    return 0;
}