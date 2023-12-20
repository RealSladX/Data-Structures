#include <iostream>
#include <climits>

using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

void printSubArray(int a[], int start, int end) {
    cout << "Subarray: " << endl;
    for (int i = start; i <= end; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

void selection(int a[], int length){
    int minIndex;
    int temp;
    for(int i = 0; i < length - 1; i++){
        minIndex = i;
        for(int j = i + 1; j < length; j++){
            if(a[j] < a[minIndex]){
                minIndex = j;
            }
        }
        if(a[i] != a[minIndex]){
            cout << "Swapping " << a[i] << " and " << a[minIndex] << endl;
        }else{
            cout << a[i] << " is in correct spot" << endl;
        }
        swap(a[i], a[minIndex]);
        printArray(a, length);
        cout << endl;
    }
}

void insertion(int a[], int length){
    int insertIndex;
    int temp;

    for(int checkIndex = 1; checkIndex < length; checkIndex++){
        int temp = a[checkIndex];
        while (checkIndex > 0 && temp < a[checkIndex - 1]) {
            int shift = a[checkIndex - 1];
            int shiftIndex = checkIndex;
            a[shiftIndex] = shift;
            cout << "Shifting Down " << shift << endl;
            printArray(a, length);
            checkIndex--;
        }
        insertIndex = checkIndex;
        if(temp != a[insertIndex]){
            cout << "Swapping " << temp << " and " << a[insertIndex] << endl;
        }else{
            cout << temp << " is in correct spot" << endl;
        }
        a[insertIndex] = temp;
        printArray(a, length);
        cout << endl;
    } 
}

void quick(int a[], int low, int high) {
    if (low < high) {
        int pivot = a[low];
        int i = low + 1;
        int j = high;

        while (i <= j) {
            while (i <= j && a[i] <= pivot) {
                i++;
            }
            while (i <= j && a[j] > pivot) {
                j--;
            }
            if (i < j) {
                swap(a[i], a[j]);
            }
        }
        swap(a[low], a[j]);
        printSubArray(a, low, high);
        quick(a, low, j - 1);
        quick(a, j + 1, high);
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

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

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


int main(){
    int test[] = {63, 10, 40, 22, 91, 35, 78, 75, 99, 52, 89, 51, 67};
    int length = sizeof(test)/sizeof(test[0]);

    cout<<"Given array is:"<<endl;
    printArray(test, length);
    cout << endl;
    // cout << "Counducting Selection Sort " << endl << endl;
    // selection(test, length);
    // cout << "Sorted Array is: " << endl;
    // printArray(test, length);
    // cout << endl;

    // cout << "Counducting Insertion Sort " << endl << endl;
    // insertion(test, length);
    // cout << "Sorted Array is: " << endl;
    // printArray(test, length);

    // cout << "Conducting Quick Sort" << endl << endl;
    // quick(test, 0, length - 1);
    // printArray(test, length);

    cout << "Conducting Merge Sort " << endl << endl;

    mergeSort(test, 0, length-1);
    printArray(test, length);

    return 0;
}