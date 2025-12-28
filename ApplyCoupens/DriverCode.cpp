/*
#include <bits/stdc++.h>
using namespace std;

enum ProductType {
    ELECTRONICS,
    FURNITURE,
    CLOTHES
};

// ===================== Product Base Class =====================
class Product {
protected:
    ProductType type;
    int cost;
    string name;

public:
    Product(ProductType type, string name, int cost)
        : type(type), cost(cost), name(name) {}

    virtual ~Product() = default;

    // All should be virtual so decorators can override or delegate
    virtual int getPrice() = 0;
    virtual ProductType getProductType() { return type; }
    virtual string getName() { return name; }
};

// ===================== Concrete Products =====================
class Mobile : public Product {
public:
    Mobile(ProductType type, string name, int cost)
        : Product(type, name, cost) {}

    int getPrice() override {
        return cost;
    }
};

class Sofa : public Product {
public:
    Sofa(ProductType type, string name, int cost)
        : Product(type, name, cost) {}

    int getPrice() override {
        return cost;
    }
};

// ===================== Decorator Base Class =====================
class CouponsDecorator : public Product {
protected:
    shared_ptr<Product> product;

public:
    CouponsDecorator(shared_ptr<Product> p)
        // Decorator does NOT copy real cost; cost=0 is fine since it's unused
        : Product(ProductType::ELECTRONICS, "", 0), product(p) {}

    // Delegation
    ProductType getProductType() override {
        return product->getProductType();
    }

    string getName() override {
        return product->getName();
    }

    // getPrice remains abstract
    virtual int getPrice() = 0;
};

// ===================== Percentage Coupon =====================
class PercentageCouponDecorator : public CouponsDecorator {
private:
    int discountPercentage;

public:
    PercentageCouponDecorator(shared_ptr<Product> p, int discountPercentage)
        : CouponsDecorator(p), discountPercentage(discountPercentage) {}

    int getPrice() override {
        int price = product->getPrice();
        return price - (price * discountPercentage / 100);
    }
};

// ===================== Type-Based Coupon =====================
class TypeCouponDecorator : public CouponsDecorator {
private:
    int discountPercentage;
    set<ProductType> eligibleProducts = { ELECTRONICS, FURNITURE };

public:
    TypeCouponDecorator(shared_ptr<Product> p, int discountPercentage)
        : CouponsDecorator(p), discountPercentage(discountPercentage) {}

    int getPrice() override {
        int price = product->getPrice();
        if (eligibleProducts.count(product->getProductType()))
            return price - (price * discountPercentage / 100);
        return price;
    }
};

// ===================== Shopping Cart =====================
class ShoppingCart {
private:
    vector<shared_ptr<Product>> allProducts;

public:
    void addProduct(shared_ptr<Product> product) {
        allProducts.push_back(product);
    }

    int finalProductCost() {
        int cost = 0;
        for (auto& product : allProducts) {
            cost += product->getPrice();
        }
        return cost;
    }
};

// ===================== Main =====================
int main() {
    ShoppingCart cart;

    shared_ptr<Product> mobile = make_shared<Mobile>(ELECTRONICS, "iPhone", 1000);
    shared_ptr<Product> sofa = make_shared<Sofa>(CLOTHES, "Shirt", 500);

    // Apply coupons explicitly
    shared_ptr<Product> discountedMobile =
        make_shared<PercentageCouponDecorator>(mobile, 20);   // 1000 → 800

    shared_ptr<Product> discountedSofa =
        make_shared<TypeCouponDecorator>(sofa, 30);           // Clothes → no discount → 500

    cart.addProduct(discountedMobile);
    cart.addProduct(discountedSofa);

    cout << "Final cost after coupons: " << cart.finalProductCost() << endl;
}

*/

#include <bits/stdc++.h>
using namespace std;

enum ProductType
{
    ELECTRONICS,
    FURNITURE,
    CLOTHES
};
class Product {
protected:
    ProductType type;
    int cost;
    string name;
public:
/*
Because of the pure virtual function, Product is abstract → you can’t create objects of it directly:
So there’s no situation where you’d need to call a default constructor of Product directly.
*/
    Product(ProductType type, string name, int cost)
        : type(type), cost(cost), name(name) {}
    virtual ~Product() = default;

    virtual int getPrice() = 0;
    ProductType getProductType() { return type; }
    string getName() { return name; }
};

// ----------------- Concrete Products -----------------
class Mobile : public Product {
public:
/*
if concreate classes assign value directly to ProductType type;int cost; string name;
 then Your concrete classes (Mobile, Sofa) directly assign type, cost, name instead of calling Product’s constructor. This compiles but breaks encapsulation (you’re setting protected fields directly).
*/
    Mobile(ProductType type, string name, int cost)
        : Product(type, name, cost) {}
    int getPrice() override { return cost; }
};

class Sofa : public Product {
public:
    Sofa(ProductType type, string name, int cost)
        : Product(type, name, cost) {}
    int getPrice() override { return cost; }
};

