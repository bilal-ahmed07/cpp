#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = nullptr;

void insertAtEnd(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Element " << value << " inserted at the end." << endl;
}

void deleteFromEnd() {
    if (head == nullptr) {
        cout << "List is empty. Nothing to delete." << endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    } else {
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
    cout << "Element deleted from the end." << endl;
}

void searchElement(int value) {
    Node* temp = head;
    int position = 1;
    while (temp != nullptr) {
        if (temp->data == value) {
            cout << "Element " << value << " found at position " << position << "." << endl;
            return;
        }
        temp = temp->next;
        position++;
    }
    cout << "Element " << value << " not found in the list." << endl;
}

void displayList() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* temp = head;
    cout << "List elements: ";
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

bool isListEmpty() {
    return head == nullptr;
}

int main() {
    int choice, value;
    while (true) {
        cout << "\n1. Insert an element at the end";
        cout << "\n2. Delete an element from the end";
        cout << "\n3. Search an element";
        cout << "\n4. Display List";
        cout << "\n5. Is List Empty";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> value;
                insertAtEnd(value);
                break;
            case 2:
                deleteFromEnd();
                break;
            case 3:
                cout << "Enter the value to search: ";
                cin >> value;
                searchElement(value);
                break;
            case 4:
                displayList();
                break;
            case 5:
                if (isListEmpty()) {
                    cout << "List is empty." << endl;
                } else {
                    cout << "List is not empty." << endl;
                }
                break;
            case 6:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}