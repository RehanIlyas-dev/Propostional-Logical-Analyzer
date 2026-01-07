# Propositonal Logic  Analyzer

## Project Description
The **Propositional Logic  Analyzer** is a C++ console application designed to evaluate and analyze Boolean logic. It parses complex logical expressions containing variables and standard operators (AND, OR, NOT, XOR, Implication, Biconditional) to generate comprehensive truth tables. It can determine if a statement is a Tautology, Contradiction, or Contingency, and can also compare two separate expressions to verify Logical Equivalence.

## Dependencies
This project relies on **Standard C++ Libraries** only. No external packages or downloads are required.
* **OS:** Windows is recommended (due to `system("cls")`), but it runs on Linux/Mac if `cls` is removed.
* **Compiler:** Any standard C++ compiler (GCC, Clang, MSVC).
* **Libraries used:**
  * `<iostream>`
  * `<cmath>`
  * `<limits>`

## Installation Instructions
1. **Clone or Download** this repository to your local machine.
2. Open your terminal or command prompt and navigate to the project directory.
3. Compile the source code using the following command:

   ```bash
   g++ main.cpp -o logical_analyzer
