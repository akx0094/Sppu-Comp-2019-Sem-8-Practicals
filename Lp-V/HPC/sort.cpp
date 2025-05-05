#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include <algorithm>  // For std::copy

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

// Merge function for Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    while (i < n1) {
        arr[k++] = left[i++];
    }

    while (j < n2) {
        arr[k++] = right[j++];
    }
}

// Sequential Merge Sort
void mergeSortSequential(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort using OpenMP
void mergeSortParallel(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortParallel(arr, l, m);

            #pragma omp section
            mergeSortParallel(arr, m + 1, r);
        }

        merge(arr, l, m, r);
    }
}

// Utility function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
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

    // Reset arrays for Merge Sort
    std::copy(std::begin(arr1), std::end(arr1), arr2);

    // Sequential Merge Sort
    start = omp_get_wtime();
    mergeSortSequential(arr1, 0, N - 1);
    end = omp_get_wtime();
    std::cout << "Sequential Merge Sort time: " << end - start << " seconds" << std::endl;
    printArray(arr1, N);  // Print sorted array

    // Parallel Merge Sort
    start = omp_get_wtime();
    mergeSortParallel(arr2, 0, N - 1);
    end = omp_get_wtime();
    std::cout << "Parallel Merge Sort time: " << end - start << " seconds" << std::endl;
    printArray(arr2, N);  // Print sorted array

    return 0;
}

