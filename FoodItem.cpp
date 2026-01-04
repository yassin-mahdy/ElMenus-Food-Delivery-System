/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#include "FoodItem.h"

#include <iostream>
using namespace std;

// paramatarized constructor with intializer list
FoodItem::FoodItem(string itemn, double p, int quan)
    : itemname(itemn), price(p), quantity(quan)
{
}
void FoodItem::displayItem() const

{
    double total = quantity * price;
    cout << itemname << " x" << quantity
         << " @ " << price << " EGP = "
         << total << " EGP" << endl;
}

double FoodItem::calculateItemTotal() const
{
    return quantity * price;
}