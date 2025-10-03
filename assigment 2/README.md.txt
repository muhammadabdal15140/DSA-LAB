# 🚌 BRT Peshawar Passenger Queue Management (Singly Linked List)

This project is a solution to a Data Structures lab task that models the passenger queue management system for the **Bus Rapid Transit (BRT) in Peshawar, Pakistan**, using a **singly linked list** implemented in C++.

---

## 📌 Project Overview

The core purpose of this application is to demonstrate the practical use of a linked list to manage a dynamic queue. Each passenger is represented as a **node** in the list, and various boarding scenarios (normal, emergency, special booking) are simulated using standard linked list operations.

---

## 🛠 Implementation Details

The `brt_linkedlist.cpp` file contains the implementation of the `Node` struct and the `LinkedList` class.

### Key Operations Implemented:

| Scenario | Linked List Method | Time Complexity | Description |
| :--- | :--- | :--- | :--- |
| **Emergency Boarding** | `insertAtBeginning(int id)` | $O(1)$ | A passenger bypasses the queue and joins the front (head). |
| **Normal Boarding** | `insertAtEnd(int id)` | $O(N)$ | A passenger joins the back of the queue (tail). |
| **Special Booking** | `insertAtPosition(int id, int pos)` | $O(P)$ | A passenger joins at a specific position $P$. |
| **Bus Arrival** | `deleteFromBeginning()` | $O(1)$ | The passenger at the front boards the bus and is removed. |

The implementation also includes a **Destructor (`~LinkedList`)** to ensure all dynamically allocated memory (nodes) is properly freed, preventing memory leaks.

---

## 🚀 How to Compile and Run

This project can be compiled using a standard C++ compiler (like g++).

### Prerequisites
* A C++ compiler (e.g., g++, clang)

### Compilation

Navigate to the directory containing `brt_linkedlist.cpp` and run:

```bash
g++ brt_linkedlist.cpp -o brt_queue