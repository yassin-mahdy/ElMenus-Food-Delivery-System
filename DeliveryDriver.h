/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#ifndef DELIVERYDRIVER_H
#define DELIVERYDRIVER_H

#include "User.h"

class DeliveryDriver : public User
{
private:
    string vehicleType;
    int completedDeliveries;
    double totalEarnings;

public:
    DeliveryDriver(); // default constructor
    // paramatarized constructor
    DeliveryDriver(string id, string n, string phoneNum, string vType, int completed, double earnings);

    // Overriding pure virtual functions
    void displayInfo() const override;
    double calculateEarnings() const override;

    // Method for calculating totalearning from ordervalue
    void completeDelivery(double orderValue);

    // getters
    string getVehicleType() const { return vehicleType; }

    int getCompletedDeliveries() const { return completedDeliveries; }

    double getTotalEarnings() const { return totalEarnings; }

    // overloading the prefix ++ operator
    DeliveryDriver &operator++();
    // overloading the postfix ++ operator
    DeliveryDriver operator++(int dummy);
};

#endif