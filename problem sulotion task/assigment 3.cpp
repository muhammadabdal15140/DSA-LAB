#include <iostream>
#include <string>
#include <limits>

using namespace std; 

struct Student {
    string name;
    int id;
};

struct Node {
    Student data;
    Node* prev;
    Node* next;

    Node(const string& name, int id) : prev(nullptr), next(nullptr) {
        data.name = name;
        data.id = id;
    }
};

class QueueManager {
private:
    Node* head;
    Node* tail;
    int count;

public:
    QueueManager() : head(nullptr), tail(nullptr), count(0) {}

    ~QueueManager() {
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
    }

    void addStudent(const string& name, int id) {
        Node* newNode = new Node(name, id);
        
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
        cout << name << " (ID: " << id << ") has been added to the queue." << endl;
    }

    void serveStudent() {
        if (head == nullptr) {
            cout << "The queue is empty. No T-shirts to give out right now." << endl;
            return;
        }

        string servedName = head->data.name;
        Node* oldHead = head;

        head = head->next;
        
        if (head == nullptr) {
            tail = nullptr;
        }
        else {
            head->prev = nullptr;
        }

        delete oldHead;
        count--;

        cout << "T-shirt served! " << servedName << " has been removed from the front of the line." << endl;
    }

    void removeStudent(int id) {
        if (head == nullptr) {
            cout << "The queue is empty. Cannot remove student." << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr && current->data.id != id) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Error: Student with ID " << id << " was not found in the queue." << endl;
            return;
        }

        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }

        cout << current->data.name << " (ID: " << current->data.id << ") has left the queue early." << endl;
        delete current;
        count--;
    }

    void displayQueue() const {
        if (head == nullptr) {
            cout << "The queue is currently empty." << endl;
            return;
        }

        cout << "\n--- Current Code-a-Thon T-Shirt Queue (Front -> Back) ---" << endl;
        Node* current = head;
        int position = 1;
        while (current != nullptr) {
            cout << position << ". " << current->data.name 
                      << " (ID: " << current->data.id << ")" << endl;
            current = current->next;
            position++;
        }
        cout << "--------------------------------------------------------" << endl;
    }

    void countStudents() const {
        cout << "Total students currently waiting in the queue: " << count << endl;
    }
};

void displayMenu() {
    cout << "\n===== Code-a-Thon T-Shirt Queue Menu =====" << endl;
    cout << "1. Add Student to Queue" << endl;
    cout << "2. Serve Student from Front" << endl;
    cout << "3. A Student Leaves (Remove by ID)" << endl;
    cout << "4. Display Queue" << endl;
    cout << "5. Count Students in Queue" << endl;
    cout << "0. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter your choice: ";
}

int getIntInput() {
    int value;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

string getStringInput() {
    string value;
    getline(cin, value);
    return value;
}

int main() {
    QueueManager queue;
    int choice;

    do {
        displayMenu();
        choice = getIntInput();

        switch (choice) {
            case 1: {
                cout << "Enter student's name: ";
                string name = getStringInput();
                cout << "Enter student's ID (integer): ";
                int id = getIntInput();
                queue.addStudent(name, id);
                break;
            }
            case 2: {
                queue.serveStudent();
                break;
            }
            case 3: {
                cout << "Enter the Student ID of the student who is leaving: ";
                int id = getIntInput();
                queue.removeStudent(id);
                break;
            }
            case 4: {
                queue.displayQueue();
                break;
            }
            case 5: {
                queue.countStudents();
                break;
            }
            case 0: {
                cout << "Exiting Code-a-Thon Queue Manager. Goodbye!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a number from the menu (0-5)." << endl;
                break;
            }
        }
    } while (choice != 0);

    return 0;
}