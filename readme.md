# **Sudoku Solver and Validator**

## **Overview**
This program is a robust Sudoku-solving tool designed to solve and validate Sudoku puzzles of varying difficulty levels. Using a recursive backtracking algorithm, the program ensures correctness and efficiency, making it capable of solving any valid Sudoku puzzle. Additionally, the program supports automated testing by reading `.in` files containing puzzles and comparing the solved output to corresponding `.out` files.

Sudoku is not only a popular puzzle game but also an excellent example of a constraint satisfaction problem, which has applications in artificial intelligence, optimization, and algorithm design.

---

## **Features**
- Solves Sudoku puzzles using a **backtracking algorithm**.
- Validates puzzles to ensure they adhere to Sudoku rules.
- Processes `.in` test files automatically and compares results against `.out` files.
- Displays the unsolved and solved boards side by side for easy comparison.
- Handles invalid or unsolvable puzzles gracefully.

---

## **Usage**

### **1. Compilation**
Use the provided `Makefile` to compile the program:
```bash
make
./solver
```