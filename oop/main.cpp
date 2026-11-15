#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// BASE CLASS
class Product {
protected:
    int id;
    string name;
    double basePrice;

private:
    static int liveCount;

public:
    Product(int i, string n, double p)
        : id(i), name(n), basePrice(p) {
        liveCount++;
    }

    virtual ~Product() {
        liveCount--;
    }

    Product(const Product&) = delete;
    Product& operator=(const Product&) = delete;

    inline int getID() const {
        return id;
    }

    inline string getName() const {
        return name;
    }

    static int getProductCount() {
        return liveCount;
    }

    virtual double finalPrice() const = 0;

    // Function overloading
    double discount(double percent) const {
        if (percent < 0 || percent > 100)
            return -1;

        return finalPrice() * (1 - percent / 100.0);
    }

    double discount(double percent, double coupon) const {
        if (coupon < 0)
            return -1;

        double amount = discount(percent);

        if (amount < 0)
            return -1;

        amount -= coupon;
        return amount > 0 ? amount : 0;
    }

    // Friend function
    friend void auditProduct(const Product& p);
};

int Product::liveCount = 0;

// DERIVED CLASSES
class Book : public Product {
public:
    Book(int id, string name, double price)
        : Product(id, name, price) {}

    double finalPrice() const override {
        return basePrice * 0.90;
    }
};

class Accessory : public Product {
public:
    Accessory(int id, string name, double price)
        : Product(id, name, price) {}

    double finalPrice() const override {
        return basePrice * 1.05;
    }
};

class Stationery : public Product {
public:
    Stationery(int id, string name, double price)
        : Product(id, name, price) {}

    double finalPrice() const override {
        return basePrice * 0.95;
    }
};

// BILL CLASS
class Bill {
private:
    double total;

public:
    Bill(double amount = 0) : total(amount) {}

    // Operator overloading
    Bill operator+(const Bill& other) const {
        return Bill(total + other.total);
    }

    double getTotal() const {
        return total;
    }
};

// FRIEND FUNCTION IMPLEMENTATION
void auditProduct(const Product& p) {
    cout << "Audit: ID = " << p.id
         << " | Name = " << p.name << endl;
}

// VALIDATION
bool isValidProduct(int id, double price) {
    return id > 0 && price >= 0;
}

bool isUniqueID(const vector<int>& ids, int id) {
    for (int existing : ids) {
        if (existing == id)
            return false;
    }
    return true;
}

// TESTING
int passed = 0;
int failed = 0;

bool equal(double a, double b) {
    return fabs(a - b) < 0.001;
}

void testResult(const string& name, bool condition) {
    if (condition) {
        cout << "[PASS] " << name << endl;
        passed++;
    } else {
        cout << "[FAIL] " << name << endl;
        failed++;
    }
}

void runTests() {
    Book b(501, "Test Book", 500);
    Accessory a(502, "Test Mouse", 800);
    Stationery s(503, "Test Pen", 200);

    Bill bill1(405);
    Bill bill2(736);

    testResult("Book pricing", equal(b.finalPrice(), 450));
    testResult("Accessory pricing", equal(a.finalPrice(), 840));
    testResult("Stationery pricing", equal(s.finalPrice(), 190));

    testResult("Percentage discount",
               equal(b.discount(10), 405));

    testResult("Percentage plus coupon",
               equal(a.discount(10, 20), 736));

    testResult("Coupon greater than amount",
               equal(b.discount(10, 500), 0));

    testResult("Invalid discount",
               equal(b.discount(150), -1));

    testResult("Negative coupon rejection",
               equal(b.discount(10, -20), -1));

    testResult("Bill addition",
               equal((bill1 + bill2).getTotal(), 1141));

    testResult("Negative price validation",
               !isValidProduct(504, -100));

    testResult("Zero price validation",
               isValidProduct(505, 0));

    vector<int> ids = {101, 102};

    testResult("Unique ID validation",
               isUniqueID(ids, 103));

    testResult("Duplicate ID rejection",
               !isUniqueID(ids, 101));

    cout << "\nTests Passed: " << passed;
    cout << "\nTests Failed: " << failed << endl;
}

int main() {
    cout << fixed << setprecision(2);

    cout << "====================================\n";
    cout << "    CAMPUS STORE MANAGEMENT SYSTEM\n";
    cout << "          NATIVE OOP VERSION\n";
    cout << "====================================\n";

    {
        Book book(101, "C++ Textbook", 500);
        Accessory accessory(202, "USB Mouse", 800);
        Stationery stationery(303, "Pen Set", 200);

        vector<Product*> products = {
            &book, &accessory, &stationery
        };

        cout << "\nLive Product Count: "
             << Product::getProductCount() << endl;

        cout << "\n---------- PRODUCT DETAILS ----------\n";

        for (const Product* p : products) {
            cout << "\nProduct ID: " << p->getID();
            cout << "\nProduct Name: " << p->getName();
            cout << "\nCategory Price: Rs. "
                 << p->finalPrice() << endl;
        }

        double bookAmount = book.discount(10);
        double accessoryAmount = accessory.discount(10, 20);
        double stationeryAmount = stationery.discount(10);

        cout << "\n---------- DISCOUNT DETAILS ----------\n";
        cout << "Book: Rs. " << bookAmount << endl;
        cout << "Accessory: Rs. " << accessoryAmount << endl;
        cout << "Stationery: Rs. " << stationeryAmount << endl;

        Bill bookBill(bookAmount);
        Bill accessoryBill(accessoryAmount);

        Bill grandTotal = bookBill + accessoryBill;

        cout << "\n---------- BILL GENERATION ----------\n";
        cout << "Book Amount: Rs. "
             << bookBill.getTotal() << endl;

        cout << "Accessory Amount: Rs. "
             << accessoryBill.getTotal() << endl;

        cout << "Grand Total: Rs. "
             << grandTotal.getTotal() << endl;

        cout << "\n---------- PRODUCT AUDIT ----------\n";

        for (const Product* p : products)
            auditProduct(*p);

        cout << "\n---------- AUTOMATED TESTS ----------\n";
        runTests();
    }

    cout << "\nLive Product Count After Cleanup: "
         << Product::getProductCount() << endl;

    cout << "\n====================================\n";
    cout << "        PROGRAM COMPLETED\n";
    cout << "====================================\n";

    return 0;
}
