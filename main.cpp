#include <iostream>
#include <fstream>
#include <cstring>

#include "Order.h"
#include "DeliveryDriver.h"
#include "Customer.h"
#include "FoodItem.h"
#include "Enums.h"

using namespace std;
const int MAX_CUSTOMERS = 100;
const int MAX_DRIVERS = 50;
const int MAX_ORDERS = 200;

struct OrderRecord
{
    char orderId[20];
    double total;
    int itemCount;
    int status;
};

// Helper functions
int findOrderIndex(Order *list[], int count, const string &id);
void binaryFileStats();
int findDriverIndex(DeliveryDriver *list[], int count, const string &id);
int findCustomerIndex(Customer *list[], int count, const string &id);

// File operations
// Helper function that finds the index of an order object inside a list just from its ID
void saveCompletedOrders(Order *orderList[], int count)
{
    ofstream file("completed_orders.txt");
    if (!file)
    {
        cout << "Error opening file\n";
        return;
    }
    for (int i = 0; i < count; i++)
    {
        if (!orderList[i])
            continue;
        if (orderList[i]->getStatus() == OrderStatus::DELIVERED)
        {
            orderList[i]->displayOrder();
            file << *orderList[i] << "\n";
        }
    }
    file.close();
}

void saveDriverStats(DeliveryDriver *driverList[], int count)
{
    ofstream file("driver_stats.txt");
    if (!file)
    {
        cout << "Error opening file\n";
        return;
    }

    cout << "\n--- Saving Driver Statistics ---\n";

    for (int i = 0; i < count; i++)
    {
        if (!driverList[i])
            continue;

        DeliveryDriver *d = driverList[i];

        // Print to terminal
        cout << "Driver Name: " << d->getName() << "\n"
             << "Driver ID: " << d->getUserID() << "\n"
             << "Completed Deliveries: " << d->getCompletedDeliveries() << "\n"
             << "Total Earnings: " << d->getTotalEarnings() << " EGP\n"
             << "--------------------------------------\n";

        // Write to file
        file << "Driver Name: " << d->getName() << "\n";
        file << "Driver ID: " << d->getUserID() << "\n";
        file << "Completed Deliveries: " << d->getCompletedDeliveries() << "\n";
        file << "Total Earnings: " << d->getTotalEarnings() << " EGP\n";
        file << "--------------------------------------\n";
    }

    file.close();
    cout << "Driver statistics saved to driver_stats.txt\n";
}

void saveOrdersBinary(Order *orderList[], int count)
{
    ofstream file("orders.dat", ios::binary);
    if (!file)
    {
        cout << "Error opening binary file\n";
        return;
    }
    OrderRecord rec;
    for (int i = 0; i < count; i++)
    {

        if (!orderList[i])
            continue;

        memset(rec.orderId, 0, sizeof(rec.orderId));
        strncpy(rec.orderId, orderList[i]->getOrderId().c_str(), sizeof(rec.orderId) - 1);
        rec.total = orderList[i]->calculateTotal();
        rec.itemCount = orderList[i]->getItemCount();
        rec.status = static_cast<int>(orderList[i]->getStatus());
        file.write(reinterpret_cast<char *>(&rec), sizeof(OrderRecord));
    }
    file.close();
}

void loadOrderBinary(int pos)
{
    ifstream file("orders.dat", ios::binary);
    if (!file)
    {
        cout << "Binary file not found\n";
        return;
    }
    OrderRecord rec;
    file.seekg(pos * sizeof(OrderRecord));
    if (!file.read(reinterpret_cast<char *>(&rec), sizeof(OrderRecord)))
    {
        cout << "Record not found\n";
        return;
    }
    cout << "Order ID: " << rec.orderId << endl;
    cout << "Total: " << rec.total << endl;
    cout << "Items: " << rec.itemCount << endl;
    switch (rec.status)
    {
    case 0:
        cout << "Status: PENDING\n";
        break;
    case 1:
        cout << "Status: PREPARING\n";
        break;
    case 2:
        cout << "Status: OUT_FOR_DELIVERY\n";
        break;
    case 3:
        cout << "Status: DELIVERED\n";
        break;
    case 4:
        cout << "Status: CANCELLED\n";
        break;
    default:
        cout << "Status: UNKNOWN\n";
        break;
    }
    file.close();
}

