/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#include "Customer.h"

// constructors
Customer::Customer() : User(), deliveryAddress(""), loyaltyPoints(0) {}

Customer::Customer(string id, string n, string phoneNum, string DeliveryAddreS, int loyaltyPTS)
    : User(id, n, phoneNum), deliveryAddress(DeliveryAddreS), loyaltyPoints(loyaltyPTS)
{
}

// overriden function
void Customer::displayInfo() const
{
    cout << "Customer's name: " << getName() << endl;
    cout << "Customer's id: " << getUserID() << endl;
    cout << "Customer's phone number: " << getPhoneNumber() << endl;
    cout << "delivery address: " << getdeliveryAddress() << endl;
    cout << "Loyalty points: " << getloyaltyPoints() << endl;
}
double Customer::calculateEarnings() const
{
    return (loyaltyPoints * 0.5);
}

Customer &Customer::operator+=(int points)
{
    loyaltyPoints += points;
    return *this;
}