#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void vectorAddition() {
    const int SIZE = 1000000;  // Size of the vectors
    vector<int> A(SIZE, 1);  // Vector A initialized with 1's
    vector<int> B(SIZE, 2);  // Vector B initialized with 2's
    vector<int> C(SIZE);     // Resultant Vector C

    // Start timing
    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        C[i] = A[i] + B[i];
    }

    // End timing
    double end = omp_get_wtime();
    cout << "Time for vector addition: " << end - start << " seconds" << endl;

    // Uncomment to print a small part of the result
    // cout << "C[0]: " << C[0] << ", C[SIZE-1]: " << C[SIZE-1] << endl;
}

void matrixMultiplication() {
    const int SIZE = 1000;  // Size of the matrix (SIZE x SIZE)
    
    // Initialize matrices A, B and C (Result)
    vector<vector<int>> A(SIZE, vector<int>(SIZE, 1));  // A with all elements as 1
    vector<vector<int>> B(SIZE, vector<int>(SIZE, 2));  // B with all elements as 2
    vector<vector<int>> C(SIZE, vector<int>(SIZE, 0));  // Result matrix C

    // Start timing
    double start = omp_get_wtime();

    // Parallel matrix multiplication
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // End timing
    double end = omp_get_wtime();
    cout << "Time for matrix multiplication: " << end - start << " seconds" << endl;

    // Uncomment to print a small part of the result matrix
    // cout << "C[0][0]: " << C[0][0] << ", C[SIZE-1][SIZE-1]: " << C[SIZE-1][SIZE-1] << endl;
}

int main() {
    // Perform Vector Addition
    vectorAddition();

    // Perform Matrix Multiplication
    matrixMultiplication();

    return 0;
}

