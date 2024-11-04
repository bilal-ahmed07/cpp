#include <iostream>

// Function prototype for InsertionSort
void InsertionSort(int n, int* a);
void BubbleSort(int n, int* a);
void SelectionSort(int n, int* a); 

int main() {
    int n;
    std::cout << "Bilal Ahmed - 056" << std::endl;
    std::string choice;
    std::cout << "Enter Size of array: ";
    std::cin >> n;
    
    if (n <= 0) { //checking size
        std::cout << "Array size must be greater than 0." << std::endl;
        return 1;
    }

    int* a = new int[n];
    std::cout << "Enter " << n << " elements: " << std::endl;
    
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter " << i+1 << " element: ";
        std::cin >> a[i];
    }

    std::cout << "Which sort you want to do (1: Insertion Sort, 2: Bubble Sort, 3: Selection Sort): ";
    std::cin >> choice;
    if (choice == "1") {
        InsertionSort(n, a);
    } else if (choice == "2") {
        BubbleSort(n,a);
    } else if(choice == "3") {
        SelectionSort(n,a);
    }

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;

    delete[] a; 
    return 0;
}

//Insertion Sort
void InsertionSort(int n, int* a) {
    for (int i = 1; i < n; i++) {
        int x = a[i]; 
        int j = i - 1;
        while (j >= 0 && a[j] > x) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
}

//Bubble Sort
void BubbleSort(int n, int* a) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++){
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void swap(int *xPointer, int *yPointer) {  //for selection sort
    int temp = *xPointer;
    *xPointer = *yPointer;
    *yPointer = temp;
}

//Selection Sort
void SelectionSort(int n, int* a) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;  
        for (int j = i+1; j < n; j++)  
        if (a[j] < a[min_idx])  
            min_idx = j;
        swap(&a[min_idx], &a[i]);  
    }  
}