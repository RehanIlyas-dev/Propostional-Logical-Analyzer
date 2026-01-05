# Logical Expression Analyzer

## Project Overview
This is a C++ console application designed to analyze logical propositions. It allows users to input logical expressions, generates truth tables for up to 10 variables, and evaluates the logical status of the statements (Tautology, Contradiction, or Contingency).

This project was developed as a first-semester programming assignment to demonstrate proficiency in C++ logic, array manipulation, and recursive parsing.

## Features
* **Truth Table Generation:** Automatically detects variables and generates a full truth table ($2^n$ rows).
* **Expression Evaluation:** Parses and solves complex boolean expressions respecting operator precedence (with parentheses support).
* **Single Mode:** Analyzes one expression to determine if it is a Tautology, Contradiction, or Contingency.
* **Comparison Mode:** Analyzes two expressions simultaneously to check for **Logical Equivalence**.
* **Supported Operators:**
    * `!` or `~` : NOT
    * `&` : AND
    * `|` : OR
    * `^` : XOR
    * `>` : IMPLICATION ($P \rightarrow Q$)
    * `=` : BICONDITIONAL ($P \leftrightarrow Q$)

## Directory Structure
```text
Logical_Analyzer_Project/
│
├── main.cpp                  # Source code
├── README.md                 # Project documentation
├── tests/                    # Text descriptions of test cases
│   ├── test_case_01.txt
│   └── test_case_02.txt
└── data/                     # Sample input files for automated testing
    ├── input_single.txt
    └── input_double.txt
