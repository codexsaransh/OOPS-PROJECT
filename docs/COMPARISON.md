# Procedural C vs Object-Oriented C++

| Feature | Procedural C | OOP C++ |
|---|---|---|
| Organization | Functions | Classes |
| Data | Structures | Objects |
| Encapsulation | Manual | Native |
| Inheritance | Not native | Native |
| Polymorphism | Not native | Native |
| Function overloading | Not native | Native |
| Operator overloading | Not native | Native |
| Reusability | Functions | Classes and inheritance |

## Change Request 1: Stationery
Added Stationery with a 0.95 pricing multiplier.

In C, pricing and category validation logic are updated.
In C++, a Stationery class derives from Product.

## Change Request 2: Flat Coupon
A flat coupon is subtracted after the percentage discount.

In C, couponDiscount() handles the calculation.
In C++, discount(percent, coupon) handles the calculation.

## Measurements
Record actual files changed, functions changed, implementation time and test results. Do not invent measurements.
