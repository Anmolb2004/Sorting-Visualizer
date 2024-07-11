#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <set>

using namespace std;

const int DELAY_MS = 200;
int stepCount;

void printArray(const vector<int>& arr, int current = -1, int comparison = -1, const string& message = "") {
    for (int i = 0; i < arr.size(); ++i) {
        if (i == current) {
            cout << "[" << arr[i] << "] ";
        } else if (i == comparison) {
            cout << "(" << arr[i] << ") ";
        } else {
            cout << arr[i] << " ";
        }
    }
    if (!message.empty()) {
        cout << " - " << message;
    }
    cout << endl;
    stepCount++;
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                printArray(arr, j, j + 1, "Swapping elements");
            } else {
                printArray(arr, j, j + 1, "No swap needed");
            }
            this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            printArray(arr, j + 1, i, "Shifting element");
            this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        }
        arr[j + 1] = key;
        printArray(arr, j + 1, i, "Inserting element");
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
            printArray(arr, min_idx, j, "Finding minimum element");
            this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        }
        swap(arr[min_idx], arr[i]);
        printArray(arr, i, min_idx, "Swapping with minimum element");
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> temp;
    int left = l;
    int right = m + 1;

    while (left <= m && right <= r) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while (left <= m) {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= r) {
        temp.push_back(arr[right]);
        right++;
    }

    for (int i = l; i <= r; ++i) {
        arr[i] = temp[i - l];
        printArray(arr, i, -1, "Merging subarrays");
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l == r) return;

    int m = (l + r) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
            printArray(arr, i, j, "Swapping with pivot");
            this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        }
    }
    swap(arr[i + 1], arr[high]);
    printArray(arr, i + 1, high, "Placing pivot in correct position");
    this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        printArray(arr, i, largest, "Heapifying");
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; --i) {
        swap(arr[0], arr[i]);
        printArray(arr, 0, i, "Swapping with root");
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        heapify(arr, i, 0);
    }
}

void displayMenu() {
    cout << "Sorting Visualizer\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Insertion Sort\n";
    cout << "3. Selection Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n";
    cout << "6. Heap Sort\n";
    cout << "7. Exit\n";
    cout << "Choose an option: ";
}

void displayArrayMenu() {
    cout << "Array Input Options:\n";
    cout << "1. Enter custom array\n";
    cout << "2. Generate random array\n";
    cout << "3. Generate sorted array\n";
    cout << "4. Generate reverse sorted array\n";
    cout << "5. Generate array with few unique elements\n";
    cout << "Choose an option: ";
}

void runSort(int choice, vector<int>& arr) {
    auto start = chrono::high_resolution_clock::now();
    stepCount = 0;

    switch (choice) {
        case 1:
            cout << "Bubble Sort: O(n^2) - Average, O(n^2) - Worst, O(n) - Best\n";
            bubbleSort(arr);
            break;
        case 2:
            cout << "Insertion Sort: O(n^2) - Average, O(n^2) - Worst, O(n) - Best\n";
            insertionSort(arr);
            break;
        case 3:
            cout << "Selection Sort: O(n^2) - Average, O(n^2) - Worst, O(n^2) - Best\n";
            selectionSort(arr);
            break;
        case 4:
            cout << "Merge Sort: O(n log n) - Average, O(n log n) - Worst, O(n log n) - Best\n";
            mergeSort(arr, 0, arr.size() - 1);
            break;
        case 5:
            cout << "Quick Sort: O(n log n) - Average, O(n^2) - Worst, O(n log n) - Best\n";
            quickSort(arr, 0, arr.size() - 1);
            break;
        case 6:
            cout << "Heap Sort: O(n log n) - Average, O(n log n) - Worst, O(n log n) - Best\n";
            heapSort(arr);
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Execution Time: " << duration.count() << " seconds" << endl;
    cout << "Total Steps: " << stepCount << endl;
}

void generateArray(vector<int>& arr, int size, int type) {
    arr.resize(size);
    if (type == 0) {  // Random array
        generate(arr.begin(), arr.end(), []() { return rand() % 100; });
    } else if (type == 1) {  // Sorted array
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
    } else if (type == 2) {  // Reverse sorted array
        for (int i = 0; i < size; ++i) {
            arr[i] = size - i;
        }
    } else if (type == 3) {  // Few unique elements
        int uniqueCount = min(size, 5);
        set<int> uniqueElements;
        while (uniqueElements.size() < uniqueCount) {
            uniqueElements.insert(rand() % 100);
        }
        vector<int> uniqueVector(uniqueElements.begin(), uniqueElements.end());
        for (int i = 0; i < size; ++i) {
            arr[i] = uniqueVector[rand() % uniqueCount];
        }
    }
}

int main() {
    srand(time(0));
    vector<int> arr;

    while (true) {
        displayMenu();
        int sortChoice;
        cin >> sortChoice;

        if (sortChoice == 7) break;

        displayArrayMenu();
        int arrayChoice;
        cin >> arrayChoice;

        int size;
        if (arrayChoice == 1) {
            cout << "Enter the size of the array: ";
            cin >> size;
            arr.resize(size);
            cout << "Enter the elements of the array: ";
            for (int i = 0; i < size; ++i) {
                cin >> arr[i];
            }
        } else {
            cout << "Enter the size of the array: ";
            cin >> size;
            generateArray(arr, size, arrayChoice - 2);
        }

        cout << "Original Array: ";
        printArray(arr);

        runSort(sortChoice, arr);

        cout << "Sorted Array: ";
        printArray(arr);
    }

    return 0;
}
