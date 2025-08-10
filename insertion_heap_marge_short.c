#include <stdio.h>
void insertionSort(int arr[], int n);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void printArray(int arr[], int n);

int main() {
    int choice, n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements: \n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("\nChoose a sorting method:\n");
    printf("1. Insertion Sort\n");
    printf("2. Merge Sort\n");
    printf("3. Heap Sort\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            insertionSort(arr, n);
            printf("\nArray sorted using Insertion Sort: \n");
            break;
        case 2:
            mergeSort(arr, 0, n - 1);
            printf("\nArray sorted using Merge Sort: \n");
            break;
        case 3:
            heapSort(arr, n);
            printf("\nArray sorted using Heap Sort: \n");
            break;
        default:
            printf("\nInvalid choice! Exiting...\n");
            return 1;
    }
    printArray(arr, n);
    return 0;
}
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void heapSort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}


void heapify(int arr[], int n, int i) {
    int largest = i;        
    int left = 2 * i + 1;   
    int right = 2 * i + 2;  

    if (left < n && arr[left] > arr[largest])
        largest = left;
        if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}