void loadOrderBinaryTimed(int pos)
{
    loadOrderBinary(pos);
    cout << "Direct access used\n";
}
int main()
{
    int customerCount = 0;
    int driverCount = 0;
    int orderCount = 0;
    Customer *customers[MAX_CUSTOMERS] = {nullptr};
    DeliveryDriver *drivers[MAX_DRIVERS] = {nullptr};
    Order *orders[MAX_ORDERS] = {nullptr};

    while (true)
    {
        cout << "\nELMENUS MANAGEMENT SYSTEM v1.0\n";
        cout << "USER MANAGEMENT\n";
        cout << "1.Register New Customer\n";
        cout << "2.Register New Delivery Driver\n";
        cout << "ORDER MANAGEMENT\n";
        cout << "3.Create New Order\n";
        cout << "4.Add Items to Order\n";
        cout << "5.Assign Driver to Order\n";
        cout << "6.Update Order Status\n";
        cout << "7.Display Order Details\n";
        cout << "INFORMATION & REPORTS\n";
        cout << "8.Display Customer Information\n";
        cout << "9.Display Driver Information\n";
        cout << "10.Compare Two Orders by Total\n";
        cout << "11.Display System Statistics\n\n";
        cout << "FILE OPERATIONS\n";
        cout << "12.Save Completed Orders to File\n";
        cout << "13.Save Driver Statistics to File\n";
        cout << "BONUS FEATURES\n";
        cout << "14.Save Orders to Binary File\n";
        cout << "15.Load Order by Position (0-based)\n";
        cout << "16.Binary File Statistics\n";
        cout << "17. Exit System\n";
        cout << "Choose option: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice)
        {

        case 1:
        {
            if (customerCount >= MAX_CUSTOMERS)
            {
                cout << "Customer storage full\n";
                break;
            }
            string id, name, phone, address;
            int points;
            do
            {
            cout << "Enter Customer ID: ";
            getline(cin, id);
            if(findCustomerIndex(customers,customerCount,id) != -1)
            {
              cout<<"This customer id is already in use Please use another one\n";
            }
            else
            {
                break;
            }
            
            } while (true);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Phone: ";
            getline(cin, phone);
            cout << "Enter Address: ";
            getline(cin, address);
            cout << "Enter number of Loyalty Points: ";
            while (!(cin >> points) || points < 0)
            {
                cout << "Invalid input,Please try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            cout << "Your loyalty points: " << points << endl;
            customers[customerCount] = new Customer(id, name, phone, address, points);
            cout << "Customer registered.\n";
            customerCount++;
            break;
        }

        case 2:
        {
            if (driverCount >= MAX_DRIVERS)
            {
                cout << "Driver storage full\n";
                break;
            }
            string id, name, phone, vehicle;
            do
            {
            cout << "Enter driver ID: ";
            getline(cin, id);
            if(findDriverIndex(drivers,driverCount,id) != -1)
            {
             cout<<"This driver id is already in use Please use another one\n";
            }
            else
            {
                break;
            }
            
            } while (true);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Phone: ";
            getline(cin, phone);
            cout << "Enter Vehicle Type: ";
            getline(cin, vehicle);
            drivers[driverCount] = new DeliveryDriver(id, name, phone, vehicle, 0, 0.0);
            cout << "Driver registered.\n";
            driverCount++;
            break;
        }

        case 3:
        {
            if (orderCount >= MAX_ORDERS)
            {
                cout << "Order storage full\n";
                break;
            }
            string oid, custId;
            do
            {
            cout << "Enter order ID: ";
            getline(cin, oid);
            if(findOrderIndex(orders,orderCount,oid) != -1)
            {
            cout<<"This order id is already in use Please use another one\n";
            }
            else
            {
                break;
            }
            } while (true);
            cout << "Enter Customer ID: ";
            getline(cin, custId);
            int index = findCustomerIndex(customers, customerCount, custId);
            if (index == -1)
            {
                cout << "Customer not found.\n";
                break;
            }
            orders[orderCount] = new Order(oid, customers[index]);
            cout << "Order created.\n";
            orderCount++;
            break;
        }

        case 4:
        {
            string orderid;
            cout << "Enter Order ID: ";
            getline(cin, orderid);
            int idx = findOrderIndex(orders, orderCount, orderid);
            if (idx == -1)
            {
                cout << "Order not found.\n";
                break;
            }
            string item;
            double price;
            int qty;
            cout << "Item name: ";
            getline(cin, item);
            cout << "Price: ";
            while (!(cin >> price) || price < 0)
            {
                cout << "Invalid input,Please enter a positive number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            cout << "The price is: " << price << endl;
            cout << "Quantity: ";
            while (!(cin >> qty) || qty < 0)
            {
                cout << "Invalid input, please enter a positive quantity: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cin.ignore(1000, '\n');
            cout << "The quantity is: " << qty << endl;
            FoodItem it(item, price, qty);
            orders[idx]->addItem(it);
            cout << "Item added.\n";
            break;
        }

        case 5:
        {
            string oid, did;
            cout << "Enter Order ID: ";
            getline(cin, oid);
            cout << "Enter Driver ID: ";
            getline(cin, did);
            int o = findOrderIndex(orders, orderCount, oid);
            int d = findDriverIndex(drivers, driverCount, did);
            if (o == -1)
            {
                cout << "Order not found\n";
                break;
            }
            if (d == -1)
            {
                cout << "Driver not found\n";
                break;
            }
            orders[o]->assignDriver(drivers[d]);
            cout << "Driver assigned.\n";
            break;
        }

        case 6:
        {
            string oid;
            cout << "Enter Order ID: ";
            getline(cin, oid);
            int o = findOrderIndex(orders, orderCount, oid);
            if (o == -1)
            {
                cout << "Order not found\n";
                break;
            }
            int s;
            cout << "New status (0-4): ";
            cin >> s;
            cin.ignore();
            if (s < 0 || s > 4)
            {
                cout << "Invalid.\n";
                break;
            }
            orders[o]->updateStatus((OrderStatus)s);
            cout << "Status updated.\n";
            break;
        }

        case 7:
        {
            string oid;
            cout << "Enter Order ID: ";
            getline(cin, oid);
            int o = findOrderIndex(orders, orderCount, oid);
            if (o == -1)
            {
                cout << "Order not found\n";
                break;
            }
            orders[o]->displayOrder();
            break;
        }

        case 8:
        {
            string cid;
            cout << "Enter Customer ID: ";
            getline(cin, cid);
            int c = findCustomerIndex(customers, customerCount, cid);
            if (c == -1)
            {
                cout << "Customer not found\n";
                break;
            }
            customers[c]->displayInfo();
            break;
        }

        case 9:
        {
            string did;
            cout << "Enter Driver ID: ";
            getline(cin, did);
            int d = findDriverIndex(drivers, driverCount, did);
            if (d == -1)
            {
                cout << "Driver not found\n";
                break;
            }
            drivers[d]->displayInfo();
            break;
        }

        case 10:
        {
            string id1, id2;
            // Ask user for both order IDs
            cout << "Enter the first order ID: ";
            getline(cin, id1);

            cout << "Enter the second order ID: ";
            getline(cin, id2);
            // find the index of each order by using helper function findOrderIndex
            int index1 = findOrderIndex(orders, orderCount, id1);
            int index2 = findOrderIndex(orders, orderCount, id2);

            if (index1 == -1 || index2 == -1)
            {
                cout << "One or both orders are not found\n";
                break;
            }
            // Compare totals using overloaded > operator
            if (*orders[index1] > *orders[index2])
                cout << id1 << " has a greater total\n";
            else
                cout << id2 << " has a greater or equal total\n";

            break;
        }

        case 11:
        {
            cout << "\n=== SYSTEM STATISTICS ===\n";

            cout << "Total Customers: " << customerCount << endl;
            cout << "Total Drivers: " << driverCount << endl;
            cout << "Total Orders: " << orderCount << endl;

            int completed = 0;

            for (int i = 0; i < orderCount; i++)
            {
                if (orders[i] != nullptr &&
                    orders[i]->getStatus() == OrderStatus::DELIVERED)
                {
                    completed++;
                }
            }

            cout << "Completed Orders: " << completed << endl;
            break;
        }

        case 12:
        {
            saveCompletedOrders(orders, orderCount);
            cout << "Completed orders saved.\n";
            break;
        }

        case 13:
        {
            saveDriverStats(drivers, driverCount);
            cout << "Driver statistics saved.\n";
            break;
        }

        case 14:
        {
            saveOrdersBinary(orders, orderCount);
            cout << "Orders saved in binary file.\n";
            break;
        }

        case 15:
        {
            int pos;
            cout << "Enter record position (0-based): ";
            while (!(cin >> pos) || pos < 0)
            {
                cout << "Invalid input,Please try again: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            loadOrderBinary(pos);
            break;
        }

        case 16:
        {
            binaryFileStats();
            break;
        }

        case 17:
        {
            cout << "Exiting system... Cleaning allocated memory.\n";

            // Delete all orders
            for (int i = 0; i < orderCount; i++)
            {
                delete orders[i];
                orders[i] = nullptr;
            }

            // Delete all customers
            for (int i = 0; i < customerCount; i++)
            {
                delete customers[i];
                customers[i] = nullptr;
            }

            // Delete all drivers
            for (int i = 0; i < driverCount; i++)
            {
                delete drivers[i];
                drivers[i] = nullptr;
            }

            cout << "Cleanup complete. Goodbye.\n";
            return 0; // exit the entire program
        }
        }
    }
}

// Helper function that finds the index of an order object inside a list just from its ID
int findOrderIndex(Order *list[], int count, const string &id)
{
    for (int i = 0; i < count; i++)
    {
        if (list[i] && list[i]->getOrderId() == id)
            return i;
    }
    return -1;
}

void binaryFileStats()
{
    ifstream file("orders.dat", ios::binary);
    if (!file)
    {
        cout << "orders.dat not found.\n";
        return;
    }

    // Move to end of file to measure size
    file.seekg(0, ios::end);
    long long size = file.tellg();

    int recordCount = size / sizeof(OrderRecord);

    cout << "\n=== Binary File Statistics ===\n";
    cout << "File size: " << size << " bytes\n";
    cout << "Number of OrderRecord entries: " << recordCount << "\n\n";

    file.close();
}

int findCustomerIndex(Customer *list[], int count, const string &id)
{
    for (int i = 0; i < count; ++i)
        if (list[i] && list[i]->getUserID() == id) // User class uses getUserID()
            return i;
    return -1;
}

int findDriverIndex(DeliveryDriver *list[], int count, const string &id)
{
    for (int i = 0; i < count; ++i)
        if (list[i] && list[i]->getUserID() == id)
            return i;
    return -1;
}
