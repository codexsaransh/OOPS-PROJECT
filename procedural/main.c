#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int id, category;
    char name[100];
    double price, percent, coupon, finalAmount;
} Product;

Product products[MAX];
int count = 0;

double categoryPrice(Product p) {
    if (p.category == 1) return p.price * 0.90;
    if (p.category == 2) return p.price * 1.05;
    if (p.category == 3) return p.price * 0.95;
    return -1;
}

double calculateDiscount(Product p) {
    double amount = categoryPrice(p);
    amount -= amount * p.percent / 100;
    amount -= p.coupon;
    return amount > 0 ? amount : 0;
}

int uniqueID(int id) {
    int i;
    for (i = 0; i < count; i++)
        if (products[i].id == id) return 0;
    return 1;
}

void audit(Product p) {
    printf("Audit: ID=%d | Name=%s\n", p.id, p.name);
}

void addProduct() {
    Product p;

    if (count >= MAX) {
        printf("Product limit reached!\n");
        return;
    }

    printf("\nEnter Product ID: ");
    if (scanf("%d", &p.id) != 1) return;

    if (p.id <= 0 || !uniqueID(p.id)) {
        printf("Invalid or duplicate ID!\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf(" %99[^\n]", p.name);

    printf("Enter Category (1.Book 2.Accessory 3.Stationery): ");
    if (scanf("%d", &p.category) != 1) return;

    if (p.category < 1 || p.category > 3) {
        printf("Invalid category!\n");
        return;
    }

    printf("Enter Base Price: ");
    if (scanf("%lf", &p.price) != 1) return;

    if (p.price < 0) {
        printf("Price cannot be negative!\n");
        return;
    }

    printf("Enter Discount Percentage: ");
    if (scanf("%lf", &p.percent) != 1) return;

    if (p.percent < 0 || p.percent > 100) {
        printf("Invalid discount!\n");
        return;
    }

    printf("Enter Coupon Amount (0 if none): ");
    if (scanf("%lf", &p.coupon) != 1) return;

    if (p.coupon < 0) {
        printf("Invalid coupon!\n");
        return;
    }

    p.finalAmount = calculateDiscount(p);
    products[count++] = p;

    printf("\nProduct registered successfully!\n");
}

void displayProducts() {
    int i;

    if (count == 0) {
        printf("\nNo products registered.\n");
        return;
    }

    printf("\n========== PRODUCT DETAILS ==========\n");

    for (i = 0; i < count; i++) {
        printf("\nID: %d", products[i].id);
        printf("\nName: %s", products[i].name);
        printf("\nBase Price: Rs. %.2f", products[i].price);
        printf("\nCategory Price: Rs. %.2f",
               categoryPrice(products[i]));
        printf("\nDiscount: %.2f%%", products[i].percent);
        printf("\nCoupon: Rs. %.2f", products[i].coupon);
        printf("\nFinal Price: Rs. %.2f\n",
               products[i].finalAmount);
    }
}

void generateBill() {
    int i;
    double total = 0;

    if (count == 0) {
        printf("\nNo products available for billing.\n");
        return;
    }

    printf("\n========== FINAL BILL ==========\n");

    for (i = 0; i < count; i++) {
        printf("%s : Rs. %.2f\n",
               products[i].name,
               products[i].finalAmount);

        total += products[i].finalAmount;
    }

    printf("--------------------------------\n");
    printf("GRAND TOTAL: Rs. %.2f\n", total);
}

void runTests() {
    Product b = {1, 1, "Book", 500, 10, 0, 0};
    Product a = {2, 2, "Accessory", 800, 10, 20, 0};
    Product s = {3, 3, "Stationery", 200, 10, 0, 0};

    printf("\n========== BASIC TESTS ==========\n");

    printf("Book expected 405: %.2f\n", calculateDiscount(b));
    printf("Accessory expected 736: %.2f\n", calculateDiscount(a));
    printf("Stationery expected 171: %.2f\n", calculateDiscount(s));
}

int main() {
    int choice;

    printf("====================================\n");
    printf("   CAMPUS STORE MANAGEMENT SYSTEM\n");
    printf("       PROCEDURAL C VERSION\n");
    printf("====================================\n");

    do {
        printf("\n1. Add Product");
        printf("\n2. Display Products");
        printf("\n3. Generate Bill");
        printf("\n4. Product Audit");
        printf("\n5. Run Basic Tests");
        printf("\n0. Exit");
        printf("\nEnter Choice: ");

        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                displayProducts();
                break;

            case 3:
                generateBill();
                break;

            case 4: {
                int i;
                for (i = 0; i < count; i++)
                    audit(products[i]);
                break;
            }

            case 5:
                runTests();
                break;

            case 0:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}
