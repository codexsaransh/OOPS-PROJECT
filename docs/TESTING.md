# Testing Documentation

| ID | Test | Expected Result |
|---|---|---|
| TC01 | Book pricing | 450 |
| TC02 | Accessory pricing | 840 |
| TC03 | Stationery pricing | 190 |
| TC04 | Book 10% discount | 405 |
| TC05 | Accessory 10% + 20 coupon | 736 |
| TC06 | Coupon exceeds amount | 0 |
| TC07 | Discount above 100% | Rejected |
| TC08 | Negative coupon | Rejected |
| TC09 | Negative price | Rejected |
| TC10 | Zero price | Accepted |
| TC11 | Duplicate ID | Rejected |
| TC12 | Bill addition | 1141 |

## Compile C
gcc -std=c11 -Wall -Wextra procedural/main.c -o procedural/procedural.exe -lm

## Compile C++
g++ -std=c++17 -Wall -Wextra oop/main.cpp -o oop/oop.exe

Record actual test results after execution.
