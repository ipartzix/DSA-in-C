#include <stdio.h> 
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
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
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("3. Quick Sort\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            bubbleSort(arr, n);
            printf("\nArray sorted using Bubble Sort: \n");
            break;
        case 2:
            selectionSort(arr, n);
            printf("\nArray sorted using Selection Sort: \n");
            break;
        case 3:
            quickSort(arr, 0, n - 1);
            printf("\nArray sorted using Quick Sort: \n");
            break;
        default:
            printf("\nInvalid choice! Exiting...\n");
            return 1;
    }
    printArray(arr, n);
    return 0;
}
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}