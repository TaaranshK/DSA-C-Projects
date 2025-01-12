#include <iostream>
#include <limits>
#include <time.h>
#include <string>
#include <cstring> // For memcpy

using namespace std;

// Constants for screen dimensions and array sizes
const int SCREEN_WIDTH = 910;  // Width of the screen
const int SCREEN_HEIGHT = 750; // Height of the screen
const int arrSize = 130;       // Size of the array to sort
const int rectSize = 7;        // Size of each rectangle in the visualizer

// Global variables for the array and backup
int arr[arrSize];  // Main array to sort
int Barr[arrSize]; // Backup array for randomization

bool complete = false; // Flag to indicate if sorting is complete

// Function to visualize the sorting process (console-based)
void visualize(int x = -1, int y = -1, int z = -1) {
    // Placeholder for visualization
    // In practice, implement console output or logging to show progress
    if (x != -1 && y != -1) {
        cout << "Swapping index " << x << " and " << y << endl;
    }
}

// Function to perform in-place heap sort
void inplaceHeapSort(int* input, int n) {
    // Building the heap
    for (int i = 1; i < n; i++) {
        int childIndex = i;
        int parentIndex = (childIndex - 1) / 2;

        // Adjust the heap
        while (childIndex > 0) {
            if (input[childIndex] > input[parentIndex]) {
                // Swap the elements
                int temp = input[parentIndex];
                input[parentIndex] = input[childIndex];
                input[childIndex] = temp;

                visualize(parentIndex, childIndex); // Visualize the swap
            } else {
                break; // No need to swap, break the loop
            }

            childIndex = parentIndex; // Move up the heap
            parentIndex = (childIndex - 1) / 2; // Update parent index
        }
    }

    // Sorting the heap
    for (int heapLast = n - 1; heapLast >= 0; heapLast--) {
        // Swap the first element with the last element of the heap
        int temp = input[0];
        input[0] = input[heapLast];
        input[heapLast] = temp;

        // Restore the heap property
        int parentIndex = 0;
        int leftChildIndex = 2 * parentIndex + 1;
        int rightChildIndex = 2 * parentIndex + 2;

        while (leftChildIndex < heapLast) {
            int maxIndex = parentIndex;

            // Check if left child is greater than parent
            if (input[leftChildIndex] > input[maxIndex]) {
                maxIndex = leftChildIndex;
            }
            // Check if right child is greater than current max
            if (rightChildIndex < heapLast && input[rightChildIndex] > input[maxIndex]) {
                maxIndex = rightChildIndex;
            }
            if (maxIndex == parentIndex) {
                break; // Heap property is restored
            }

            // Swap parent with the maximum child
            int temp = input[parentIndex];
            input[parentIndex] = input[maxIndex];
            input[maxIndex] = temp;

            visualize(maxIndex, parentIndex); // Visualize the swap

            parentIndex = maxIndex; // Move down the heap
            leftChildIndex = 2 * parentIndex + 1; // Update left child index
            rightChildIndex = 2 * parentIndex + 2; // Update right child index
        }
    }
}

// Function to partition the array for Quick Sort
int partition_array(int a[], int si, int ei) {
    int count_small = 0;

    // Count the number of elements smaller than or equal to pivot
    for (int i = (si + 1); i <= ei; i++) {
        if (a[i] <= a[si]) {
            count_small++;
        }
    }
    
    // Place the pivot in its correct position
    int c = si + count_small;
    int temp = a[c];
    a[c] = a[si];
    a[si] = temp;
    visualize(c, si); // Visualize the swap

    // Two pointers to partition the array
    int i = si, j = ei;
    while (i < c && j > c) {
        if (a[i] <= a[c]) {
            i++; // Move the left pointer right
        } else if (a[j] > a[c]) {
            j--; // Move the right pointer left
        } else {
            // Swap elements at i and j
            int temp_1 = a[j];
            a[j] = a[i];
            a[i] = temp_1;

            visualize(i, j); // Visualize the swap
            i++; // Move both pointers
            j--;
        }
    }
    return c; // Return the pivot index
}

// Function to perform Quick Sort
void quickSort(int a[], int si, int ei) {
    if (si >= ei) {
        return; // Base case for recursion
    }

    // Partition and recursively sort
    int c = partition_array(a, si, ei);
    quickSort(a, si, c - 1);
    quickSort(a, c + 1, ei);
}

