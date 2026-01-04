/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#ifndef FOODITEM_H
#define FOODITEM_H

#include <iostream>
using namespace std;

class FoodItem
{
private:
    string itemname;
    double price;
    int quantity;

public:
    // default constructor
    FoodItem() : itemname(""), price(0), quantity(0) {}
    // paramatarized constructor
    FoodItem(string itemn, double p, int quan);

    // Mutators (setters)
    void setItemname(string n) { itemname = n; }

    void setPrice(double p) { price = p; }

    void setQuantity(int quan) { quantity = quan; }

    // Accessors (getters)
    string getItemname() const { return itemname; }

    int getQuantity() const { return quantity; }

    double getPrice() const { return price; }

    // function that calculates the total price of an item
    double calculateItemTotal() const;

    // function that displays item in format (Chicken Shawarma x2 @ 45.00 EGP = 90.00 EGP)
    void displayItem() const;
};

#endif
