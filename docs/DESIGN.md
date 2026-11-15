# System Design

## Procedural C
Product data is represented using a structure. Functions handle registration, validation, pricing, discount calculation, auditing and billing.

## Object-Oriented C++
Product is the abstract base class.
Book, Accessory and Stationery inherit from Product.
Bill manages billing and overloads the + operator.

## Class Diagram

             Product
                |
       -------------------
       |        |        |
      Book  Accessory Stationery

              Bill

## Polymorphism
The virtual finalPrice() function is overridden by derived classes.

## Encapsulation
Product data members use protected and private access.

## Static Member
The Product class maintains a live object counter.

## Friend Function
auditProduct() accesses Product data through friendship.
