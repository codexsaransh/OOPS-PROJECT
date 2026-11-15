#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Product {

private:

    int id;

    static int productCount;

protected:

    string name;
    double basePrice;

public:

    Product(int i, string n, double p)
        : id(i), name(n), basePrice(p) {

        if (p < 0)
            basePrice = 0;

        productCount++;
    }

    Product(const Product&) = delete;

    Product& operator=(const Product&) = delete;

    virtual ~Product() {
        productCount--;
    }

    inline string getName() const {
        return name;
    }

    inline double getPrice() const {
        return basePrice;
    }

    int getID() const {
        return id;
    }

    static int getProductCount() {
        return productCount;
    }

    virtual double finalPrice() const {
        return basePrice;
    }

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

        return amount > coupon ? amount - coupon : 0;
    }

    friend void auditProduct(const Product& p);
};

int Product::productCount = 0;


// FRIEND FUNCTION

void auditProduct(const Product& p) {

    cout << "Audit: ID=" << p.id
         << ", Name=" << p.name << endl;
}


// BOOK CLASS

class Book : public Product {

public:

    Book(int id, string name, double price)
        : Product(id, name, price) {}

    double finalPrice() const override {
        return basePrice * 0.90;
    }
};


// ACCESSORY CLASS

class Accessory : public Product {

public:

    Accessory(int id, string name, double price)
        : Product(id, name, price) {}

    double finalPrice() const override {
        return basePrice * 1.05;
    }
};


// STATIONERY CLASS

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

    explicit Bill(double amount = 0) {
        total = amount >= 0 ? amount : 0;
    }

    Bill operator+(const Bill& other) const {
        return Bill(total + other.total);
    }

    friend ostream& operator<<(ostream& out, const Bill& b) {

        out << fixed << setprecision(2) << b.total;

        return out;
    }
};


// MAIN FUNCTION

int main() {

    cout << fixed << setprecision(2);

    cout << "====================================\n";
    cout << "   CAMPUS STORE MANAGEMENT SYSTEM\n";
    cout << "          OOP VERSION\n";
    cout << "====================================\n";

    Book book(101, "C++ Textbook", 500);

    Accessory accessory(202, "USB Mouse", 800);

    Stationery stationery(303, "Pen Set", 200);

    cout << "\n--- PRODUCT OBJECT COUNT ---\n";

    cout << "Live Product Objects: "
         << Product::getProductCount() << endl;


    cout << "\n--- PRODUCT DETAILS ---\n";

    cout << book.getName()
         << " | Category Price: Rs. "
         << book.finalPrice() << endl;

    cout << accessory.getName()
         << " | Category Price: Rs. "
         << accessory.finalPrice() << endl;

    cout << stationery.getName()
         << " | Category Price: Rs. "
         << stationery.finalPrice() << endl;


    cout << "\n--- DISCOUNT DETAILS ---\n";

    double bookAmount = book.discount(10);

    double accessoryAmount = accessory.discount(10, 20);

    double stationeryAmount = stationery.discount(10);

    cout << "Book after 10% discount: Rs. "
         << bookAmount << endl;

    cout << "Accessory after 10% discount and Rs.20 coupon: Rs. "
         << accessoryAmount << endl;

    cout << "Stationery after 10% discount: Rs. "
         << stationeryAmount << endl;


    cout << "\n--- BILL GENERATION ---\n";

    Bill bookBill(bookAmount);

    Bill accessoryBill(accessoryAmount);

    Bill totalBill = bookBill + accessoryBill;

    cout << "Combined Bill: Rs. "
         << totalBill << endl;


    cout << "\n--- PRODUCT AUDIT ---\n";

    auditProduct(book);


    cout << "\n--- VALIDATION ---\n";

    cout << "Invalid discount result: "
         << book.discount(150) << endl;

    cout << "Coupon greater than amount: "
         << accessory.discount(10, 1000) << endl;


    cout << "\n====================================\n";
    cout << "       PROGRAM COMPLETED\n";
    cout << "====================================\n";

    return 0;
}
