/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#ifndef ORDER_H
#define ORDER_H

#include "Customer.h"
#include "DeliveryDriver.h"
#include "FoodItem.h"
#include "Enums.h"

#include <iostream>
#include <string>
using namespace std;

class Order
{
private:
    string orderId;
    Customer *customer;     // aggregation
    DeliveryDriver *driver; // aggregation
    FoodItem *items;        // Dynamic arrays of FoodItem objects (composition)
    int itemCount, capacity;
    OrderStatus status;
    static int totalOrders;

public:
    Order();

    Order(string id, Customer *cust);

    Order(const Order &obj);

    ~Order();

    void addItem(const FoodItem &item);

    void assignDriver(DeliveryDriver *drv)
    {
        driver = drv;
    }

    void updateStatus(OrderStatus newStatus);

    double calculateTotal() const;

    void displayOrder() const;

    // static function
    static int getTotalOrders() { return totalOrders; }

    // getters
    string getOrderId() const { return orderId; }

    const Customer *getCustomer() const { return customer; }

    const DeliveryDriver *getDriver() const { return driver; }

    OrderStatus getStatus() const { return status; }

    int getItemCount() const { return itemCount; }

    Order &operator+=(const FoodItem &food);

    friend Order operator+(const Order &order1, const Order &order2);

    FoodItem &operator[](int index);

    const FoodItem &operator[](int index) const;

    friend ostream &operator<<(ostream &out, const Order &obj);

    friend bool operator>(const Order &order1, const Order &order2);
};

#endif