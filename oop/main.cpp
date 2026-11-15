#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <set>
using namespace std;

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

    int getID() const { return id; }
    string getName() const { return name; }

    static int getProductCount() {
        return liveCount;
    }

    virtual double finalPrice() const = 0;

    double discount(double percent) const {
        if (percent < 0 || percent > 100)
            return -1;

        return finalPrice() * (1 - percent / 100);
    }

    double discount(double percent, double coupon) const {
        if (coupon < 0) return -1;

        double amount = discount(percent);

        if (amount < 0) return -1;

        amount -= coupon;
        return amount > 0 ? amount : 0;
    }

    friend void auditProduct(const Product& p);
};

int Product::liveCount = 0;

class Book : public Product {
public:
    Book(int i, string n, double p) : Product(i, n, p) {}

    double finalPrice() const override {
        return basePrice * 0.90;
    }
};

class Accessory : public Product {
public:
    Accessory(int i, string n, double p) : Product(i, n, p) {}

    double finalPrice() const override {
        return basePrice * 1.05;
    }
};

class Stationery : public Product {
public:
    Stationery(int i, string n, double p) : Product(i, n, p) {}

    double finalPrice() const override {
        return basePrice * 0.95;
    }
};

void auditProduct(const Product& p) {
    cout << "Audit: ID=" << p.id
         << " | Name=" << p.name << endl;
}

class Bill {
private:
    double total;

public:
    Bill(double amount = 0) : total(amount) {}

    Bill operator+(const Bill& other) const {
        return Bill(total + other.total);
    }

    double getTotal() const {
        return total;
    }
};

int main() {
    vector<unique_ptr<Product>> products;
    set<int> ids;

    int choice;

    cout << fixed << setprecision(2);

    cout << "====================================\n";
    cout << "   CAMPUS STORE MANAGEMENT SYSTEM\n";
    cout << "          NATIVE OOP VERSION\n";
    cout << "====================================\n";

    do {
        cout << "\n1. Add Product";
        cout << "\n2. Display Products";
        cout << "\n3. Generate Bill";
        cout << "\n4. Product Audit";
        cout << "\n5. Show Live Product Count";
        cout << "\n0. Exit";
        cout << "\nEnter Choice: ";

        if (!(cin >> choice)) break;

        switch (choice) {

        case 1: {
            int id, category;
            string name;
            double price, percent, coupon;

            cout << "\nEnter Product ID: ";
            cin >> id;

            if (id <= 0 || ids.count(id)) {
                cout << "Invalid or duplicate ID!\n";
                break;
            }

            cout << "Enter Product Name: ";
            getline(cin >> ws, name);

            cout << "Category (1.Book 2.Accessory 3.Stationery): ";
            cin >> category;

            if (category < 1 || category > 3) {
                cout << "Invalid category!\n";
                break;
            }

            cout << "Enter Base Price: ";
            cin >> price;

            if (price < 0) {
                cout << "Negative price not allowed!\n";
                break;
            }

            cout << "Enter Discount Percentage: ";
            cin >> percent;

            if (percent < 0 || percent > 100) {
                cout << "Invalid discount!\n";
                break;
            }

            cout << "Enter Coupon Amount (0 if none): ";
            cin >> coupon;

            if (coupon < 0) {
                cout << "Invalid coupon!\n";
                break;
            }

            if (category == 1)
                products.push_back(make_unique<Book>(id, name, price));

            else if (category == 2)
                products.push_back(make_unique<Accessory>(id, name, price));

            else
                products.push_back(make_unique<Stationery>(id, name, price));

            ids.insert(id);

            cout << "Product registered successfully!\n";

            break;
        }

        case 2:
            if (products.empty()) {
                cout << "No products registered.\n";
                break;
            }

            cout << "\n========== PRODUCT DETAILS ==========\n";

            for (const auto& p : products) {
                cout << "\nID: " << p->getID();
                cout << "\nName: " << p->getName();
                cout << "\nCategory Price: Rs. "
                     << p->finalPrice() << endl;
            }

            break;

        case 3: {
            if (products.empty()) {
                cout << "No products available for billing.\n";
                break;
            }

            Bill grandTotal;

            cout << "\n========== FINAL BILL ==========\n";

            for (const auto& p : products) {
                double percent, coupon;

                cout << "\nProduct: " << p->getName();

                cout << "\nDiscount Percentage: ";
                cin >> percent;

                if (percent < 0 || percent > 100) {
                    cout << "Invalid discount!\n";
                    continue;
                }

                cout << "Coupon Amount: ";
                cin >> coupon;

                if (coupon < 0) {
                    cout << "Invalid coupon!\n";
                    continue;
                }

                double amount = p->discount(percent, coupon);

                Bill item(amount);
                grandTotal = grandTotal + item;

                cout << "Payable: Rs. " << amount << endl;
            }

            cout << "\nGRAND TOTAL: Rs. "
                 << grandTotal.getTotal() << endl;

            break;
        }

        case 4:
            for (const auto& p : products)
                auditProduct(*p);
            break;

        case 5:
            cout << "Live Product Count: "
                 << Product::getProductCount() << endl;
            break;

        case 0:
            cout << "Thank you for using the system!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
