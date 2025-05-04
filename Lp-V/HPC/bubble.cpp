#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

// Sequential Bubble Sort
void bubbleSortSequential(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort using OpenMP
void bubbleSortParallel(int arr[], int n) {
    #pragma omp parallel for
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Utility function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Predefined array (not random)
    int arr1[] = {20, 10, 50, 40, 60, 30, 70, 80, 90, 100};
    int arr2[10]; // To store the parallel sorted array

    // Copy arr1 into arr2 for parallel sorting
    std::copy(std::begin(arr1), std::end(arr1), arr2);

    const int N = sizeof(arr1) / sizeof(arr1[0]);

    // Sequential Bubble Sort
    double start = omp_get_wtime();
    bubbleSortSequential(arr1, N);
    double end = omp_get_wtime();
    std::cout << "Sequential Bubble Sort time: " << end - start << " seconds" << std::endl;
    printArray(arr1, N);  // Print sorted array

    // Parallel Bubble Sort
    start = omp_get_wtime();
    bubbleSortParallel(arr2, N);
    end = omp_get_wtime();
    std::cout << "Parallel Bubble Sort time: " << end - start << " seconds" << std::endl;
    printArray(arr2, N);  // Print sorted array

    return 0;
}

