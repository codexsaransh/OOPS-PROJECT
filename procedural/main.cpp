#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

struct Product {
    int id;
    string name;
    double basePrice;
    int category;
};

bool isValidPrice(double price) {
    return price >= 0;
}

bool isUniqueID(const vector<Product>& products, int id) {
    for (const auto& p : products)
        if (p.id == id)
            return false;

    return true;
}

double finalPrice(const Product& p) {
    switch (p.category) {
        case 1: return p.basePrice * 0.90;
        case 2: return p.basePrice * 1.05;
        case 3: return p.basePrice * 0.95;
        default: return p.basePrice;
    }
}

double discount(const Product& p, double percent) {
    if (percent < 0 || percent > 100)
        return -1;

    return finalPrice(p) * (1 - percent / 100.0);
}

double discount(const Product& p, double percent, double coupon) {
    if (coupon < 0)
        return -1;

    double amount = discount(p, percent);

    if (amount < 0)
        return -1;

    return amount > coupon ? amount - coupon : 0;
}

void auditProduct(const Product& p) {
    cout << "Audit: ID=" << p.id
         << ", Name=" << p.name << endl;
}

double calculateBill(double a, double b) {
    return a + b;
}

void displayProduct(const Product& p) {
    cout << "\nProduct ID: " << p.id;
    cout << "\nName: " << p.name;
    cout << "\nBase Price: Rs. " << p.basePrice;
    cout << "\nCategory Price: Rs. " << finalPrice(p);
    cout << endl;
}

int main() {

    cout << fixed << setprecision(2);

    vector<Product> products;

    Product book = {101, "C++ Textbook", 500, 1};
    Product accessory = {202, "USB Mouse", 800, 2};
    Product stationery = {303, "Pen Set", 200, 3};

    products.push_back(book);
    products.push_back(accessory);
    products.push_back(stationery);

    cout << "====================================\n";
    cout << "   CAMPUS STORE MANAGEMENT SYSTEM\n";
    cout << "       PROCEDURAL VERSION\n";
    cout << "====================================\n";

    cout << "\n--- PRODUCT DETAILS ---\n";

    for (const auto& p : products)
        displayProduct(p);

    double bookAmount = discount(book, 10);
    double accessoryAmount = discount(accessory, 10, 20);
    double stationeryAmount = discount(stationery, 10);

    cout << "\n--- DISCOUNT DETAILS ---\n";

    cout << "Book after 10% discount: Rs. "
         << bookAmount << endl;

    cout << "Accessory after 10% discount and Rs.20 coupon: Rs. "
         << accessoryAmount << endl;

    cout << "Stationery after 10% discount: Rs. "
         << stationeryAmount << endl;

    cout << "\n--- BILL GENERATION ---\n";

    double total = calculateBill(bookAmount, accessoryAmount);

    cout << "Book + Accessory Total: Rs. "
         << total << endl;

    cout << "\n--- PRODUCT AUDIT ---\n";

    auditProduct(book);

    cout << "\n--- VALIDATION ---\n";

    cout << "Negative price valid: "
         << (isValidPrice(-100) ? "YES" : "NO") << endl;

    cout << "Duplicate ID valid: "
         << (isUniqueID(products, 101) ? "YES" : "NO") << endl;

    cout << "\n====================================\n";
    cout << "       PROGRAM COMPLETED\n";
    cout << "====================================\n";

    return 0;
}
