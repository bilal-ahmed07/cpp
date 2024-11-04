#include<iostream>
using namespace std;

int main() {
    int x,n;

    cout << "Length of array: ";
    cin >> n;

    int a[n];
    cout << "Enter the elements of array: " << endl;
    for(int i=0;i<n;i++) {
        cout << "Enter element at " << i+1 << ": ";
        cin >> a[i];
    }

    cout << "Enter number: ";
    cin >> x;

    //Binary Search
    int low = 0;
    int high = n-1;
    int mid = (low + high) / 2;
    while (low <= high) {
        if (a[mid] == x) {
            cout << "Element is present at index " << mid << endl;
            return 0;
        } else if(x < a[mid]) {
            high = mid - 1;
            mid = (low + high) / 2;
        } else if(x > a[mid]) {
            low = mid + 1;
            mid = (low + high) / 2;
        }
    }
    cout << "Element not in array" << endl; 
    
    for (int i = 0; i < n; i++) {
        if (x > a[i] && x < a[i+1]) {
            cout << "Item should be placed at " << i+1 << endl;
            return 0;
        }
    }
}
    