// Function to merge two sorted arrays
void merge2SortedArrays(int a[], int si, int ei) {
    int size_output = (ei - si) + 1; // Size of the output array
    int* output = new int[size_output]; // Temporary output array

    int mid = (si + ei) / 2; // Midpoint for dividing
    int i = si, j = mid + 1, k = 0;

    // Merge the two halves
    while (i <= mid && j <= ei) {
        if (a[i] <= a[j]) {
            output[k] = a[i];
            visualize(i, j); // Visualize the merging
            i++;
        } else {
            output[k] = a[j];
            visualize(i, j); // Visualize the merging
            j++;
        }
        k++;
    }

    // Copy remaining elements from left half
    while (i <= mid) {
        output[k] = a[i];
        visualize(-1, i); // Visualize remaining elements
        i++;
        k++;
    }

    // Copy remaining elements from right half
    while (j <= ei) {
        output[k] = a[j];
        visualize(-1, j); // Visualize remaining elements
        j++;
        k++;
    }

    // Copy sorted elements back to original array
    for (int l = si; l <= ei; l++) {
        a[l] = output[l - si]; // Adjusted index for output array
        visualize(l); // Visualize the sorting
    }
    delete[] output; // Free memory
}

// Function to perform Merge Sort
void mergeSort(int a[], int si, int ei) {
    if (si >= ei) {
        return; // Base case for recursion
    }
    int mid = (si + ei) / 2; // Find midpoint

    // Recursively sort the two halves
    mergeSort(a, si, mid);
    mergeSort(a, mid + 1, ei);

    // Merge the two sorted halves
    merge2SortedArrays(a, si, ei);
}

// Function to perform Bubble Sort
void bubbleSort() {
    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = 0; j < arrSize - 1 - i; j++) {
            if (arr[j + 1] < arr[j]) {
                // Swap the elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                visualize(j + 1, j, arrSize - i); // Visualize the swap
            }
        }
    }
}

// Function to perform Insertion Sort
void insertionSort() {
    for (int i = 1; i < arrSize; i++) {
        int j = i - 1; // Index for sorted portion
        int temp = arr[i]; // Element to be inserted
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j]; // Shift element to the right
            j--;
            visualize(i, j + 1); // Visualize the shifting
        }
        arr[j + 1] = temp; // Insert the element
    }
}

// Function to perform Selection Sort
void selectionSort() {
    int minIndex;
    for (int i = 0; i < arrSize - 1; i++) {
        minIndex = i; // Assume the first element is the minimum
        for (int j = i + 1; j < arrSize; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // Update the minimum index
                visualize(i, minIndex); // Visualize the comparison
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
        visualize(minIndex, i); // Visualize the swap
    }
}

// Function to load backup array into the main array
void load_array_from_backup() {
    memcpy(arr, Barr, sizeof(Barr)); // Load backup array
}

// Function to initialize the array with random values
void initialize() {
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < arrSize; i++) {
        Barr[i] = rand() % SCREEN_HEIGHT; // Random value in range
    }
    load_array_from_backup(); // Load into main array
}

// Main function
int main() {
    int choice;

    // Initialize the array with random values
    initialize();

    // User interface for selecting sorting algorithm
    cout << "Choose a sorting algorithm to visualize:\n";
    cout << "1. In-Place Heap Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "4. Bubble Sort\n";
    cout << "5. Insertion Sort\n";
    cout << "6. Selection Sort\n";
    cout << "Enter your choice (1-6): ";
    
    // Input validation for choice
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid choice. Please enter a number between 1 and 6: ";
        } else {
            break; // Valid choice
        }
    }

    // Execute the chosen sorting algorithm
    switch (choice) {
        case 1:
            inplaceHeapSort(arr, arrSize);
            break;
        case 2:
            quickSort(arr, 0, arrSize - 1);
            break;
        case 3:
            mergeSort(arr, 0, arrSize - 1);
            break;
        case 4:
            bubbleSort();
            break;
        case 5:
            insertionSort();
            break;
        case 6:
            selectionSort();
            break;
    }

    complete = true; // Mark sorting as complete
    cout << "Sorting completed!" << endl;

    // Print the sorted array (optional)
    cout << "Sorted array: ";
    for (int i = 0; i < arrSize; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0; // Exit program
}
