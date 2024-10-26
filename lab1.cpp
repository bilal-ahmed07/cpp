//Task 1
// #include<iostream>
// using namespace std;
// int main() {
//     int a, b, c;
//     cout << "Enter num 1: ";
//     cin >> a;
//     cout << "Enter num 2: ";
//     cin >> b;
//     cout << "Enter num 3: ";	    cin >> c;
//     if (a<b && a<c) {
//         cout << a << " is smaller";
//     } else if (b<a && b<c) {
//         cout << b << " is smaller";
//     } else {
//         cout << c << " is smaller";
//     }
//     return 0;
// }

//Task 2
#include<iostream>
using namespace std;
int main() {
    int a[10];
    for (int i = 0; i < 10; i++) {
        cout << "Enter number " << i + 1 << ": ";	        cin >> a[i];
    }
    for (int i = 0; i < 9; i++) {
       for (int j= i+1; j<10; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << a[i] << " ";
    }
}


//Task 3
// #include <iostream>
// struct student{
//     std::string name;
//     int id,age;
// };
// int main() {
//     student studt;
//     std::cout << "Enter Student id: ";
//     std::cin >> studt.id;
//     std::cout << "Enter Student name: ";
//     std::cin >> studt.name;
//     std::cout << "Enter Student age: ";
//     std::cin >> studt.age;

//     std::cout << "Student Id: " << studt.id
//     << "\nStudent Name: " << studt.name
//     << "\nStudent Age: " << studt.age;
// }

//Task 4
// #include <iostream>
// struct Student {
//     int id;
//     std::string name;
//     int age;
// };
// int main() {
//     Student* studt = new Student;
//     std::cout << "Enter Student ID: ";
//     std::cin >> studt->id; 
//     std::cout << "Enter Student name: ";
//     std::cin >> studt->name;
//     std::cout << "Enter Student age: ";
//     std::cin >> studt->age;

//     std::cout << "Student Id: " << studt->id
//               << "\nStudent Name: " << studt->name
//               << "\nStudent Age: " << studt->age;
//     delete studt;
//     return 0;
// }