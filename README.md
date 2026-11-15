# CAMPUS STORE MANAGEMENT SYSTEM

## MAHARAJA SURAJMAL INSTITUTE OF TECHNOLOGY
Department of Information Technology

Subject: Object Oriented Programming

## Project Description

This project demonstrates the impact of Object-Oriented
Programming on software development efficiency.

Two implementations are developed:

1. Procedural Programming
2. Object-Oriented Programming

Both systems perform equivalent store management operations.

## Functional Features

- Product registration
- Unique product IDs
- Product categories
- Category-specific pricing
- Percentage discounts
- Coupon discounts
- Customer billing
- Bill addition
- Product auditing
- Input validation
- Product object counting

## Product Pricing

Book:
Base Price x 0.90

Accessory:
Base Price x 1.05

Stationery:
Base Price x 0.95

## OOP Concepts

1. Classes and Objects
2. Constructors
3. Function Overloading
4. Friend Functions
5. Operator Overloading
6. Inline Functions
7. Inheritance
8. Static Data Members
9. Non-static Data Members

## Project Structure

CampusStore/
|
|-- procedural/
|   |-- main.cpp
|
|-- oop/
|   |-- main.cpp
|
|-- tests/
|   |-- test_cases.txt
|
|-- docs/
|
|-- README.md
|-- .gitignore

## Compilation

Procedural:
g++ -std=c++17 procedural/main.cpp -o procedural.exe

OOP:
g++ -std=c++17 oop/main.cpp -o oop.exe

## Expected Results

Book after discount: Rs.405

Accessory after discount and coupon: Rs.736

Stationery after discount: Rs.171

Combined bill: Rs.1141

## Conclusion

The project compares procedural and object-oriented
programming using a common campus store scenario.

OOP provides inheritance, encapsulation and polymorphism,
which can make future extensions easier to maintain.

However, initial development effort and actual change
effort must be measured to establish the advantages.