// ----------------- Abstract Decorator -----------------
/*
if define like this 
class CouponsDecorator : public Product {
private:
public:
};

This defeats the purpose of the decorator pattern.

A decorator must hold a wrapped Product and delegate calls.

Without this, PercentageCouponDecorator and TypeCouponDecorator each redundantly declare shared_ptr<Product> product; → not proper inheritance.
*/
class CouponsDecorator : public Product {
protected:
    shared_ptr<Product> product;
public:
    CouponsDecorator(shared_ptr<Product> p)
        : Product(p->getProductType(), p->getName(), p->getPrice()), product(p) {}
    virtual int getPrice() = 0;
};

// ----------------- Percentage Coupon -----------------
class PercentageCouponDecorator : public CouponsDecorator {
private:
    int discountPercentage;
public:
    PercentageCouponDecorator(shared_ptr<Product> p, int discountPercentage)
        : CouponsDecorator(p), discountPercentage(discountPercentage) {}

    int getPrice() override {
        int price = product->getPrice();
        return price - (price * discountPercentage / 100);
    }
};

// ----------------- Type-based Coupon -----------------
class TypeCouponDecorator : public CouponsDecorator {
private:
    int discountPercentage;
    set<ProductType> eligibleProducts = {ELECTRONICS, FURNITURE};
public:
    TypeCouponDecorator(shared_ptr<Product> p, int discountPercentage)
        : CouponsDecorator(p), discountPercentage(discountPercentage) {}

    int getPrice() override {
        int price = product->getPrice();
        if (eligibleProducts.count(product->getProductType())) {
            return price - (price * discountPercentage / 100);
        }
        return price;
    }
};

// ----------------- Shopping Cart -----------------
class ShoppingCart {
private:
    vector<shared_ptr<Product>> allProducts;
public:
    void addProduct(shared_ptr<Product> product) {
        // Example: Apply both type coupon and percentage coupon
        // shared_ptr<Product> updatedProduct =
        //     make_shared<PercentageCouponDecorator>(
        //         make_shared<TypeCouponDecorator>(product, 30), 20);
        allProducts.push_back(product); // leave coupon decision to caller
    }

    int finalProductCost() {
        int cost = 0;
        for (auto& product : allProducts) {
            cost += product->getPrice();
        }
        return cost;
    }
};

// ----------------- Main -----------------
int main() {
    ShoppingCart cart;

    shared_ptr<Product> mobile = make_shared<Mobile>(ELECTRONICS, "iPhone", 1000);
    shared_ptr<Product> sofa = make_shared<Sofa>(CLOTHES, "Shirt", 500);

    // Apply coupons explicitly
    shared_ptr<Product> discountedMobile = make_shared<PercentageCouponDecorator>(mobile, 20);
    shared_ptr<Product> discountedSofa = make_shared<TypeCouponDecorator>(sofa, 30);

    cart.addProduct(discountedMobile);
    cart.addProduct(discountedSofa);

    cout << "Final cost after coupons: " << cart.finalProductCost() << endl;


    cout << "\n--- Nested Coupon Example (Type + Percentage) ---\n";
shared_ptr<Product> laptop = make_shared<Mobile>(ELECTRONICS, "MacBook Pro", 2000);

// First decorator → type-based discount (30%) because it's ELECTRONICS
shared_ptr<Product> laptopType30 = make_shared<TypeCouponDecorator>(laptop, 30);

// Second decorator → additional percentage discount (20%)
shared_ptr<Product> laptopNested = make_shared<PercentageCouponDecorator>(laptopType30, 20);

cout << "Original: 2000\n";
cout << "After 30% type discount: " << laptopType30->getPrice() << endl;
cout << "After additional 20%: " << laptopNested->getPrice() << endl;


cout << "\n--- Triple Nested Coupons Example ---\n";
shared_ptr<Product> tv = make_shared<Mobile>(ELECTRONICS, "Sony Bravia", 3000);

// 1) Type coupon: 15%
shared_ptr<Product> tvType15 = make_shared<TypeCouponDecorator>(tv, 15);

// 2) Percent coupon: 10%
shared_ptr<Product> tvType15Pct10 = make_shared<PercentageCouponDecorator>(tvType15, 10);

// 3) Another percent coupon: 5%
shared_ptr<Product> tvFinal = make_shared<PercentageCouponDecorator>(tvType15Pct10, 5);

cout << "Original: 3000\n";
cout << "After 15% type coupon: " << tvType15->getPrice() << endl;
cout << "After +10%: " << tvType15Pct10->getPrice() << endl;
cout << "After +5%: " << tvFinal->getPrice() << endl;


cout << "\n--- Type Coupon Ineffective Example (Clothes) ---\n";
shared_ptr<Product> shirt = make_shared<Sofa>(CLOTHES, "T-Shirt", 400);

// Type coupon: 30% (won’t apply)
shared_ptr<Product> shirtType30 = make_shared<TypeCouponDecorator>(shirt, 30);

// Percentage coupon: 20% always applies
shared_ptr<Product> shirtFinal = make_shared<PercentageCouponDecorator>(shirtType30, 20);

cout << "Original: 400\n";
cout << "After Type Coupon (ignored): " << shirtType30->getPrice() << endl;
cout << "After 20% off: " << shirtFinal->getPrice() << endl;

}
