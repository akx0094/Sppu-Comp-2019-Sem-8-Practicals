#include <iostream>
#include <vector>
#include <omp.h>
#include <random>
#include <chrono>
#include <limits>

using namespace std;

int main() {
    const int SIZE = 10000000;
    vector<int> data(SIZE);

    // Initialize with random numbers between 1 and 10000
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);
    for (int i = 0; i < SIZE; i++) {
        data[i] = dis(gen);
    }

    // Sequential reduction
    auto start = chrono::high_resolution_clock::now();
    int min_val = numeric_limits<int>::max();
    int max_val = numeric_limits<int>::min();
    long long sum = 0;
    for (int num : data) {
        min_val = min(min_val, num);
        max_val = max(max_val, num);
        sum += num;
    }
    double avg = static_cast<double>(sum) / SIZE;
    auto end = chrono::high_resolution_clock::now();
    cout << "Sequential Results:\n"
         << "Min: " << min_val << "\n"
         << "Max: " << max_val << "\n"
         << "Sum: " << sum << "\n"
         << "Average: " << avg << "\n"
         << "Time taken: " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n\n";

    // Parallel reduction
    start = chrono::high_resolution_clock::now();
    min_val = numeric_limits<int>::max();
    max_val = numeric_limits<int>::min();
    sum = 0;
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        min_val = min(min_val, data[i]);
        max_val = max(max_val, data[i]);
        sum += data[i];
    }
    avg = static_cast<double>(sum) / SIZE;
    end = chrono::high_resolution_clock::now();
    cout << "Parallel Results:\n"
         << "Min: " << min_val << "\n"
         << "Max: " << max_val << "\n"
         << "Sum: " << sum << "\n"
         << "Average: " << avg << "\n"
         << "Time taken: " 
         << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds\n";

    return 0;
}

