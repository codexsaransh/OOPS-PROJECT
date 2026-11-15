# Campus Store Management System

## Project Overview

This project demonstrates the impact of programming paradigms on software development efficiency through a Campus Store Management System.

Two implementations are provided:

1. Procedural Programming using C.
2. Object-Oriented Programming using C++.

Both implementations address the same store-management requirements so that their design, organization, maintainability and extensibility can be compared.

## Technology Stack

| Component | Technology |
|---|---|
| Procedural implementation | C |
| OOP implementation | C++ |
| Compiler | GCC / G++ |
| Standard C | C11 |
| Standard C++ | C++17 |
| Editor | Visual Studio Code |
| Version control | Git and GitHub |

## Project Structure

```text
OOPS assignment/
│
├── procedural/
│   ├── main.c
│   └── README_Procedural.md
│
├── oop/
│   ├── main.cpp
│   └── README_OOP.md
│
├── tests/
│   └── test_cases.txt
│
├── docs/
│   ├── PROJECT_DOCUMENTATION.md
│   ├── DESIGN.md
│   ├── TESTING.md
│   └── COMPARISON.md
│
├── README.md
└── .gitignore
$ErrorActionPreference = "Stop"

# Create folders
New-Item -ItemType Directory -Force procedural, oop, tests, docs | Out-Null

# ROOT README
@'
# Campus Store Management System

A comparative study of Procedural Programming and Object-Oriented Programming.

## Implementations
- Procedural: C (C11)
- Object-Oriented: C++ (C++17)

## Features
- Product registration and validation
- Unique product IDs
- Book, Accessory and Stationery categories
- Category-based pricing
- Percentage discounts
- Percentage discount with flat coupon
- Bill generation and addition
- Product auditing
- Automated tests

## Pricing Rules

| Category | Formula | Example |
|---|---|---|
| Book | Base price * 0.90 | 500 = 450 |
| Accessory | Base price * 1.05 | 800 = 840 |
| Stationery | Base price * 0.95 | 200 = 190 |

## Sample Billing
- Book after 10% discount: Rs. 405
- Accessory after 10% discount and Rs. 20 coupon: Rs. 736
- Grand Total: Rs. 1141

## Compilation

Procedural C:
gcc -std=c11 -Wall -Wextra procedural/main.c -o procedural/procedural.exe -lm

Native OOP C++:
g++ -std=c++17 -Wall -Wextra oop/main.cpp -o oop/oop.exe

## Project Structure

- procedural/main.c
- procedural/README_Procedural.md
- oop/main.cpp
- oop/README_OOP.md
- tests/test_cases.txt
- docs/PROJECT_DOCUMENTATION.md
- docs/DESIGN.md
- docs/TESTING.md
- docs/COMPARISON.md

## OOP Concepts
Classes, objects, constructors, destructors, encapsulation, inheritance, polymorphism, function overloading, friend functions, operator overloading and static members are implemented natively in C++.

C uses structures and functions and does not natively support these OOP features.
