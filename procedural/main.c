#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_PRODUCTS 100

#define BOOK 1
#define ACCESSORY 2
#define STATIONERY 3

typedef struct {
    int id;
    char name[100];
    double basePrice;
    int category;
} Product;

Product products[MAX_PRODUCTS];
int productCount = 0;

int passed = 0;
int failed = 0;

/* Check whether price is valid */
int isValidPrice(double price) {
    return price >= 0;
}

/* Check unique product ID */
int isUniqueID(int id) {
    int i;

    for (i = 0; i < productCount; i++) {
        if (products[i].id == id)
            return 0;
    }

    return 1;
}

/* Register product */
int registerProduct(Product p) {

    if (p.id <= 0) {
        printf("Error: Invalid product ID.\n");
        return 0;
    }

    if (!isValidPrice(p.basePrice)) {
        printf("Error: Negative price not allowed.\n");
        return 0;
    }

    if (!isUniqueID(p.id)) {
        printf("Error: Duplicate product ID.\n");
        return 0;
    }

    if (p.category < BOOK || p.category > STATIONERY) {
        printf("Error: Invalid category.\n");
        return 0;
    }

    if (productCount >= MAX_PRODUCTS) {
        printf("Error: Product storage full.\n");
        return 0;
    }

    products[productCount++] = p;

    return 1;
}

/* Calculate category-based price */
double finalPrice(Product p) {

    switch (p.category) {

        case BOOK:
            return p.basePrice * 0.90;

        case ACCESSORY:
            return p.basePrice * 1.05;

        case STATIONERY:
            return p.basePrice * 0.95;

        default:
            return -1;
    }
}

/* Apply percentage discount */
double discount(Product p, double percent) {

    double amount;

    if (percent < 0 || percent > 100)
        return -1;

    amount = finalPrice(p);

    if (amount < 0)
        return -1;

    return amount * (1 - percent / 100.0);
}

/* Apply percentage discount and coupon */
double couponDiscount(Product p, double percent, double coupon) {

    double amount;

    if (coupon < 0)
        return -1;

    amount = discount(p, percent);

    if (amount < 0)
        return -1;

    amount -= coupon;

    return amount > 0 ? amount : 0;
}

/* Product audit */
void auditProduct(Product p) {

    printf("Audit: ID = %d | Name = %s\n", p.id, p.name);
}

/* Display product details */
void displayProduct(Product p) {

    printf("\nProduct ID: %d", p.id);
    printf("\nProduct Name: %s", p.name);
    printf("\nBase Price: Rs. %.2f", p.basePrice);
    printf("\nCategory Price: Rs. %.2f\n", finalPrice(p));
}

/* Calculate bill */
double calculateBill(double amount1, double amount2) {

    return amount1 + amount2;
}

/* Test result */
void testResult(const char *name, int condition) {

    if (condition) {
        printf("[PASS] %s\n", name);
        passed++;
    } else {
        printf("[FAIL] %s\n", name);
        failed++;
    }
}

/* Compare floating-point values */
int equal(double a, double b) {

    return fabs(a - b) < 0.001;
}

/* Automated testing */
void runTests() {

    Product book = {101, "C++ Textbook", 500, BOOK};
    Product accessory = {202, "USB Mouse", 800, ACCESSORY};
    Product stationery = {303, "Pen Set", 200, STATIONERY};

    Product invalid = {404, "Invalid", -100, BOOK};
    Product zero = {405, "Zero Price", 0, BOOK};

    printf("\n====================================\n");
    printf("          AUTOMATED TESTS\n");
    printf("====================================\n");

    testResult("Book category pricing",
               equal(finalPrice(book), 450));

    testResult("Accessory category pricing",
               equal(finalPrice(accessory), 840));

    testResult("Stationery category pricing",
               equal(finalPrice(stationery), 190));

    testResult("Percentage discount",
               equal(discount(book, 10), 405));

    testResult("Percentage plus coupon",
               equal(couponDiscount(accessory, 10, 20), 736));

    testResult("Coupon greater than amount",
               equal(couponDiscount(book, 10, 500), 0));

    testResult("Invalid discount percentage",
               equal(discount(book, 150), -1));

    testResult("Negative price validation",
               !isValidPrice(-100));

    testResult("Zero price validation",
               isValidPrice(0));

    testResult("Bill addition",
               equal(calculateBill(
                   discount(book, 10),
                   couponDiscount(accessory, 10, 20)
               ), 1141));

    testResult("Product registration",
               registerProduct(book));

    testResult("Duplicate ID rejection",
               !registerProduct(book));

    testResult("Negative price registration rejection",
               !registerProduct(invalid));

    testResult("Zero price registration",
               registerProduct(zero));

    printf("\nTests Passed: %d\n", passed);
    printf("Tests Failed: %d\n", failed);

    printf("====================================\n");
}

/* Main function */
int main() {

    Product book = {101, "C++ Textbook", 500, BOOK};
    Product accessory = {202, "USB Mouse", 800, ACCESSORY};
    Product stationery = {303, "Pen Set", 200, STATIONERY};

    double bookAmount;
    double accessoryAmount;
    double stationeryAmount;
    double total;

    printf("====================================\n");
    printf("    CAMPUS STORE MANAGEMENT SYSTEM\n");
    printf("       PROCEDURAL C VERSION\n");
    printf("====================================\n");

    registerProduct(book);
    registerProduct(accessory);
    registerProduct(stationery);

    printf("\n---------- PRODUCT DETAILS ----------\n");

    {
        int i;

        for (i = 0; i < productCount; i++)
            displayProduct(products[i]);
    }

    bookAmount = discount(book, 10);

    accessoryAmount = couponDiscount(accessory, 10, 20);

    stationeryAmount = discount(stationery, 10);

    printf("\n---------- DISCOUNT DETAILS ----------\n");

    printf("Book after 10%% discount: Rs. %.2f\n",
           bookAmount);

    printf("Accessory after 10%% discount and Rs.20 coupon: Rs. %.2f\n",
           accessoryAmount);

    printf("Stationery after 10%% discount: Rs. %.2f\n",
           stationeryAmount);

    printf("\n---------- BILL GENERATION ----------\n");

    total = calculateBill(bookAmount, accessoryAmount);

    printf("Book Amount: Rs. %.2f\n", bookAmount);

    printf("Accessory Amount: Rs. %.2f\n", accessoryAmount);

    printf("Grand Total: Rs. %.2f\n", total);

    printf("\n---------- PRODUCT AUDIT ----------\n");

    {
        int i;

        for (i = 0; i < productCount; i++)
            auditProduct(products[i]);
    }

    runTests();

    printf("\n====================================\n");
    printf("        PROGRAM COMPLETED\n");
    printf("====================================\n");

    return 0;
}
