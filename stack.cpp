#include <iostream>
using namespace std;

int st[10];
int top = -1;
void push(int x) {
    if (top == 9) {
        cout << "The Stack is full" << endl;
    } else {
        top = top + 1;
        st[top] = x;
        cout << st[top] << " is added" << endl;
    }
}

void Pop(){
    if (top < 0) {
        cout << "The Stack is empty" << endl;
    } else {
        cout << st[top] << " is removed from stack" << endl;
        top -= 1;
    }
}

void Display() {
    if (top > 0 && top < 10) {
        cout << "Stack elements are: ";
        for (int i = 0; i <= top; i++) {
            cout << st[i] << " ";
        }
        cout << endl;
    }
}

void TopElement() {
    if (top < 0) {
        cout << "The Stack is empty" << endl;
        return;
    }
    cout << "Top element is: " << st[top] << endl;
    
}

// int main() {
//     int choice, x;

//     while (true) {
//         cout << "\nStack Menu:" <<endl;
//         cout << "1. Push" << endl;
//         cout << "2. Pop" << endl;
//         cout << "3. Top Element" << endl;
//         cout << "4. Display" << endl;
//         cout << "5. Exit" << endl;
//         cout << "Enter: ";
//         cin >> choice;

//         if (choice == 1) {
//             cout << "Enter element to push in stack: ";
//             cin >> x;
//             push(x);
//         } else if (choice == 2) {
//             Pop();
//         } else if (choice == 3) {
//             TopElement();
//         } else if (choice == 4) {
//             Display();
//         } else if (choice == 5) {
//             break;
//         }
//     }
// }

int main() {
    push(5);
    push(2);
    push(3);
    Pop();
    push(6);
    push(9);
    push(3);
    Display();
    TopElement();
}