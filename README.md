# ElMenus Food Delivery Management System

A C++ object-oriented backend system that simulates a food delivery platform similar to Talabat or Uber Eats.  
This project focuses on applying core and advanced OOP principles, dynamic memory management, and clean software design.

The system manages customers, delivery drivers, food items, and orders through a menu-driven console application.

---

## 🧠 Key Concepts & Technologies

- C++ (Object-Oriented Programming)
- Abstraction & Polymorphism
- Inheritance
- Aggregation & Composition
- Dynamic Memory Management (Rule of Three)
- Operator Overloading
- Enums & Static Members
- File I/O (Text & Binary – Bonus)
- Git & GitHub (version control practice)

---

## 🏗️ System Overview

### Main Components
- **Users**
  - Abstract base class `User`
  - Derived classes: `Customer`, `DeliveryDriver`
- **Orders**
  - Aggregates customers and drivers
  - Composes food items using a dynamically resized array
- **Food Items**
  - Represents menu items with quantity and pricing
- **Order Lifecycle**
  - Managed using `OrderStatus` enum

---

## 📂 Project Structure
├── Enums.h

├── User.h / User.cpp

├── Customer.h / Customer.cpp

├── DeliveryDriver.h / DeliveryDriver.cpp

├── FoodItem.h / FoodItem.cpp

├── Order.h / Order.cpp

├── main.cpp

└── README.md


---

## ✨ Features

- Create and manage customers and delivery drivers
- Dynamic addition of food items to orders
- Driver assignment and earnings tracking
- Order status management (Pending → Delivered / Cancelled)
- Customer loyalty points system
- Operator overloading (`+=`, `+`, `<<`, `>`, `[]`, `++`)
- Menu-driven interface with input validation
- Persistent storage using file operations

---

## 📁 File Operations

- **completed_orders.txt**
  - Stores completed order details
- **driver_stats.txt**
  - Stores driver earnings and delivery statistics
-  Binary file support for direct O(1) order access

---

## ▶️ How to Run

1. Compile all `.cpp` files using a C++17-compatible compiler
2. Run the generated executable
3. Use the console menu to interact with the system

Example:
```bash
g++ *.cpp -std=c++17 -o ElMenus
./ElMenus

