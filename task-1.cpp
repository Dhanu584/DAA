#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to count inversions using a modified merge sort
int mergeAndCount(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left;   // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left;   // Starting index to be sorted
    int invCount = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            invCount += (mid - i + 1); // Number of inversions
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; i++) arr[i] = temp[i];

    return invCount;
}

int mergeSortAndCount(vector<int>& arr, vector<int>& temp, int left, int right) {
    int invCount = 0;
    if (left < right) {
        int mid = (left + right) / 2;

        invCount += mergeSortAndCount(arr, temp, left, mid);
        invCount += mergeSortAndCount(arr, temp, mid + 1, right);
        invCount += mergeAndCount(arr, temp, left, mid, right);
    }
    return invCount;
}

int countInversions(vector<int>& arr) {
    vector<int> temp(arr.size());
    return mergeSortAndCount(arr, temp, 0, arr.size() - 1);
}

int main() {
    int n = 100; // Number of students
    vector<vector<int>> students(n); // Course choices of each student

    // Random input (you can replace this with real data)
    for (int i = 0; i < n; ++i) {
        int courses = 5; // Number of courses per student
        for (int j = 0; j < courses; ++j) {
            students[i].push_back(rand() % 100 + 1); // Random course codes between 1 and 100
        }
    }

    vector<int> inversionCounts(n, 0);
    for (int i = 0; i < n; ++i) {
        inversionCounts[i] = countInversions(students[i]);
    }

    // Count students with specific inversion counts
    int zero = 0, one = 0, two = 0, three = 0;
    for (int count : inversionCounts) {
        if (count == 0) zero++;
        else if (count == 1) one++;
        else if (count == 2) two++;
        else if (count == 3) three++;
    }

    // Output results
    cout << "Number of students with 0 inversions: " << zero << endl;
    cout << "Number of students with 1 inversion: " << one << endl;
    cout << "Number of students with 2 inversions: " << two << endl;
    cout << "Number of students with 3 inversions: " << three << endl;

    return 0;
}
