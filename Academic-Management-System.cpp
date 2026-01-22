#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
protected:
    string name;
    int id;
public:
    Person(string n, int i) : name(n), id(i) {}
    virtual void displayInfo() = 0; 
    int getId() { return id; }
};

class Student : public Person {
private:
    float gpa;
public:
    Student(string n, int i, float g) : Person(n, i), gpa(g) {}

    void displayInfo() override {
        cout << "[Student Log] ID: " << id << " | Name: " << name << " | GPA: " << gpa << endl;
    }

    float getGpa() { return gpa; }
};

struct Node {
    Student* data;
    Node* next;
};

class UniversitySystem {
private:
    Node* head;
public:
    UniversitySystem() : head(nullptr) {}

    void addStudent(string name, int id, float gpa) {
        Student* newStudent = new Student(name, id, gpa);
        Node* newNode = new Node{newStudent, head};
        head = newNode;
        cout << "Done! Student " << name << " has been added to the system.\n";
    }

    void displayAll() {
        Node* temp = head;
        if (!temp) {
            cout << "The system is currently empty.\n";
            return;
        }
        cout << "\n--- Current University Records ---\n";
        while (temp) {
            temp->data->displayInfo();
            temp = temp->next;
        }
    }

    void searchById(int id) {
        Node* temp = head;
        while (temp) {
            if (temp->data->getId() == id) {
                cout << "Match Found: ";
                temp->data->displayInfo();
                return;
            }
            temp = temp->next;
        }
        cout << "Sorry, no student found with ID: " << id << endl;
    }

    ~UniversitySystem() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current->data;
            delete current;
            current = next;
        }
    }
};

int main() {
    UniversitySystem myUni;
    int choice, id;
    string name;
    float gpa;

    cout << "Welcome to the Academic Management System v1.0\n";

    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Add a new student\n";
        cout << "2. View all students\n";
        cout << "3. Search for a student by ID\n";
        cout << "4. Close the program\n";
        cout << "Your Choice: ";
        cin >> choice;

        if (choice == 4) {
            cout << "Shutting down system. Goodbye!\n";
            break;
        }

        switch (choice) {
            case 1:
                cout << "Enter student name: "; cin >> name;
                cout << "Enter student ID: "; cin >> id;
                cout << "Enter GPA: "; cin >> gpa;
                myUni.addStudent(name, id, gpa);
                break;
            case 2:
                myUni.displayAll();
                break;
            case 3:
                cout << "Enter the ID you're looking for: "; cin >> id;
                myUni.searchById(id);
                break;
            default:
                cout << "Oops! Invalid input, please try again.\n";
        }
    }
    return 0;
}
