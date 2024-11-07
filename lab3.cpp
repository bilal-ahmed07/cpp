// #include<iostream>
// using namespace std;

// int main() {
//     cout << "Bilal Ahmed - 056" << endl;
//     int x;
//     int n;
//     x = 33;
//     int a[10] = {11,22,33,36,45,52,57,60,64,78};
//     n = sizeof(a)/sizeof(a[0]);
//     //Binary Search
//     int low = 0;
//     int high = n-1;
//     int mid = (low + high) / 2;
//     while (low <= high) {
//         if (a[mid] == x) {
//             cout << "33 is present at index " << mid << endl;
//             return 0;
//         } else if(x < a[mid]) {
//             high = mid - 1;
//             mid = (low + high) / 2;
//         } else if(x > a[mid]) {
//             low = mid + 1;
//             mid = (low + high) / 2;
//         }
//     }
//     cout << "Element not in array" << endl; 
//     // for (int i = 0; i < n; i++) {
//     //     if (x > a[i] && x < a[i+1]) {
//     //         cout << "Item should be placed at " << i+1 << endl;
//     //         return 0;
//     //     }
//     // }
// }

//Task 3

// #include<iostream>
// using namespace std;
// int main() {
//     cout << "Bilal Ahmed - 056" << endl;
//     int numbers[10]={11,22,33,36,45,52,57,60,64,78};
//     int n = sizeof(numbers)/sizeof(numbers[0]);
//     int target1 = 52;
//     int target2 = 33;

//     int low = 0;
//     int high = n-1;
//     int mid = (low + high) / 2;
//     while (low <= high) {
//         if (numbers[mid] ==  target1) {
//             cout << "52 is present at index " << mid << endl;
//             return 0;
//         } else if(target1 < numbers[mid]) {
//             high = mid - 1;
//             mid = (low + high) / 2;
//         } else if(target1 > numbers[mid]) {
//             low = mid + 1;
//             mid = (low + high) / 2;
//         }
//     }
// }

#include<iostream>
using namespace std;

int main() {
    cout << "Bilal Ahmed - 056" << endl;
    int numbers[10]={11,22,33,36,45,52,57,60,64,78};
    int n = sizeof(numbers)/sizeof(numbers[0]);
    int x = 78;
    int low = 0;
    int high = n-1;
    int mid = (low + high) / 2;
    while (low <= high) {
        if (numbers[mid] ==  x) {
            for(int i = mid;i < n;i++) {
                numbers[i] = numbers[i+1];
            }
            n--;
            for (int i = 0;i < n;i++) {
                cout << numbers[i] << " ";
            }
            break;
        } else if(x < numbers[mid]) {
            high = mid - 1;
            mid = (low + high) / 2;
        } else if(x > numbers[mid]) {
            low = mid + 1;
            mid = (low + high) / 2;
        }
    }
    cout << endl << x << " is deleted";
}