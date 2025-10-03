#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        Node* nextNode = nullptr;
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }

    void insertAtBeginning(int value);
    void insertAtEnd(int value);
    void insertAtPosition(int value, int pos);
    bool deleteFromBeginning(int* removedValue = nullptr);
    void display() const;
};

void LinkedList::insertAtBeginning(int value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void LinkedList::insertAtEnd(int value) {
    Node* newNode = new Node(value);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}

void LinkedList::insertAtPosition(int value, int pos) {
    if (pos < 1) {
        throw out_of_range("Position must be 1 or greater.");
    }

    if (pos == 1) {
        insertAtBeginning(value);
        return;
    }

    Node* newNode = new Node(value);

    Node* current = head;
    for (int i = 1; i < pos - 1 && current != nullptr; ++i) {
        current = current->next;
    }

    if (current == nullptr) {
        delete newNode;
        throw out_of_range("Position is out of bounds for the current queue size.");
    }

    newNode->next = current->next;
    current->next = newNode;
}

bool LinkedList::deleteFromBeginning(int* removedValue) {
    if (head == nullptr) {
        return false;
    }

    Node* nodeToDelete = head;

    if (removedValue != nullptr) {
        *removedValue = nodeToDelete->data;
    }

    head = head->next;

    delete nodeToDelete;

    return true;
}

void LinkedList::display() const {
    Node* current = head;
    if (current == nullptr) {
        cout << "Queue is empty.\n";
        return;
    }

    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << "\n";
}

int main() {
    LinkedList list;

    const int ID_NORMAL_1 = 101;
    const int ID_NORMAL_2 = 102;
    const int ID_NORMAL_3 = 103;
    const int ID_EMERGENCY = 999;
    const int ID_SPECIAL_BOOKING = 555;

    cout << "--- BRT Peshawar Passenger Queue Simulation ---\n\n";

   
    list.insertAtEnd(ID_NORMAL_1);
    list.insertAtEnd(ID_NORMAL_2);
    list.insertAtEnd(ID_NORMAL_3);
    cout << "Initial Queue after adding passengers:\n";
    list.display();
    cout << "\n";

    
    list.insertAtBeginning(ID_EMERGENCY);
    cout << "After adding an emergency passenger at beginning:\n";
    list.display();
    cout << "\n";

    
    try {
        list.insertAtPosition(ID_SPECIAL_BOOKING, 2);
        cout << "After inserting special booking passenger at position 2:\n";
        list.display();
    } catch (const out_of_range& e) {
        cerr << "Error inserting at position: " << e.what() << "\n";
    }
    cout << "\n";

    
    int removed;
    if (list.deleteFromBeginning(&removed)) {
        cout << "After first passenger boards (deletion):\n";
        list.display();
    } else {
        cout << "Queue was empty, no passenger boarded.\n";
    }
    cout << "\n--- Simulation End ---\n";

    return 0;
}