/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"

class Customer : public User
{
private:
    string deliveryAddress;
    int loyaltyPoints;

public:
    Customer();                                                                                                    // default constructor
    Customer(string id = "", string n = "", string phoneNum = "", string DeliveryAddreS = "", int loyaltyPTS = 0); // paramatarized constructor

    // overriding pure virtual functions from abstarct User class
    void displayInfo() const override;
    double calculateEarnings() const override;

    // setters
    void setdeliveryAddress(string Delivaddress) { deliveryAddress = Delivaddress; }
    void setloyaltyPoints(int loyaltyPTS) { loyaltyPoints = loyaltyPTS; }

    // getters
    string getdeliveryAddress() const { return deliveryAddress; }
    int getloyaltyPoints() const { return loyaltyPoints; }

    // operator += overloading
    Customer &operator+=(int points);
};

#endif