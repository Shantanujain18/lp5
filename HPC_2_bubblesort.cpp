#include <iostream>
#include <omp.h>

using namespace std;

void bubbleSort(int arr[], int n) {
  int i, j;

  #pragma omp parallel shared(arr, n) private(i,j)
  {
    for (i = 0; i < n - 1; i++) {
      #pragma omp for schedule(dynamic)
      for (j = 0; j < n - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          #pragma omp critical
          {
            swap(arr[j], arr[j + 1]);
          }
        }
      }
    }
  }
}

int main() {
  int arr[] = {64, 25, 12, 22, 11};
  int n = sizeof(arr) / sizeof(arr[0]);

  cout << "Original array: ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  bubbleSort(arr, n);

  cout << "Sorted array: ";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;

  return 0;
}

//#pragma omp parallel directive to parallelize the outer loop
//shared clause to specify that the array arr and the size n are shared among all threads
//used the private clause to specify that the loop variables i and j are private to each thread.
//#pragma omp for directive to parallelize the inner loop 
//schedule(dynamic) clause ensures that the iterations are dynamically assigned to each thread.
//used the #pragma omp critical directive to ensure that the swap operation is performed atomically. 