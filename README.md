# Odd-Even Transposition Sort (MPI)

This project implements the **Odd-even transposition sort** algorithm using **Open MPI** in **C++**.

It was created as a part of the PRL course assignment (Parallel and Distributed Computing) at FIT VUT Brno, Summer semester 2024/2025.

---

## 📌 Task Summary

- Implement the **Odd-even transposition sort** algorithm as presented in lectures.
- The program reads a binary file `numbers` with `n` bytes (one per process).
- Each **MPI process** handles one number (byte).
- The algorithm performs `n` phases of parallel sorting (odd/even exchanges).
- The output is printed to **standard output** as:
  1. The input sequence (space-separated, in one line),
  2. The sorted sequence (each number on a new line).

---

## 📂 File Format

The file `numbers` is a **binary file** of unsigned 1-byte integers.  
Each number is in the range `[0, 255]` and stored without any separators.

Example generation (in bash):

```bash
dd if=/dev/random bs=1 count=10 of=numbers
```
## 🚀 Compilation and Run
```bash
mpic++ -o oets oets.cpp
mpirun --oversubscribe -np <number_of_processes> ./oets
```
The number of processes must match the number of bytes in the input file.

## 🛠️ Example
Input file (numbers) contains:
```bash
54 53 70 25
```
Output:
```bash
54 53 70 25
25
53
54
70
```

## ✅ Requirements
- Open MPI
- C++ compiler (e.g., g++)


## 👨‍💻 Author
- Student: Dinara Garipova (xgarip00)
- Project for: PRL – Parallel and Distributed Systems (FIT VUT)
- Semester: Summer 2024/2025