# DSA Lab 02: Static and Dynamic Arrays; Pointers and Dynamic Memory Allocation

**Course:** Data Structures and Algorithms (Department of Computing, NUST SEECS)
**Student:** Zain Ahmad Irfan
**CMS ID:** 577280

This lab uses C++ to practise static and dynamic arrays, pointer arithmetic, and dynamic memory allocation with `new` and `delete[]`. It also covers 2D dynamic arrays, growing an array at runtime, and finding common memory errors.

## Contents

| File | Description |
|------|-------------|
| `task1.cpp` | Fixed-size array accessed through a pointer (shop sales for 5 days) |
| `task2.cpp` | Dynamic array whose size is chosen at runtime (student marks) |
| `task3.cpp` | Fixed-size 2D array accessed through a row pointer (2 branches × 3 days) |
| `task4.cpp` | Dynamic 2D array (marks matrix with runtime rows and columns) |
| `task5.cpp` | Expanding a dynamic array when a new student joins |
| `task6.cpp` | Corrected version of a buggy dynamic-array fragment |
| `report.pdf` / `report.html` | Lab report with test results and written answers |
| `DSA Lab 02.docx` | Submission document with code screenshots and outputs |

## Build and run

All programs are standard C++11 and compile without warnings using g++:

```bash
g++ -std=c++11 -Wall -Wextra task1.cpp -o task1
./task1
```

Replace `task1` with `task2` … `task6` to build and run the other tasks.

## Tasks

### Task 1: Fixed-size array via pointer
The program declares `int sales[5];` and `int* p = sales;`. It reads the values, displays them, adds up the total and adds 2 to Day 3, all through `*(p + i)`. The pointer `p` itself is never moved.

- `p` holds the address of `sales[0]`. `&p` is the address of the pointer variable itself. `*p` is `sales[0]`, and `*(p + 2)` is `sales[2]`.
- The valid indices are 0 to 4. `*(p + 5)` reads one element past the end of the array, which is undefined behaviour.

### Task 2: Dynamic array sized at runtime
The program checks that `n` is between 1 and 10 before allocating `int* marks = new int[n];`. It reads, displays and sums the marks with pointer notation, calculates the average as a `double` and counts the passes (marks of 50 or more). It then frees the array with `delete[] marks; marks = nullptr;`.

- The pointer `marks` and the heap block it points to are two separate objects. Setting the pointer to `nullptr` does not change the memory that was freed.
- `new int[n]` works because it allocates memory while the program runs. `int marks[n];` does not work in standard C++ because the size of a built-in array must be known at compile time.

### Task 3: Fixed-size 2D array via row pointer
The program declares `int sales[2][3];` and `int (*rowPtr)[3] = sales;`. All input, output, branch totals and day totals use `*(*(rowPtr + r) + c)`.

- `rowPtr + 1` points to the next whole row, so it moves forward by `3 × sizeof(int)` bytes.
- `int** p = sales;` is invalid. `sales` becomes a pointer to a row (`int(*)[3]`), not a pointer to a pointer.

### Task 4: Dynamic 2D array
The program checks the number of rows and columns, then allocates an array of row pointers (`new int*[rows]`) and a separate block of `cols` integers for each row. It finds the student with the highest total, and on a tie the first student wins. When it finishes, it frees each row first and then the array of row pointers.

- If only `delete[] marks;` ran, the row blocks would never be freed, causing a memory leak.

```
marks (int**, stack)
   |
   v
[ marks[0] | marks[1] ]          <- heap: array of row pointers
     |          |
     v          v
[ m00 | m01 | m02 ]  [ m10 | m11 | m12 ]   <- heap: one block per student
```

### Task 5: Expanding a dynamic array
The program allocates a new block of `n + 1` integers and copies the old values into it. It reads the new mark into the last position, frees the old block, points `marks` at the new block and updates `n`. The final block is freed exactly once.

- Changing `n` only changes a number. The old heap block cannot grow in place, so a larger block has to be allocated and the data copied into it.

### Task 6: Diagnosing a buggy fragment
The buggy fragment had three errors:

1. **Off-by-one loop:** `i <= n` writes to `values[n]`, which is out of bounds. The fix is `i < n`.
2. **Mismatched deallocation:** the fragment used `delete values;` on an array created with `new int[n]`. The fix is `delete[] values;`.
3. **Use after free:** `values[0]` is read after the memory has been freed. The fix is to print before freeing and then set the pointer to `nullptr`.

**Definitions:**

- **Out-of-bounds access:** a valid pointer is used at an index outside the memory that was reserved.
- **Dangling pointer:** a pointer still holds the address of memory that has already been freed.
- **Memory leak:** allocated memory can no longer be reached from any pointer, so it can never be freed.

A run that looks successful does not prove the memory access is valid. Undefined behaviour does not always crash, so tools such as sanitizers or Valgrind are needed to confirm the code is correct.

## Test summary

| Task | Test input | Result |
|------|------------|--------|
| 1 | 10 20 30 40 50 | Total 150; after the update 152 ✅ |
| 2 | n = 4; 40 50 70 81 | Total 241, average 60.25, 3 passes ✅ |
| 2 | n = 0 | Error message shown; nothing allocated ✅ |
| 3 | 2 4 6 / 1 3 5 | Branch totals 12, 9; day totals 3, 7, 11 ✅ |
| 4 | 2×3: 50 60 70 / 80 40 90 | Totals 180, 210; top student 2 ✅ |
| 4 | 2×2: 40 60 / 50 50 | Tie; top student 1 ✅ |
| 5 | 45 60 75 + 90 | 45 60 75 90 ✅ |
| 6 | 4 5 6 | Values: 4 5 6; memory freed correctly ✅ |
