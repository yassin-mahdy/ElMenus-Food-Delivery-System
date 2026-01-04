/*
 * Name: YASSIN MOHAMED MAHDY
 * ID: 20246150
 *
 * Name: MOHAMED HESHAM ABD ELHAMID
 * ID: 20247009
 *
 * Group: G5
 */

#include "Order.h"

// default constructor that sets all  0 ,nullptr, ""
Order::Order()
    : orderId(""), itemCount(0), capacity(0), customer(nullptr),
      driver(nullptr), items(nullptr)
{
    totalOrders++;
    status = OrderStatus::PENDING;
}

// Paramatarized constructor that only takes string id and object pointer of type Customer as arguements
Order::Order(string id, Customer *cust)
    : orderId(id), customer(cust), driver(nullptr),
      items(nullptr), itemCount(0), capacity(0)
{
    status = OrderStatus::PENDING;
    // increment total orders
    totalOrders++;
}

// copy constructor
Order::Order(const Order &obj)
    : orderId(obj.orderId), customer(obj.customer),
      driver(obj.driver), itemCount(obj.itemCount),
      capacity(obj.capacity), status(obj.status)
{
    // increment total orders
    totalOrders++;
    // checks if the source object has items in the items array then copies them
    if (capacity > 0)
    {
        items = new FoodItem[capacity];

        for (int i = 0; i < itemCount; i++)
        {
            items[i] = obj.items[i];
        }
    }
    else
    {
        items = nullptr;
    }
}
// destructor
Order::~Order()
{
    delete[] items; // free memory
    items = nullptr;
}

// function that takes a FoodItem object reference as an arguements, adds a new item to items array and
// dynamically resizes if there is no space available
void Order::addItem(const FoodItem &item)
{
    // check if the array isn't initialized
    if (itemCount == 0)
    {
        capacity = 1;
        items = new FoodItem[capacity]; // allocate items array dynamically
        items[0] = item;
        itemCount = 1;
        return;
    }

    // if full size, resize
    if (itemCount == capacity)
    {
        // resize
        capacity *= 2;
        FoodItem *newarr = new FoodItem[capacity];
        // copy items into new array
        for (int i = 0; i < itemCount; i++)
        {
            newarr[i] = items[i];
        }
        // free memory of old array
        delete[] items;
        items = newarr; // assign the old array to the address of the new array
    }
    // adding mechanism
    items[itemCount] = item;
    itemCount++; // increment the itemCount
}

// function that updates the status
void Order::updateStatus(OrderStatus newStatus)
{
    status = newStatus;
    if (newStatus == OrderStatus::DELIVERED)
    {
        double total = calculateTotal();
        if (driver != nullptr)
        {

            driver->completeDelivery(total);
            (*driver)++;
        }
        if (customer != nullptr)
        {
            *customer += total / 10;
        }
    }
}

// Calculates the total cost of a whole order, no params required
double Order::calculateTotal() const
{
    double total = 0;
    for (int i = 0; i < itemCount; i++)
    {
        total += items[i].calculateItemTotal();
    }
    return total;
}

// Displays complete order details (ID, customer, driver, status, items, price)
void Order::displayOrder() const
{
    cout << "orderId: " << orderId << endl;
    if (customer != nullptr)
    {
        cout << "Customer info: " << endl;
        customer->displayInfo();
    }
    else
    {
        cout << "There is no customer" << endl;
    }
    if (driver != nullptr)
    {
        cout << "Driver's info: " << endl;
        driver->displayInfo();
    }
    else
    {
        cout << "There is no driver. " << endl;
    }
    if (itemCount > 0)
    {
        cout << "Items: " << endl;
        for (int i = 0; i < itemCount; i++)
        {
            items[i].displayItem();
        }
        cout << "Total price: " << calculateTotal() << endl;
    }
    else
    {
        cout << "No items in the order: " << endl;
    }
    cout << "Order Status: ";
    switch (status)
    {
    case OrderStatus::PENDING:
        cout << "Pending";
        break;
    case OrderStatus::PREPARING:
        cout << "Preparing";
        break;
    case OrderStatus::OUT_FOR_DELIVERY:
        cout << "Out for delivery";
        break;
    case OrderStatus::DELIVERED:
        cout << "Delivered";
        break;
    case OrderStatus::CANCELLED:
        cout << "Cancelled";
        break;
    default:
        cout << "Unknown";
        break;
    }
    cout << endl;
}

