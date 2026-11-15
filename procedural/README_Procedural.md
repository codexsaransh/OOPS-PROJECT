# Campus Store Management System
### Procedural Programming Implementation

**Maharaja Surajmal Institute of Technology**  
Department of Information Technology  
Subject: Object-Oriented Programming (OOPS)  
Project: OOPS Case Study Assignment

---

## 1. Project Overview

The Campus Store Management System is a C++ application developed using the procedural programming approach.

The system simulates a college store that sells books, accessories and stationery. It handles product registration, category-based pricing, discounts, coupon calculations, billing and product auditing.

This implementation serves as the procedural baseline for comparing software development efficiency with an Object-Oriented Programming implementation.

## 2. Objectives

- Understand procedural programming using C++.
- Implement product management using structures.
- Perform category-specific price calculations.
- Implement percentage-based discounts.
- Support additional coupon discounts.
- Generate customer bills.
- Validate product information.
- Perform product auditing.
- Test program correctness using automated test cases.

## 3. Technologies Used

| Technology | Purpose |
|---|---|
| C++ | Programming language |
| GCC | C++ compiler |
| C++17 | Language standard |
| Visual Studio Code | Development environment |
| Git | Version control |
| GitHub | Team collaboration |

## 4. Project Structure

```text
CampusStore/
│
├── procedural/
│   └── main.cpp
│
├── oop/
│   └── main.cpp
│
├── tests/
│   └── test_cases.txt
│
├── docs/
│
├── README.md
└── README_PROCEDURAL.md
```

## 5. Functional Features

### Product Management
- Register products using structures.
- Store product ID, name, base price and category.
- Prevent duplicate product IDs.
- Reject negative product prices.

### Product Categories

| Category | Pricing Rule |
|---|---|
| Book | 10% reduction |
| Accessory | 5% increase |
| Stationery | 5% reduction |

### Discount Management

The system supports:

1. Percentage-based discounts.
2. Percentage discounts combined with flat coupons.
3. Prevention of negative payable amounts.
4. Validation of discount percentages.

### Billing System

The billing system calculates individual product amounts and generates the combined bill.

### Product Auditing

The audit function displays:
- Product ID
- Product name

## 6. Pricing Calculations

The following sample products are used:

| Product | Base Price | Category Price |
|---|---:|---:|
| C++ Textbook | ₹500 | ₹450 |
| USB Mouse | ₹800 | ₹840 |
| Pen Set | ₹200 | ₹190 |

### Discount Calculations

| Product | Calculation | Final Amount |
|---|---|---:|
| Book | ₹450 - 10% | ₹405 |
| Accessory | ₹840 - 10% - ₹20 coupon | ₹736 |
| Stationery | ₹190 - 10% | ₹171 |

**Combined Book and Accessory Bill: ₹1,141**

## 7. Functions Implemented

| Function | Responsibility |
|---|---|
| `isValidPrice()` | Validates product prices |
| `isUniqueID()` | Checks duplicate product IDs |
| `registerProduct()` | Registers products |
| `finalPrice()` | Calculates category-specific prices |
| `discount()` | Calculates percentage discounts |
| `couponDiscount()` | Calculates percentage and coupon discounts |
| `auditProduct()` | Displays product audit information |
| `displayProduct()` | Displays product details |
| `calculateBill()` | Calculates combined bill |
| `runTests()` | Executes automated test cases |
| `testResult()` | Displays test results |

## 8. Automated Testing

The implementation includes automated tests for:

1. Book category pricing.
2. Accessory category pricing.
3. Stationery category pricing.
4. Percentage discount calculation.
5. Percentage discount with coupon.
6. Coupon greater than payable amount.
7. Invalid discount percentage.
8. Negative price validation.
9. Bill addition.
10. Product registration.
11. Duplicate product ID rejection.
12. Invalid category rejection.

Expected result:

```text
Tests Passed: 12
Tests Failed: 0
```

## 9. Compilation and Execution

### Compile

Open the terminal in the project root directory.

```bash
g++ -std=c++17 procedural/main.cpp -o procedural.exe
```

### Execute

Windows PowerShell:

```powershell
.\procedural.exe
```

## 10. Advantages of Procedural Programming

- Simple program structure.
- Easy-to-understand functions.
- Direct execution flow.
- Suitable for smaller applications.
- Straightforward implementation of individual operations.

## 11. Limitations

- Product categories require modifications to existing pricing logic.
- As requirements grow, functions can become more complex.
- Data and operations are maintained separately.
- Extending the application may require changes across multiple functions.

## 12. Conclusion

The procedural implementation successfully demonstrates the basic functionality of the Campus Store Management System.

It provides a working baseline for evaluating the impact of Object-Oriented Programming on software development efficiency, code reuse, maintainability and future modifications.

The actual comparison will be based on measured development time, change effort, code modifications and test results.

---

**Project:** Campus Store Management System  
**Implementation:** Procedural Programming  
**Language:** C++  
**Institution:** Maharaja Surajmal Institute of Technology