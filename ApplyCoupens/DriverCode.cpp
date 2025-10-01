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
}