// allows adding a new FoodItem object to the items array using addItem() function
Order &Order::operator+=(const FoodItem &food)
{
    addItem(food);
    return *this;
}

// Returns the item at the given index (modifiable)
FoodItem &Order::operator[](int index)
{
    if (index < 0 || index >= itemCount)
    {
        throw out_of_range("Invalid index in Order::operator[]");
    }

    return items[index];
}

// Returns the item at the given index (non-modifiable)
const FoodItem &Order::operator[](int index) const
{
    if (index < 0 || index >= itemCount)
    {
        throw out_of_range("Invalid index in Order::operator[]");
    }

    return items[index];
}

// Prints order details
ostream &operator<<(ostream &out, const Order &obj)
{
    out << "Order id: " << obj.orderId << endl;
    if (obj.customer != nullptr)
    {
        out << "Customer's info: " << endl;
        out << "Customer's info:\n";
        out << "Name: " << obj.customer->getName() << "\n";
        out << "ID: " << obj.customer->getUserID() << "\n";
        out << "Phone: " << obj.customer->getPhoneNumber() << "\n";
        out << "Address: " << obj.customer->getdeliveryAddress() << "\n";
        out << "Loyalty Points: " << obj.customer->getloyaltyPoints() << "\n";
    }
    else
    {
        out << "No customer assigned." << endl;
    }
    if (obj.driver != nullptr)
    {
        out << "Driver's info: " << endl;
        out << "Driver Name: " << obj.driver->getName() << "\n";
        out << "Driver ID: " << obj.driver->getUserID() << "\n";
        out << "Vehicle: " << obj.driver->getVehicleType() << "\n";
        out << "Completed deliveries: " << obj.driver->getCompletedDeliveries() << "\n";
        out << "Total earnings: " << obj.driver->getTotalEarnings() << "\n";
    }
    else
    {
        out << "No driver assigned" << endl;
    }
    if (obj.itemCount > 0)
    {
        out << "Items: " << endl;
        for (int i = 0; i < obj.itemCount; i++)

            out << obj.items[i].getItemname()
                << " x" << obj.items[i].getQuantity()
                << " @ " << obj.items[i].getPrice()
                << " = " << obj.items[i].calculateItemTotal() << "\n";
    }
    else
    {
        out << "No items in the order" << endl;
    }
    out << "Order Status: ";
    switch (obj.status)
    {
    case OrderStatus::PENDING:
        out << "Pending";
        break;
    case OrderStatus::PREPARING:
        out << "Preparing";
        break;
    case OrderStatus::OUT_FOR_DELIVERY:
        out << "Out for delivery";
        break;
    case OrderStatus::DELIVERED:
        out << "Delivered";
        break;
    case OrderStatus::CANCELLED:
        out << "Cancelled";
        break;
    default:
        out << "Unknown";
        break;
    }

    out << endl;
    return out;
}

// Check if (order 1 total > order 2 total) is true
bool operator>(const Order &order1, const Order &order2)
{
    return order1.calculateTotal() > order2.calculateTotal();
}

// combines 2 orders into 1 new order
Order operator+(const Order &order1, const Order &order2)
{
    Order newOrder;
    newOrder.orderId = order1.orderId + "+" + order2.orderId;
    if (order1.customer == order2.customer)
    {
        newOrder.customer = order1.customer; // then they are the same customer
    }
    else
    {
        newOrder.customer = nullptr; // cause they are different customers now we let the nullptr be there
    }
    newOrder.driver = nullptr; // no driver assigned
    for (int i = 0; i < order1.itemCount; i++)
    {
        newOrder.addItem(order1.items[i]);
    }
    for (int i = 0; i < order2.itemCount; i++)
    {
        newOrder.addItem(order2.items[i]);
    }
    newOrder.status = OrderStatus::PENDING;
    return newOrder;
}

int Order::totalOrders = 0;