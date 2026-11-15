# Project Documentation

## Problem Statement
Develop a Campus Store Management System supporting product registration, category pricing, discounts, coupons, billing and auditing.

## Objectives
- Implement the same requirements in C and C++.
- Compare procedural and object-oriented programming.
- Demonstrate maintainability and extensibility.
- Test pricing and billing operations.

## Product Categories
Book: 90% of base price.
Accessory: 105% of base price.
Stationery: 95% of base price.

## Discount Rules
Percentage discount is applied first.
Flat coupon is subtracted afterward.
Final payable amount cannot be negative.

## Sample Results
Book: 500 -> 450 -> 405.
Accessory: 800 -> 840 -> 756 -> 736.
Stationery: 200 -> 190 -> 171.

## Implementation
Procedural implementation uses C structures and functions.
OOP implementation uses native C++ classes and OOP concepts.

## Expected Result
Both programs should produce equivalent pricing and billing results.
