// Task 6: Corrected version of the buggy fragment.
//
// Original fragment (for reference - do NOT run, kept here only for the report):
//
//     int n = 3;
//     int* values = new int[n];
//     for (int i = 0; i <= n; i++)
//         cin >> values[i];
//     delete values;
//     cout << values[0];
//
// Three errors in the original fragment:
//   1. "i <= n" loops for i = 0,1,2,3 (4 iterations), but values[] only has valid indices 0..2
//      (n = 3 elements). Writing to values[3] writes past the end of the allocated block -
//      an out-of-bounds write. Consequence: undefined behaviour; it can silently corrupt
//      unrelated heap memory or crash, and the damage may not show up until later.
//   2. "delete values;" releases an array allocated with new int[n] (array form) using the
//      single-object delete instead of delete[]. Consequence: mismatched new[]/delete[] is
//      undefined behaviour; it can corrupt the heap allocator's bookkeeping, causing crashes
//      or corruption elsewhere that are hard to trace back to this line.
//   3. "cout << values[0];" runs AFTER delete values; has already freed the block, so values
//      is a dangling pointer at that point and values[0] reads freed memory. Consequence:
//      undefined behaviour; the printed value is unpredictable, and in a larger program that
//      memory could already have been reused by something else.

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

// Distinguishing the three problems (also discussed in the report):
// - Out-of-bounds access: using a still-valid pointer/array but at an index outside the memory
//   that was actually reserved (e.g. values[3] above). The pointer is fine; the offset is not.
// - Dangling pointer: a pointer that still holds the address of memory that has already been
//   freed (or gone out of scope); dereferencing it accesses memory the program no longer owns.
// - Memory leak: allocated memory that is never freed because every pointer to it is lost
//   (overwritten or goes out of scope) before delete[]/delete is called; the memory stays
//   reserved but the program can never reach or release it again.
//
// Why an apparently successful run does not prove the memory accesses were valid:
// Undefined behaviour is not guaranteed to crash or to produce visibly wrong output. An
// out-of-bounds write or a dangling-pointer read may, by chance, land on memory that currently
// holds a plausible-looking value, or on memory the allocator has not yet reused, so the program
// can appear to "work" on a given run, compiler, or machine. The C++ standard makes no promises
// about what happens in these cases, so correctness cannot be confirmed just by observing one
// successful-looking run; only careful reasoning about the code (or tools such as sanitizers or
// Valgrind) can confirm that every access is within bounds and to memory that is still alive.
