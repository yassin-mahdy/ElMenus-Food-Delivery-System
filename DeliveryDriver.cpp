/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#include "DeliveryDriver.h"

// constructors
DeliveryDriver::DeliveryDriver()
    : User(), vehicleType(""), completedDeliveries(0), totalEarnings(0.0)
{
}
DeliveryDriver::DeliveryDriver(string id, string n, string phoneNum, string vType, int completed, double earnings)
    : User(id, n, phoneNum), vehicleType(vType), completedDeliveries(completed), totalEarnings(earnings)
{
}

// overriding virtual functions
void DeliveryDriver::displayInfo() const
{
    cout << "Driver's name: " << getName() << endl
         << "Driver's ID: " << getUserID() << endl
         << "Driver's phone number: " << getPhoneNumber() << endl
         << "Driver's vehicle type: " << getVehicleType() << endl
         << "Number of completed deliveries: " << getCompletedDeliveries() << endl
         << "Driver's total earnings: " << getTotalEarnings() << endl;
    if (completedDeliveries > 0)
    {
        cout << "Average earnings per delivery: "
             << (totalEarnings / completedDeliveries) << endl;
    }
    else
        cout << "Average earnings per delivery: N/A" << endl;
}

double DeliveryDriver::calculateEarnings() const
{
    return totalEarnings;
}

void DeliveryDriver::completeDelivery(double orderValue)
{
    totalEarnings += orderValue * 0.15;
}

DeliveryDriver &DeliveryDriver::operator++()
{
    ++completedDeliveries;
    return *this;
}

DeliveryDriver DeliveryDriver::operator++(int dummy)
{
    DeliveryDriver temp = *this;
    ++completedDeliveries;
    return temp;
}