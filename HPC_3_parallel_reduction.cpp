#include <iostream>
#include <cmath>
#include <omp.h>

// Function to find the minimum value in an array using parallel reduction
double parallel_min(double* A, int n)
{
    double min_val = A[0];
    #pragma omp parallel for reduction(min: min_val)
    for (int i = 0; i < n; i++) {
        if (A[i] < min_val) {
            min_val = A[i];
        }
    }
    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
double parallel_max(double* A, int n)
{
    double max_val = A[0];
    #pragma omp parallel for reduction(max: max_val)
    for (int i = 0; i < n; i++) {
        if (A[i] > max_val) {
            max_val = A[i];
        }
    }
    return max_val;
}

// Function to find the sum of values in an array using parallel reduction
double parallel_sum(double* A, int n)
{
    double sum = 0.0;
    #pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Function to find the average value of values in an array using parallel reduction
double parallel_avg(double* A, int n)
{
    double sum = parallel_sum(A, n);
    return sum / n;
}

// Example usage
int main()
{
    int n = 10000000;
    double* A = new double[n];
    for (int i = 0; i < n; i++) {
        A[i] = sin(i);
    }

    double min_val = parallel_min(A, n);
    double max_val = parallel_max(A, n);
    double sum = parallel_sum(A, n);
    double avg = parallel_avg(A, n);

    std::cout << "Minimum value: " << min_val << std::endl;
    std::cout << "Maximum value: " << max_val << std::endl;
    std::cout << "Sum of values: " << sum << std::endl;
    std::cout << "Average value: " << avg << std::endl;

    delete[] A;
    return 0;
}
