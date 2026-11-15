#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PRODUCTS 100

#define BOOK 1
#define ACCESSORY 2
#define STATIONERY 3

typedef struct Product Product;

struct Product {
    int id;
    char name[100];
    double basePrice;
    int category;
};

typedef struct {
    double total;
} Bill;

int liveProductCount = 0;

/* Product constructor equivalent */
Product createProduct(int id, const char *name,
                      double price, int category) {

    Product p;

    p.id = id;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    p.basePrice = price;
    p.category = category;

    liveProductCount++;

    return p;
}

/* Product cleanup equivalent */
void destroyProduct(Product *p) {
    if (p != NULL && liveProductCount > 0) {
        liveProductCount--;
    }
}

/* Inline accessor equivalent */
int getProductID(const Product *p) {
    return p->id;
}

/* Static function equivalent */
int getProductCount(void) {
    return liveProductCount;
}

/* Category-specific pricing */
double finalPrice(const Product *p) {

    switch (p->category) {

        case BOOK:
            return p->basePrice * 0.90;

        case ACCESSORY:
            return p->basePrice * 1.05;

        case STATIONERY:
            return p->basePrice * 0.95;

        default:
            return -1;
    }
}

/* Percentage discount */
double discountPercent(const Product *p, double percent) {

    double price = finalPrice(p);

    if (price < 0 || percent < 0 || percent > 100)
        return -1;

    return price * (1 - percent / 100.0);
}

/* Percentage discount with coupon */
double discountCoupon(const Product *p,
                      double percent, double coupon) {

    double amount;

    if (coupon < 0)
        return -1;

    amount = discountPercent(p, percent);

    if (amount < 0)
        return -1;

    amount -= coupon;

    return amount > 0 ? amount : 0;
}

/* Audit function */
void auditProduct(const Product *p) {

    printf("Audit: ID = %d | Name = %s\n",
           p->id, p->name);
}

/* Display product */
void displayProduct(const Product *p) {

    printf("\nProduct ID: %d", p->id);
    printf("\nProduct Name: %s", p->name);
    printf("\nBase Price: Rs. %.2f", p->basePrice);
    printf("\nCategory Price: Rs. %.2f\n",
           finalPrice(p));
}

/* Bill constructor equivalent */
Bill createBill(double amount) {

    Bill b;
    b.total = amount;
    return b;
}

/* Operator + equivalent */
Bill addBills(Bill a, Bill b) {

    Bill result;
    result.total = a.total + b.total;

    return result;
}

/* Product validation */
int isValidProduct(const Product *p) {

    return p->id > 0 &&
           p->basePrice >= 0 &&
           p->category >= BOOK &&
           p->category <= STATIONERY;
}

/* Unique ID validation */
int isUniqueID(const Product products[],
               int count, int id) {

    int i;

    for (i = 0; i < count; i++) {
        if (products[i].id == id)
            return 0;
    }

    return 1;
}

/* Floating point comparison */
int equal(double a, double b) {
    return fabs(a - b) < 0.001;
}

/* Testing */
int passed = 0;
int failed = 0;

void testResult(const char *name, int condition) {

    if (condition) {
        printf("[PASS] %s\n", name);
        passed++;
    } else {
        printf("[FAIL] %s\n", name);
        failed++;
    }
}

void runTests(void) {

    Product b = createProduct(501, "Test Book", 500, BOOK);
    Product a = createProduct(502, "Test Mouse", 800, ACCESSORY);
    Product s = createProduct(503, "Test Pen", 200, STATIONERY);

    Product list[2] = {
        {101, "Existing", 100, BOOK},
        {102, "Existing 2", 200, ACCESSORY}
    };

    Bill bill1 = createBill(405);
    Bill bill2 = createBill(736);
    Bill combined = addBills(bill1, bill2);

    printf("\n====================================\n");
    printf("             OOP C TESTS\n");
    printf("====================================\n");

    testResult("Book pricing", equal(finalPrice(&b), 450));
    testResult("Accessory pricing", equal(finalPrice(&a), 840));
    testResult("Stationery pricing", equal(finalPrice(&s), 190));

    testResult("Percentage discount",
               equal(discountPercent(&b, 10), 405));

    testResult("Percentage plus coupon",
               equal(discountCoupon(&a, 10, 20), 736));

    testResult("Coupon greater than amount",
               equal(discountCoupon(&b, 10, 500), 0));

    testResult("Invalid discount",
               equal(discountPercent(&b, 150), -1));

    testResult("Negative coupon rejection",
               equal(discountCoupon(&b, 10, -20), -1));

    testResult("Bill addition",
               equal(combined.total, 1141));

    testResult("Product validation",
               isValidProduct(&b));

    testResult("Negative price rejection",
               !isValidProduct(&(Product){504, "Invalid", -100, BOOK}));

    testResult("Zero price accepted",
               isValidProduct(&(Product){505, "Zero", 0, BOOK}));

    testResult("Unique ID validation",
               isUniqueID(list, 2, 103));

    testResult("Duplicate ID rejection",
               !isUniqueID(list, 2, 101));

    testResult("Product ID accessor",
               getProductID(&b) == 501);

    printf("\nTests Passed: %d\n", passed);
    printf("Tests Failed: %d\n", failed);

    destroyProduct(&b);
    destroyProduct(&a);
    destroyProduct(&s);

    printf("====================================\n");
}

/* Main */
int main(void) {

    Product book = createProduct(
        101, "C++ Textbook", 500, BOOK);

    Product accessory = createProduct(
        202, "USB Mouse", 800, ACCESSORY);

    Product stationery = createProduct(
        303, "Pen Set", 200, STATIONERY);

    double bookAmount;
    double accessoryAmount;
    double stationeryAmount;

    Bill bookBill;
    Bill accessoryBill;
    Bill grandTotal;

    printf("====================================\n");
    printf("    CAMPUS STORE MANAGEMENT SYSTEM\n");
    printf("       STRUCTURED C VERSION\n");
    printf("====================================\n");

    printf("\nLive Product Count: %d\n",
           getProductCount());

    printf("\n---------- PRODUCT DETAILS ----------\n");

    displayProduct(&book);
    displayProduct(&accessory);
    displayProduct(&stationery);

    bookAmount = discountPercent(&book, 10);

    accessoryAmount = discountCoupon(
        &accessory, 10, 20);

    stationeryAmount = discountPercent(
        &stationery, 10);

    printf("\n---------- DISCOUNT DETAILS ----------\n");

    printf("Book: Rs. %.2f\n", bookAmount);
    printf("Accessory: Rs. %.2f\n", accessoryAmount);
    printf("Stationery: Rs. %.2f\n", stationeryAmount);

    bookBill = createBill(bookAmount);
    accessoryBill = createBill(accessoryAmount);

    grandTotal = addBills(bookBill, accessoryBill);

    printf("\n---------- BILL GENERATION ----------\n");

    printf("Book Amount: Rs. %.2f\n", bookBill.total);
    printf("Accessory Amount: Rs. %.2f\n", accessoryBill.total);
    printf("Grand Total: Rs. %.2f\n", grandTotal.total);

    printf("\n---------- PRODUCT AUDIT ----------\n");

    auditProduct(&book);
    auditProduct(&accessory);
    auditProduct(&stationery);

    runTests();

    destroyProduct(&book);
    destroyProduct(&accessory);
    destroyProduct(&stationery);

    printf("\nRemaining Live Product Count: %d\n",
           getProductCount());

    printf("\n====================================\n");
    printf("        PROGRAM COMPLETED\n");
    printf("====================================\n");

    return 0;
}
